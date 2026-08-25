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

    <!-- ======================================================
         HEADER
         ====================================================== -->

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


    <!-- ======================================================
         ETAT WIFI + REBOOT
         ====================================================== -->

    <section class="system-grid">

        <div class="panel">

            <div class="panel-title">
                📡 État Wi-Fi
            </div>

            <div
                id="status"
                class="status-content"
            >
                Connexion...
            </div>

        </div>


        <div class="panel system-panel">

            <div class="panel-title">
                ⚙️ Système
            </div>

            <button
                class="button button-danger reboot-button"
                type="button"
                onclick="rebootESP()"
            >
                🔄 Reboot ESP8266
            </button>

        </div>

    </section>


    <!-- ======================================================
         PILOTAGE
         ====================================================== -->

    <section class="panel">

        <div class="panel-title">
            🎛️ Pilotage
        </div>

        <div class="control-groups">

            <!-- LEDS -->

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
                        class="button button-orange"
                        type="button"
                        onclick="led('orange')"
                    >
                        🟠 Orange
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


            <!-- BUZZER -->

            <div class="control-group">

                <div class="control-label">
                    🔊 Buzzer
                </div>

                <div class="button-row">

                    <button
                        class="button"
                        type="button"
                        onclick="buzzer('beep')"
                    >
                        🔔 Test
                    </button>

                    <button
                        class="button"
                        type="button"
                        onclick="buzzer('success')"
                    >
                        ✅ Succès
                    </button>

                    <button
                        class="button"
                        type="button"
                        onclick="buzzer('wifi')"
                    >
                        📡 Wi-Fi
                    </button>

                    <button
                        class="button"
                        type="button"
                        onclick="buzzer('error')"
                    >
                        ⚠️ Erreur
                    </button>

                </div>

            </div>

        </div>

    </section>


    <!-- ======================================================
         REGLAGES AFFICHAGE
         ====================================================== -->

    <section class="panel refresh-panel">

        <div class="refresh-settings">

            <div>

                <div class="panel-title">
                    🔄 Rafraîchissement
                </div>

                <div class="refresh-description">
                    Fréquence de lecture des températures
                </div>

            </div>

            <div class="refresh-control">

                <label for="refreshInterval">
                    Intervalle
                </label>

                <input
                    id="refreshInterval"
                    type="number"
                    min="1"
                    max="60"
                    step="1"
                    value="2"
                    inputmode="numeric"
                >

                <span>
                    secondes
                </span>

                <button
                    class="button"
                    type="button"
                    onclick="applyRefreshInterval()"
                >
                    ✓ Appliquer
                </button>

            </div>

        </div>

    </section>


    <!-- ======================================================
         SONDES
         ====================================================== -->

    <section class="panel sensors-panel">

        <div class="panel-title">
            🌡️ Sondes & consignes
        </div>

        <div
            id="temperatures"
            class="sensor-grid"
        >
            Chargement des sondes...
        </div>

    </section>


    <!-- ======================================================
         FOOTER
         ====================================================== -->

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