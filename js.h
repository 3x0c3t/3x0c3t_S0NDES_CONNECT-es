#ifndef JS_H
#define JS_H

const char JS_PAGE[] PROGMEM = R"rawliteral(

/* ============================================================
   VARIABLES
   ============================================================ */

let rebooting = false;

let statusBusy = false;

let temperaturesBusy = false;

let lastSensorCount = 0;


/* ============================================================
   API
   ============================================================ */

async function api(
    url,
    timeout = 1500
)
{
    const controller =
        new AbortController();

    const timeoutId =
        setTimeout(
            () => controller.abort(),
            timeout
        );

    try
    {
        const response =
            await fetch(
                url,
                {
                    method: "GET",

                    cache: "no-store",

                    signal:
                        controller.signal
                }
            );

        if (!response.ok)
        {
            throw new Error(
                "HTTP " +
                response.status
            );
        }

        return await response.json();
    }
    finally
    {
        clearTimeout(timeoutId);
    }
}


/* ============================================================
   ECHAPPEMENT HTML
   ============================================================ */

function escapeHtml(value)
{
    return String(value)
        .replace(
            /&/g,
            "&amp;"
        )
        .replace(
            /</g,
            "&lt;"
        )
        .replace(
            />/g,
            "&gt;"
        )
        .replace(
            /"/g,
            "&quot;"
        )
        .replace(
            /'/g,
            "&#039;"
        );
}


/* ============================================================
   STATUS
   ============================================================ */

async function updateStatus()
{
    if (
        rebooting ||
        statusBusy
    )
    {
        return;
    }

    statusBusy = true;

    try
    {
        const data =
            await api(
                "/api/status",
                1200
            );

        if (rebooting)
        {
            return;
        }


        const wifiValue =
            document.getElementById(
                "wifiValue"
            );

        const ssidValue =
            document.getElementById(
                "ssidValue"
            );

        const ipValue =
            document.getElementById(
                "ipValue"
            );

        const rssiValue =
            document.getElementById(
                "rssiValue"
            );

        const uptimeValue =
            document.getElementById(
                "uptimeValue"
            );

        const badge =
            document.getElementById(
                "connectionBadge"
            );


        if (wifiValue)
        {
            wifiValue.innerHTML =
                data.wifi
                ? '<span class="ok">CONNECTÉ</span>'
                : '<span class="error">ERREUR</span>';
        }


        if (ssidValue)
        {
            ssidValue.textContent =
                data.ssid || "-";
        }


        if (ipValue)
        {
            ipValue.textContent =
                data.ip || "-";
        }


        if (rssiValue)
        {
            rssiValue.textContent =
                Number(data.rssi || 0) +
                " dBm";
        }


        if (uptimeValue)
        {
            uptimeValue.textContent =
                formatUptime(
                    Number(
                        data.uptime || 0
                    )
                );
        }


        if (badge)
        {
            if (data.wifi)
            {
                badge.textContent =
                    "CONNECTÉ";

                badge.className =
                    "badge badge-ok";
            }
            else
            {
                badge.textContent =
                    "ERREUR";

                badge.className =
                    "badge badge-error";
            }
        }
    }
    catch (error)
    {
        /*
         * Silence volontaire.
         *
         * L'ESP peut être en train de
         * redémarrer ou de reconnecter
         * le WiFi.
         */
    }
    finally
    {
        statusBusy = false;
    }
}


/* ============================================================
   UPTIME
   ============================================================ */

function formatUptime(ms)
{
    const seconds =
        Math.floor(
            ms / 1000
        );

    const days =
        Math.floor(
            seconds / 86400
        );

    const hours =
        Math.floor(
            (seconds % 86400) / 3600
        );

    const minutes =
        Math.floor(
            (seconds % 3600) / 60
        );

    const secs =
        seconds % 60;


    if (days > 0)
    {
        return (
            days +
            "j " +
            hours +
            "h"
        );
    }


    if (hours > 0)
    {
        return (
            hours +
            "h " +
            minutes +
            "m"
        );
    }


    if (minutes > 0)
    {
        return (
            minutes +
            "m " +
            secs +
            "s"
        );
    }


    return (
        secs +
        " s"
    );
}


/* ============================================================
   TEMPERATURES
   ============================================================ */

