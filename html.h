#ifndef HTML_H
#define HTML_H

const char HTML_PAGE[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="fr">

<head>

<meta charset="UTF-8">

<meta
    name="viewport"
    content="width=device-width, initial-scale=1.0, viewport-fit=cover"
>

<meta
    name="theme-color"
    content="#111827"
>

<title>3x0c3t S0NDES</title>

<link
    rel="stylesheet"
    href="/style.css?v=12"
>

</head>


<body>

<div class="app">


    <!-- =====================================================
         HEADER
         ===================================================== -->

    <header class="header">

        <div class="header-main">

            <div>

                <h1>
                    🌡️ 3x0c3t S0NDES
                </h1>

                <div class="subtitle">
                    ESP8266 · Surveillance & pilotage
                </div>

            </div>

            <div class="version">
                v1.2
            </div>

        </div>


        <div class="header-links">

            <a
                href="https://3x0c3t.com"
                target="_blank"
                rel="noopener"
            >
                3x0c3t.com
            </a>

            <span>·</span>

            <a
                href="https://github.com/3x0c3t/3x0c3t_S0NDES_CONNECT-es"
                target="_blank"
                rel="noopener"
            >
                GitHub
            </a>

        </div>

    </header>



    <!-- =====================================================
         CONTENU PRINCIPAL
         ===================================================== -->

    <main class="main">


        <!-- =================================================
             ETAT + REBOOT
             ================================================= -->

        <section class="card status-card">

            <div class="card-title">

                <div>
                    <span class="icon">📡</span>
                    <span>État système</span>
                </div>

                <span
                    id="connectionBadge"
                    class="badge badge-ok"
                >
                    CONNECTÉ
                </span>

            </div>


            <div
                id="status"
                class="status-grid"
            >

                <div class="status-item">

                    <span class="status-label">
                        WiFi
                    </span>

                    <strong id="wifiValue">
                        ...
                    </strong>

                </div>


                <div class="status-item">

                    <span class="status-label">
                        SSID
                    </span>

                    <strong id="ssidValue">
                        ...
                    </strong>

                </div>


                <div class="status-item">

                    <span class="status-label">
                        IP
                    </span>

                    <strong id="ipValue">
                        ...
                    </strong>

                </div>


                <div class="status-item">

                    <span class="status-label">
                        Signal
                    </span>

                    <strong id="rssiValue">
                        ...
                    </strong>

                </div>


                <div class="status-item">

                    <span class="status-label">
                        Uptime
                    </span>

                    <strong id="uptimeValue">
                        ...
                    </strong>

                </div>

            </div>


            <div class="system-action">

                <button
                    class="button button-danger"
                    id="rebootButton"
                    onclick="rebootESP()"
                >
                    🔄 Redémarrer l'ESP8266
                </button>

            </div>

        </section>



        <!-- =================================================
             TEMPERATURES
             ================================================= -->

        <section class="card temperature-card">

            <div class="card-title">

                <div>
                    <span class="icon">🌡️</span>
                    <span>Températures</span>
                </div>

                <span
                    id="sensorCount"
                    class="badge"
                >
                    0 sondes
                </span>

            </div>


            <div
                id="temperatures"
                class="temperature-grid"
            >

                <div class="loading">
                    Chargement...
                </div>

            </div>

        </section>



        <!-- =================================================
             PILOTAGE
             ================================================= -->

        <section class="card control-card">

            <div class="card-title">

                <div>
                    <span class="icon">🎛️</span>
                    <span>Pilotage</span>
                </div>

            </div>


            <div class="control-grid">


                <!-- LEDs -->

                <div class="control-block">

                    <div class="control-header">

                        <span>
                            💡 LEDs
                        </span>

                        <span
                            id="ledStatus"
                            class="control-state"
                        >
                            Prêt
                        </span>

                    </div>


                    <div class="button-grid">

                        <button
                            class="button button-secondary"
                            onclick="led('off')"
                        >
                            OFF
                        </button>

                        <button
                            class="button button-success"
                            onclick="led('green')"
                        >
                            Vert
                        </button>

                        <button
                            class="button button-danger"
                            onclick="led('red')"
                        >
                            Rouge
                        </button>

                        <button
                            class="button button-warning"
                            onclick="led('orange')"
                        >
                            Orange
                        </button>

                        <button
                            class="button button-primary"
                            onclick="led('rainbow')"
                        >
                            Rainbow
                        </button>

                    </div>

                </div>



                <!-- BUZZER -->

                <div class="control-block">

                    <div class="control-header">

                        <span>
                            🔊 Buzzer
                        </span>

                        <span
                            id="buzzerStatus"
                            class="control-state"
                        >
                            Prêt
                        </span>

                    </div>


                    <div class="button-grid">

                        <button
                            class="button button-secondary"
                            onclick="buzzer('beep')"
                        >
                            Bip
                        </button>

                        <button
                            class="button button-success"
                            onclick="buzzer('success')"
                        >
                            Succès
                        </button>

                        <button
                            class="button button-primary"
                            onclick="buzzer('startup')"
                        >
                            Mélodie
                        </button>

                    </div>

                </div>

            </div>

        </section>



        <!-- =================================================
             CONSIGNES
             ================================================= -->

        <section class="card setpoint-card">

            <div class="card-title">

                <div>
                    <span class="icon">🎯</span>
                    <span>Consignes</span>
                </div>

                <span class="badge">
                    LOCAL
                </span>

            </div>


            <div
                id="setpoints"
                class="setpoint-grid"
            >

                <!-- Généré par JavaScript -->

            </div>

        </section>


    </main>



    <!-- =====================================================
         FOOTER
         ===================================================== -->

    <footer class="footer">

        <span>
            3x0c3t S0NDES
        </span>

        <span>
            ESP8266
        </span>

        <span>
            v1.2-dev
        </span>

    </footer>


</div>


<script
    src="/script.js?v=12"
    defer
></script>


</body>

</html>

)rawliteral";

#endif