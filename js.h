#ifndef JS_H
#define JS_H

const char JS_PAGE[] PROGMEM = R"rawliteral(

async function api(url)
{
    const response = await fetch(url);

    if (!response.ok)
    {
        throw new Error("HTTP " + response.status);
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
        const data = await api("/api/status");

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
            data.ssid +
            "</strong></p>";

        html +=
            "<p>IP : <strong>" +
            data.ip +
            "</strong></p>";

        html +=
            "<p>Signal : " +
            data.rssi +
            " dBm</p>";

        html +=
            "<p>Uptime : " +
            data.uptime +
            " s</p>";

        const element = document.getElementById("status");

        if (element)
        {
            element.innerHTML = html;
        }
    }
    catch (error)
    {
        console.error("Erreur état :", error);

        const element = document.getElementById("status");

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
        const data = await api("/api/temperatures");

        let html = "";

        if (!data.temperatures || !Array.isArray(data.temperatures))
        {
            throw new Error("Format JSON températures invalide");
        }

        for (let i = 0; i < data.temperatures.length; i++)
        {
            html +=
                '<div class="temperature">' +
                "S" +
                (i + 1) +
                " : " +
                Number(data.temperatures[i]).toFixed(2) +
                " °C" +
                "</div>";
        }

        const element =
            document.getElementById("temperatures");

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
            document.getElementById("temperatures");

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
    }
    catch (error)
    {
        console.error("Erreur LED :", error);
        alert("Erreur LED");
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

        alert("Erreur buzzer");
    }
}


// ============================================================
// REBOOT
// ============================================================

async function rebootESP()
{
    if (!confirm("Redémarrer l'ESP8266 ?"))
    {
        return;
    }

    try
    {
        await api("/api/reboot");
    }
    catch (error)
    {
        // Normal :
        // l'ESP vient probablement de redémarrer.
    }

    const element =
        document.getElementById("status");

    if (element)
    {
        element.innerHTML =
            "Redémarrage en cours...";
    }
}


// Alias éventuel
function reboot()
{
    rebootESP();
}


// ============================================================
// INITIALISATION
// ============================================================

updateStatus();
updateTemperatures();


// ============================================================
// RAFRAICHISSEMENT AUTOMATIQUE
// ============================================================

setInterval(
    updateStatus,
    3000
);

setInterval(
    updateTemperatures,
    2000
);

)rawliteral";

#endif