async function updateTemperatures()
{
    if (
        rebooting ||
        temperaturesBusy
    )
    {
        return;
    }

    temperaturesBusy = true;

    try
    {
        const data =
            await api(
                "/api/temperatures",
                1200
            );

        if (rebooting)
        {
            return;
        }


        if (
            !data ||
            !Array.isArray(
                data.temperatures
            )
        )
        {
            throw new Error(
                "Format températures invalide"
            );
        }


        const temperatures =
            data.temperatures;


        lastSensorCount =
            temperatures.length;


        const temperatureElement =
            document.getElementById(
                "temperatures"
            );


        const countElement =
            document.getElementById(
                "sensorCount"
            );


        if (countElement)
        {
            countElement.textContent =
                temperatures.length +
                (
                    temperatures.length > 1
                    ? " sondes"
                    : " sonde"
                );
        }


        if (!temperatureElement)
        {
            return;
        }


        let html = "";


        for (
            let i = 0;
            i < temperatures.length;
            i++
        )
        {
            const value =
                Number(
                    temperatures[i]
                );


            const valid =
                Number.isFinite(
                    value
                );


            html +=

                '<div class="sensor">' +

                    '<div class="sensor-header">' +

                        '<span class="sensor-name">' +

                            "SONDE " +

                            (i + 1) +

                        "</span>" +

                        '<span class="sensor-state">' +

                            (
                                valid
                                ? "OK"
                                : "ERREUR"
                            ) +

                        "</span>" +

                    "</div>" +

                    '<div class="sensor-value">' +

                        (
                            valid
                            ? value.toFixed(2)
                            : "--"
                        ) +

                        '<span class="sensor-unit">' +
                            "°C" +
                        "</span>" +

                    "</div>" +

                "</div>";
        }


        if (
            temperatures.length === 0
        )
        {
            html =
                '<div class="loading">' +
                    "Aucune sonde détectée" +
                "</div>";
        }


        temperatureElement.innerHTML =
            html;


        updateSetpoints(
            temperatures.length
        );
    }
    catch (error)
    {
        /*
         * Pas d'erreur console.
         *
         * Une perte réseau temporaire
         * n'est pas une panne logicielle.
         */
    }
    finally
    {
        temperaturesBusy = false;
    }
}


/* ============================================================
   CONSIGNES
   ============================================================ */

function updateSetpoints(count)
{
    const element =
        document.getElementById(
            "setpoints"
        );

    if (!element)
    {
        return;
    }


    if (count <= 0)
    {
        element.innerHTML =
            '<div class="loading">' +
                "Aucune sonde" +
            "</div>";

        return;
    }


    /*
     * Ne reconstruit pas inutilement
     * l'interface si le nombre de sondes
     * n'a pas changé.
     */

    const existing =
        element.children.length;


    if (
        existing === count
    )
    {
        return;
    }


    let html = "";


    for (
        let i = 0;
        i < count;
        i++
    )
    {
        const key =
            "setpoint_" +
            i;


        const saved =
            localStorage.getItem(
                key
            );


        const value =
            saved !== null
            ? saved
            : "25.00";


        html +=

            '<div class="setpoint">' +

                '<span class="setpoint-name">' +

                    "S" +

                    (i + 1) +

                "</span>" +

                '<input ' +

                    'type="number" ' +

                    'step="0.1" ' +

                    'min="-55" ' +

                    'max="125" ' +

                    'value="' +

                    value +

                    '" ' +

                    'id="setpoint_' +

                    i +

                    '" ' +

                    'onchange="saveSetpoint(' +

                    i +

                    ')" ' +

                '>' +

                '<span class="setpoint-unit">' +

                    "°C" +

                "</span>" +

            "</div>";
    }


    element.innerHTML =
        html;


    /*
     * Note :
     *
     * Pour l'instant les consignes
     * sont conservées dans le navigateur.
     *
     * Une API ESP dédiée pourra ensuite
     * les envoyer réellement à l'ESP8266.
     */

    const note =
        document.createElement(
            "div"
        );

    note.className =
        "setpoint-note";

    note.textContent =
        "Consignes locales du navigateur";

    element.appendChild(
        note
    );
}


/* ============================================================
   SAUVEGARDE CONSIGNE
   ============================================================ */

function saveSetpoint(index)
{
    const input =
        document.getElementById(
            "setpoint_" +
            index
        );

    if (!input)
    {
        return;
    }


    localStorage.setItem(
        "setpoint_" + index,
        input.value
    );
}


/* ============================================================
   LED
   ============================================================ */

async function led(color)
{
    if (rebooting)
    {
        return;
    }


    const status =
        document.getElementById(
            "ledStatus"
        );


    if (status)
    {
        status.textContent =
            "Commande...";
    }


    try
    {
        await api(
            "/api/led?color=" +
            encodeURIComponent(
                color
            ),
            1500
        );


        if (status)
        {
            status.textContent =
                color.toUpperCase();
        }
    }
    catch (error)
    {
        if (status)
        {
            status.textContent =
                "Indisponible";
        }
    }
}


