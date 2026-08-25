#ifndef JS_H
#define JS_H

const char JS_PAGE[] PROGMEM = R"rawliteral(

async function api(url)
{
    const response = await fetch(
        url,
        {
            cache: "no-store"
        }
    );

    if (!response.ok)
    {
        throw new Error(
            "HTTP " + response.status
        );
    }

    return await response.json();
}


// ============================================================
// ETAT DU SYSTEME
// ============================================================

async function updateStatus()
{
    try
    {
        const data = await api(
            "/api/status"
        );

        let html = "";

        html +=
            "<p>WiFi : " +
            (
                data.wifi
                ? '<span class="ok">CONNECTÉ</span>'
                : '<span class="error">ERREUR</span>'
            ) +
            "</p>";

        html +=
            "<p>SSID : <strong>" +
            (
                data.ssid || "-"
            ) +
            "</strong></p>";

        html +=
            "<p>IP : <strong>" +
            (
                data.ip || "-"
            ) +
            "</strong></p>";

        html +=
            "<p>Signal : " +
            (
                data.rssi !== undefined
                ? data.rssi + " dBm"
                : "-"
            ) +
            "</p>";

        html +=
            "<p>Uptime : " +
            (
                data.uptime !== undefined
                ? Math.floor(data.uptime) + " s"
                : "-"
            ) +
            "</p>";

        const element =
            document.getElementById(
                "status"
            );

        if (element)
        {
            element.innerHTML = html;
        }
    }
    catch (error)
    {
        console.error(
            "Erreur état :",
            error
        );

        const element =
            document.getElementById(
                "status"
            );

        if (element)
        {
            element.innerHTML =
                '<span class="error">ESP inaccessible</span>';
        }
    }
}


// ============================================================
// TEMPERATURES
// ============================================================

async function updateTemperatures()
{
    try
    {
        const data = await api(
            "/api/temperatures"
        );

        let html = "";

        // ----------------------------------------------------
        // Vérification des données reçues
        // ----------------------------------------------------

        if (
            !data ||
            !Array.isArray(data.temperatures)
        )
        {
            throw new Error(
                "Format température invalide"
            );
        }

        // ----------------------------------------------------
        // Affichage
        // ----------------------------------------------------

        for (
            let i = 0;
            i < data.temperatures.length;
            i++
        )
        {
            const value =
                Number(
                    data.temperatures[i]
                );

            html +=
                '<div class="temperature">' +
                "<strong>S" +
                (i + 1) +
                "</strong> : " +
                (
                    Number.isFinite(value)
                    ? value.toFixed(2)
                    : "--"
                ) +
                " °C" +
                "</div>";
        }

        // ----------------------------------------------------
        // Aucun capteur
        // ----------------------------------------------------

        if (
            data.temperatures.length === 0
        )
        {
            html =
                '<div class="warning">Aucune sonde</div>';
        }

        const element =
            document.getElementById(
                "temperatures"
            );

        if (element)
        {
            element.innerHTML = html;
        }
    }
    catch (error)
    {
        console.error(
            "Erreur températures :",
            error
        );

        const element =
            document.getElementById(
                "temperatures"
            );

        if (element)
        {
            element.innerHTML =
                '<span class="error">Erreur température</span>';
        }
    }
}


// ============================================================
// LED
// ============================================================

async function led(color)
{
    try
    {
        await api(
            "/api/led?color=" +
            encodeURIComponent(color)
        );

        updateStatus();
    }
    catch (error)
    {
        console.error(
            "Erreur LED :",
            error
        );

        alert(
            "Erreur LED"
        );
    }
}


// ============================================================
// BUZZER
// ============================================================

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

        alert(
            "Erreur buzzer"
        );
    }
}


// ============================================================
// REBOOT
// ============================================================

async function reboot()
{
    if (!confirm("Redémarrer l'ESP8266 ?"))
    {
        return;
    }

    const element = document.getElementById("status");

    if (element)
    {
        element.innerHTML =
            '<span class="warning">Redémarrage en cours...</span>';
    }

    try
    {
        await api("/api/reboot");
    }
    catch (error)
    {
        // Normal :
        // l'ESP peut avoir redémarré avant la réponse HTTP.
        console.log("ESP redémarré ou connexion interrompue.");
    }
}


// ============================================================
// COMPATIBILITÉ AVEC LE BOUTON HTML
// ============================================================

function rebootESP()
{
    reboot();
}


    // --------------------------------------------------------
    // Arrêt des timers
    // --------------------------------------------------------

    if (window.statusTimer)
    {
        clearInterval(
            window.statusTimer
        );

        window.statusTimer = null;
    }

    if (window.temperatureTimer)
    {
        clearInterval(
            window.temperatureTimer
        );

        window.temperatureTimer = null;
    }


    // --------------------------------------------------------
    // Demande de reboot
    // --------------------------------------------------------

    try
    {
        await fetch(
            "/api/reboot",
            {
                method: "GET",
                cache: "no-store"
            }
        );
    }
    catch (error)
    {
        // Normal :
        // l'ESP peut couper la connexion
        // immédiatement pendant son reboot.
    }


    // --------------------------------------------------------
    // Attente du redémarrage
    // --------------------------------------------------------

    setTimeout(
        function()
        {
            location.reload();
        },
        5000
    );
}


// ============================================================
// INITIALISATION
// ============================================================

updateStatus();

updateTemperatures();


// ============================================================
// RAFRAICHISSEMENT AUTOMATIQUE
// ============================================================

window.statusTimer =
    setInterval(
        updateStatus,
        3000
    );


window.temperatureTimer =
    setInterval(
        updateTemperatures,
        2000
    );


// ============================================================
// FIN
// ============================================================

)rawliteral";

#endif