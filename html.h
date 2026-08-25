#ifndef HTML_H
#define HTML_H

const char HTML_PAGE[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="fr">

<head>

<meta charset="UTF-8">

<meta
    name="viewport"
    content="width=device-width, initial-scale=1.0"
>

<title>3x0c3t S0NDES</title>

<style>

* {
    box-sizing: border-box;
}

body {
    margin: 0;
    padding: 20px;

    background: #111;
    color: #eee;

    font-family:
        Arial,
        Helvetica,
        sans-serif;
}

.container {
    max-width: 900px;
    margin: auto;
}

h1 {
    margin-bottom: 5px;
}

h2 {
    margin-top: 0;
}

.card {
    background: #1c1c1c;

    border: 1px solid #333;

    border-radius: 10px;

    padding: 15px;

    margin-bottom: 15px;
}

.status {
    font-size: 18px;
}

.ok {
    color: #55dd77;
}

.error {
    color: #ff5555;
}

button {
    border: 0;

    border-radius: 6px;

    padding: 12px 16px;

    margin: 4px;

    font-size: 15px;

    cursor: pointer;
}

button:hover {
    opacity: 0.8;
}

.temperature {
    font-size: 24px;

    padding: 8px 0;
}

pre {
    white-space: pre-wrap;
}

</style>

</head>


<body>

<div class="container">

<h1>🌡️ 3x0c3t S0NDES</h1>

<p>Interface de pilotage ESP8266</p>


<!-- =====================================================
     ÉTAT
===================================================== -->

<div class="card">

<h2>État système</h2>

<div id="status">
    Chargement...
</div>

</div>


<!-- =====================================================
     TEMPÉRATURES
===================================================== -->

<div class="card">

<h2>🌡️ Températures</h2>

<div id="temperatures">
    Chargement...
</div>

</div>


<!-- =====================================================
     LED
===================================================== -->

<div class="card">

<h2>💡 LEDs</h2>

<button onclick="led('off')">
    OFF
</button>

<button onclick="led('green')">
    Vert
</button>

<button onclick="led('red')">
    Rouge
</button>

<button onclick="led('orange')">
    Orange
</button>

<button onclick="led('rainbow')">
    Rainbow
</button>

</div>


<!-- =====================================================
     BUZZER
===================================================== -->

<div class="card">

<h2>🔊 Buzzer</h2>

<button onclick="buzzer('beep')">
    Bip
</button>

<button onclick="buzzer('success')">
    Succès
</button>

<button onclick="buzzer('startup')">
    Mélodie
</button>

</div>


<!-- =====================================================
     REBOOT
===================================================== -->

<div class="card">

<h2>⚙️ Système</h2>

<button onclick="reboot()">
    🔄 Redémarrer l'ESP
</button>

</div>


</div>


<script>

async function api(url)
{
    const response = await fetch(url);

    if (!response.ok)
        throw new Error("HTTP " + response.status);

    return await response.json();
}


// ========================================================
// STATUS
// ========================================================

async function updateStatus()
{
    try
    {
        const data =
            await api("/api/status");

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
            Math.floor(data.uptime / 1000) +
            " s</p>";

        document.getElementById("status").innerHTML =
            html;
    }
    catch (error)
    {
        document.getElementById("status").innerHTML =
            '<span class="error">ESP inaccessible</span>';
    }
}


// ========================================================
// TEMPERATURES
// ========================================================

async function updateTemperatures()
{
    try
    {
        const data =
            await api("/api/temperatures");

        let html = "";

        for (
            let i = 0;
            i < data.values.length;
            i++
        )
        {
            html +=
                '<div class="temperature">' +
                "S" +
                (i + 1) +
                " : " +
                data.values[i].toFixed(2) +
                " °C" +
                "</div>";
        }

        document.getElementById(
            "temperatures"
        ).innerHTML = html;
    }
    catch (error)
    {
        document.getElementById(
            "temperatures"
        ).innerHTML =
            '<span class="error">Erreur</span>';
    }
}


// ========================================================
// LED
// ========================================================

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
        alert("Erreur LED");
    }
}


// ========================================================
// BUZZER
// ========================================================

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
        alert("Erreur buzzer");
    }
}


// ========================================================
// REBOOT
// ========================================================

async function reboot()
{
    if (
        !confirm(
            "Redémarrer l'ESP8266 ?"
        )
    )
        return;

    try
    {
        await api("/api/reboot");
    }
    catch (error)
    {
        // Normal :
        // l'ESP vient probablement de redémarrer.
    }

    document.getElementById(
        "status"
    ).innerHTML =
        "Redémarrage en cours...";
}


// ========================================================
// RAFRAÎCHISSEMENT
// ========================================================

updateStatus();
updateTemperatures();

setInterval(
    updateStatus,
    3000
);

setInterval(
    updateTemperatures,
    2000
);

</script>

</body>

</html>

)rawliteral";

#endif