/* ============================================================
   BUZZER
   ============================================================ */

async function buzzer(action)
{
    if (rebooting)
    {
        return;
    }


    const status =
        document.getElementById(
            "buzzerStatus"
        );


    if (status)
    {
        status.textContent =
            "Commande...";
    }


    try
    {
        await api(
            "/api/buzzer?action=" +
            encodeURIComponent(
                action
            ),
            1500
        );


        if (status)
        {
            status.textContent =
                "OK";
        }
    }
    catch (error)
    {
        if (status)
        {
            status.textContent =
                "Indisponible";
        }
    }
}


/* ============================================================
   REBOOT
   ============================================================ */

function rebootESP()
{
    if (rebooting)
    {
        return;
    }


    if (
        !confirm(
            "Redémarrer l'ESP8266 ?"
        )
    )
    {
        return;
    }


    /*
     * BLOQUER immédiatement
     * les mises à jour périodiques.
     */

    rebooting = true;


    const status =
        document.getElementById(
            "status"
        );


    const badge =
        document.getElementById(
            "connectionBadge"
        );


    const button =
        document.getElementById(
            "rebootButton"
        );


    if (status)
    {
        status.innerHTML =
            '<div class="status-item">' +
                '<strong class="warning">' +
                    "REDÉMARRAGE..." +
                "</strong>" +
            "</div>";
    }


    if (badge)
    {
        badge.textContent =
            "REBOOT";

        badge.className =
            "badge badge-warning";
    }


    if (button)
    {
        button.disabled =
            true;

        button.textContent =
            "⏳ Redémarrage...";
    }


    /*
     * Ne surtout pas await.
     *
     * L'ESP peut couper la connexion
     * avant de retourner sa réponse.
     */

    fetch(
        "/api/reboot",
        {
            method: "GET",

            cache: "no-store",

            keepalive: false
        }
    )
    .catch(
        () =>
        {
            /*
             * Réponse perdue = normal.
             */
        }
    );


    /*
     * Laisse le temps à l'ESP
     * de redémarrer.
     */

    setTimeout(
        waitForESP,
        6000
    );
}


/* ============================================================
   ATTENTE RETOUR ESP
   ============================================================ */

async function waitForESP()
{
    let attempts = 0;

    const maxAttempts = 20;


    async function check()
    {
        attempts++;


        try
        {
            const data =
                await api(
                    "/api/status",
                    1200
                );


            if (
                data &&
                data.wifi === true
            )
            {
                /*
                 * ESP revenu.
                 */

                rebooting = false;


                const button =
                    document.getElementById(
                        "rebootButton"
                    );


                if (button)
                {
                    button.disabled =
                        false;

                    button.textContent =
                        "🔄 Redémarrer l'ESP8266";
                }


                updateStatus();

                updateTemperatures();

                return;
            }
        }
        catch (error)
        {
            /*
             * ESP encore indisponible.
             */
        }


        if (
            attempts < maxAttempts
        )
        {
            setTimeout(
                check,
                1000
            );
        }
        else
        {
            /*
             * On rend la main au système
             * normal de rafraîchissement.
             */

            rebooting = false;


            const button =
                document.getElementById(
                    "rebootButton"
                );


            if (button)
            {
                button.disabled =
                    false;

                button.textContent =
                    "🔄 Redémarrer l'ESP8266";
            }


            updateStatus();

            updateTemperatures();
        }
    }


    check();
}


/* ============================================================
   COMPATIBILITE
   ============================================================ */

function reboot()
{
    rebootESP();
}


/* ============================================================
   INITIALISATION
   ============================================================ */

function initWebInterface()
{
    updateStatus();

    updateTemperatures();
}


/* ============================================================
   RAFRAICHISSEMENT STATUS
   ============================================================ */

setInterval(
    function()
    {
        if (!rebooting)
        {
            updateStatus();
        }
    },
    3000
);


/* ============================================================
   RAFRAICHISSEMENT TEMPERATURES
   ============================================================ */

setInterval(
    function()
    {
        if (!rebooting)
        {
            updateTemperatures();
        }
    },
    2500
);


/* ============================================================
   DEMARRAGE
   ============================================================ */

if (
    document.readyState ===
    "loading"
)
{
    document.addEventListener(
        "DOMContentLoaded",
        initWebInterface
    );
}
else
{
    initWebInterface();
}

)rawliteral";

#endif