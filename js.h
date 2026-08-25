#ifndef JS_H
#define JS_H

const char JS_PAGE[] PROGMEM = R"rawliteral(

/* ============================================================
   API
   ============================================================ */

async function api(url)
{
    const response = await fetch(
        url + "?t=" + Date.now(),
        {
            method: "GET",
            cache: "no-store"
        }
    );

    if (!response.ok)
    {
        throw new Error("HTTP " + response.status);
    }

    return await response.json();
}


/* ============================================================
   ÉTAT
   ============================================================ */

async function updateStatus()
{
    try
    {
        const data = await api("/api/status");

        const element = document.getElementById("status");

        if (!element)
        {
            return;
        }

        element.innerHTML =
            "<p>WiFi : " +
            (
                data.wifi
                ? '<span class="ok">CONNECTÉ</span>'
                : '<span class="error">ERREUR</span>'
            ) +
            "</p>" +

            "<p>SSID : <strong>" +
            (data.ssid || "-") +
            "</strong></p>" +

            "<p>IP : <strong>" +
            (data.ip || "-") +
            "</strong></p>" +

            "<p>Signal : " +
            (data.rssi ?? "-") +
            " dBm</p>" +

            "<p>Uptime : " +
            Math.floor((data.uptime || 0) / 1000) +
            " s</p>";
    }
    catch (error)
    {
        console.warn(
            "ESP temporairement inaccessible",
            error
        );

        const element =
            document.getElementById("status");

        if (element)
        {
            element.innerHTML =
                '<span class="error">' +
                "ESP temporairement inaccessible" +
                "</span>";
        }
    }
}


/* ============================================================
   TEMPÉRATURES
   ============================================================ */

async function updateTemperatures()
{
    try
    {
        const data =
            await api("/api/temperatures");

        if (!data)
        {
            throw new Error("Réponse vide");
        }

        if (!Array.isArray(data.temperatures))
        {
            throw new Error(
                "Format JSON températures invalide"
            );
        }

        const element =
            document.getElementById("temperatures");

        if (!element)
        {
            return;
        }

        let html = "";

        for (
            let i = 0;
            i < data.temperatures.length;
            i++
        )
        {
            const temperature =
                Number(data.temperatures[i]);

            const value =
                Number.isFinite(temperature)
                ? temperature.toFixed(2)
                : "--";

            html +=
                '<div class="temperature">' +
                "<strong>S" +
                (i + 1) +
                "</strong> : " +
                value +
                " °C" +
                "</div>";
        }

        element.innerHTML = html;
    }
    catch (error)
    {
        console.warn(
            "Températures temporairement indisponibles",
            error
        );

        const element =
            document.getElementById("temperatures");

        if (element)
        {
            element.innerHTML =
                '<span class="error">' +
                "Températures temporairement indisponibles" +
                "</span>";
        }
    }
}


/* ============================================================
   LED
   ============================================================ */

async function led(color)
{
    try
    {
        await api(
            "/api/led?color=" +
            encodeURIComponent(color)
        );
    }
    catch (error)
    {
        console.error(
            "Erreur LED :",
            error
        );
    }
}


/* ============================================================
   BUZZER
   ============================================================ */

async function buzzer(action)
{
    try
    {
        await api(
            "/api/buzzer?action=" +
            encodeURIComponent(action)
        );
    }
    catch (error)
    {
        console.error(
            "Erreur buzzer :",
            error
        );
    }
}


/* ============================================================
   REBOOT
   ============================================================ */

async function reboot()
{
    if (
        !confirm(
            "Redémarrer l'ESP8266 ?"
        )
    )
    {
        return;
    }

    try
    {
        await api("/api/reboot");
    }
    catch (error)
    {
        /*
         * Normal :
         * l'ESP peut couper la connexion
         * pendant son redémarrage.
         */
    }

    const element =
        document.getElementById("status");

    if (element)
    {
        element.innerHTML =
            '<span class="ok">' +
            "Redémarrage en cours..." +
            "</span>";
    }
}


/*
 * Compatibilité avec l'ancien HTML
 */
function rebootESP()
{
    reboot();
}


/* ============================================================
   INTERVALLE DE RAFRAÎCHISSEMENT
   ============================================================ */

let refreshInterval = 5;
let refreshTimer = null;
let refreshBusy = false;


/* ============================================================
   LECTURE DE L'INTERVALLE
   ============================================================ */

