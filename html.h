#ifndef HTML_H
#define HTML_H

const char HTML_PAGE[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="fr">

<head>

<meta charset="utf-8">

<meta
    name="viewport"
    content="width=device-width, initial-scale=1, viewport-fit=cover"
>

<meta
    name="theme-color"
    content="#101318"
>

<title>FRIGO | 3x0c3t</title>

<link rel="stylesheet" href="/style.css">

</head>

<body>

<div class="app">

<header class="header">

    <div class="brand">

        <div class="brand-title">
            🌡️ FRIGO
        </div>

        <div class="brand-subtitle">
            3x0c3t · ESP8266
        </div>

    </div>

    <nav class="links">

        <a
            href="https://3x0c3t.com"
            target="_blank"
            rel="noopener"
        >
            3x0c3t.com
        </a>

        <a
            href="https://github.com/3x0c3t/3x0c3t_S0NDES_CONNECT-es"
            target="_blank"
            rel="noopener"
        >
            GitHub
        </a>

    </nav>

</header>


<section class="system-grid">

    <div class="panel status-panel">

        <div class="panel-title">
            📡 État Wi-Fi
        </div>

        <div id="status" class="status-content">
            Connexion...
        </div>

    </div>


    <div class="panel reboot-panel">

        <div class="panel-title">
            ⚙️ Système
        </div>

        <button
            class="button button-danger"
            onclick="rebootESP()"
        >
            🔄 Reboot ESP8266
        </button>

    </div>

</section>


<section class="panel control-panel">

    <div class="panel-title">
        🎛️ Pilotage
    </div>

    <div class="control-groups">

        <div class="control-group">

    <div class="control-label">
        💡 LEDs
    </div>

    <div class="button-row">

        <button
            class="button button-blue"
            type="button"
            onclick="led('blue')"
        >
            🔵 Bleu
        </button>

        <button
            class="button button-green"
            type="button"
            onclick="led('green')"
        >
            🟢 Vert
        </button>

        <button
            class="button button-red"
            type="button"
            onclick="led('red')"
        >
            🔴 Rouge
        </button>

        <button
            class="button"
            type="button"
            onclick="led('off')"
        >
            ⚫ OFF
        </button>

    </div>

</div>


        <div class="control-group">

            <div class="control-label">
                🔊 Buzzer
            </div>

            <div class="button-row">

                <button
                    class="button"
                    onclick="buzzer('beep')"
                >
                    🔔 Test
                </button>

                <button
                    class="button"
                    onclick="buzzer('success')"
                >
                    ✅ Succès
                </button>

                <button
                    class="button"
                    onclick="buzzer('wifi')"
                >
                    📡 Wi-Fi
                </button>

                <button
                    class="button"
                    onclick="buzzer('error')"
                >
                    ⚠️ Erreur
                </button>

            </div>

        </div>

    </div>

</section>


<section class="panel refresh-panel">

    <div class="panel-title">
        🔄 Rafraîchissement
    </div>

    <div class="refresh-control">

        <label for="refreshInterval">
            Fréquence de lecture des températures
        </label>

        <div class="refresh-input">

            <input
                id="refreshInterval"
                type="number"
                min="1"
                max="60"
                value="5"
            >

            <span>
                secondes
            </span>

            <button
                class="button"
                onclick="changeRefreshInterval()"
            >
                ✓ Appliquer
            </button>

        </div>

    </div>

</section>


<section class="panel sensors-panel">

    <div class="sensors-heading">

        <div>

            <div class="panel-title">
                🌡️ Sondes & consignes
            </div>

            <div class="sensors-subtitle">
                Surveillance des températures
            </div>

        </div>

        <div
            id="sensorSummary"
            class="sensor-summary"
        >
            --
        </div>

    </div>


    <div
        id="temperatures"
        class="sensor-grid"
    >

        <div class="sensor-card state-gray">

            <div class="sensor-header">

                <div class="sensor-name">
                    <span class="sensor-icon">
                        🌡️
                    </span>
                    S1
                </div>

                <div class="sensor-state">
                    CHARGEMENT
                </div>

            </div>

            <div class="sensor-temperature">

                <span class="sensor-temperature-value">
                    --
                </span>

                <span class="sensor-temperature-unit">
                    °C
                </span>

            </div>

        </div>

    </div>

</section>


<footer class="footer">

    <span>
        3x0c3t_S0NDES_CONNECT-es
    </span>

    <span>
        v1.2-dev
    </span>

</footer>

</div>

<script src="/script.js"></script>

</body>

</html>

)rawliteral";

#endif