function getRefreshInterval()
{
    const element =
        document.getElementById(
            "refreshInterval"
        );

    if (!element)
    {
        return 5;
    }

    let value =
        parseInt(element.value, 10);

    if (!Number.isFinite(value))
    {
        value = 5;
    }

    if (value < 1)
    {
        value = 1;
    }

    if (value > 60)
    {
        value = 60;
    }

    return value;
}


/* ============================================================
   RAFRAÎCHISSEMENT COMPLET
   ============================================================ */

async function refreshAll()
{
    /*
     * Empêche plusieurs cycles simultanés.
     */
    if (refreshBusy)
    {
        return;
    }

    refreshBusy = true;

    try
    {
        /*
         * IMPORTANT :
         * Les deux requêtes sont séquentielles.
         * Pas de bombardement simultané de l'ESP.
         */

        await updateStatus();

        await new Promise(
            resolve => setTimeout(resolve, 50)
        );

        await updateTemperatures();
    }
    finally
    {
        refreshBusy = false;
    }
}


/* ============================================================
   TIMER
   ============================================================ */

function startRefreshTimer()
{
    if (refreshTimer !== null)
    {
        clearTimeout(refreshTimer);
    }

    refreshInterval =
        getRefreshInterval();

    async function loop()
    {
        await refreshAll();

        refreshInterval =
            getRefreshInterval();

        refreshTimer =
            setTimeout(
                loop,
                refreshInterval * 1000
            );
    }

    refreshTimer =
        setTimeout(
            loop,
            refreshInterval * 1000
        );
}


/* ============================================================
   CHANGEMENT INTERVALLE
   ============================================================ */

function changeRefreshInterval()
{
    refreshInterval =
        getRefreshInterval();

    startRefreshTimer();
}


/* ============================================================
   CONSIGNES
   ============================================================ */

const sensorSetpoints = {};


function getSensorSetpoint(index)
{
    const key =
        "sensorSetpoint_" +
        index;

    const stored =
        localStorage.getItem(key);

    if (stored === null)
    {
        return "";
    }

    return stored;
}


function setSensorSetpoint(index)
{
    const input =
        document.getElementById(
            "setpoint_" + index
        );

    if (!input)
    {
        return;
    }

    let value =
        parseFloat(input.value);

    if (!Number.isFinite(value))
    {
        localStorage.removeItem(
            "sensorSetpoint_" + index
        );

        return;
    }

    /*
     * Limites raisonnables pour éviter
     * les joyeusetés du genre 384729 °C.
     */

    if (value < -55)
    {
        value = -55;
    }

    if (value > 125)
    {
        value = 125;
    }

    input.value =
        value.toFixed(1);

    localStorage.setItem(
        "sensorSetpoint_" + index,
        value
    );

    updateSetpointDisplay(index);
}


function updateSetpointDisplay(index)
{
    const input =
        document.getElementById(
            "setpoint_" + index
        );

    if (!input)
    {
        return;
    }

    const value =
        parseFloat(input.value);

    const display =
        document.getElementById(
            "setpointDisplay_" + index
        );

    if (!display)
    {
        return;
    }

    if (Number.isFinite(value))
    {
        display.textContent =
            value.toFixed(1) +
            " °C";
    }
    else
    {
        display.textContent =
            "Aucune consigne";
    }
}


function restoreSetpoints()
{
    const inputs =
        document.querySelectorAll(
            '[id^="setpoint_"]'
        );

    inputs.forEach(
        function(input)
        {
            const id =
                input.id;

            const index =
                parseInt(
                    id.replace(
                        "setpoint_",
                        ""
                    ),
                    10
                );

            if (!Number.isFinite(index))
            {
                return;
            }

            const value =
                getSensorSetpoint(index);

            if (value !== "")
            {
                input.value =
                    Number(value).toFixed(1);
            }

            updateSetpointDisplay(index);
        }
    );
}


/* ============================================================
   INITIALISATION
   ============================================================ */

async function init()
{
    /*
     * Premier affichage.
     */
    await refreshAll();

    /*
     * Restaurer les consignes locales.
     */
    restoreSetpoints();

    /*
     * Démarrer UNE SEULE boucle.
     */
    startRefreshTimer();
}


/* ============================================================
   DOM READY
   ============================================================ */

if (
    document.readyState ===
    "loading"
)
{
    document.addEventListener(
        "DOMContentLoaded",
        init
    );
}
else
{
    init();
}

)rawliteral";

#endif