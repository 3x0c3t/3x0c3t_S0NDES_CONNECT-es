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

    <title>3x0c3t S0NDES</title>

    <link rel="stylesheet" href="/style.css">
</head>

<body>

<div class="app">

    <!-- =====================================================
         HEADER
         ===================================================== -->

    <header class="header">

        <div class="header-title">
            <h1>3x0c3t S0NDES</h1>
            <span class="version">v1.2 DEV</span>
        </div>

        <div class="connection">
            <span id="connection-dot" class="status-dot"></span>
            <span id="connection-status">ESP8266</span>
        </div>

    </header>


    <!-- =====================================================
         CONTENU PRINCIPAL
         ===================================================== -->

    <main class="main">


        <!-- =================================================
             TEMPÉRATURES
             ================================================= -->

        <section class="card temperatures-card">

            <div class="card-header">
                <div>
                    <span class="card-icon">🌡️</span>
                    <h2>Températures</h2>
                </div>

                <span id="temperature-state" class="badge">
                    ACTIF
                </span>
            </div>


            <div id="temperatures" class="temperature-grid">

                <!-- S1 -->
                <article class="sensor">

                    <div class="sensor-header">
                        <span class="sensor-name">S1</span>
                        <span class="sensor-state">OK</span>
                    </div>

                    <div class="sensor-value">
                        <span id="temp-1">--.--</span>
                        <span class="unit">°C</span>
                    </div>

                </article>


                <!-- S2 -->
                <article class="sensor">

                    <div class="sensor-header">
                        <span class="sensor-name">S2</span>
                        <span class="sensor-state">OK</span>
                    </div>

                    <div class="sensor-value">
                        <span id="temp-2">--.--</span>
                        <span class="unit">°C</span>
                    </div>

                </article>


                <!-- S3 -->
                <article class="sensor">

                    <div class="sensor-header">
                        <span class="sensor-name">S3</span>
                        <span class="sensor-state">OK</span>
                    </div>

                    <div class="sensor-value">
                        <span id="temp-3">--.--</span>
                        <span class="unit">°C</span>
                    </div>

                </article>


                <!-- S4 -->
                <article class="sensor">

                    <div class="sensor-header">
                        <span class="sensor-name">S4</span>
                        <span class="sensor-state">OK</span>
                    </div>

                    <div class="sensor-value">
                        <span id="temp-4">--.--</span>
                        <span class="unit">°C</span>
                    </div>

                </article>

            </div>

        </section>



        <!-- =================================================
             WIFI
             ================================================= -->

        <section class="card">

            <div class="card-header">

                <div>
                    <span class="card-icon">📡</span>
                    <h2>Connexion</h2>
                </div>

                <span id="wifi-status" class="badge badge-ok">
                    CONNECTÉ
                </span>

            </div>


            <div class="info-grid">

                <div class="info-item">

                    <span class="info-label">
                        SSID
                    </span>

                    <span
                        id="wifi-ssid"
                        class="info-value"
                    >
                        --
                    </span>

                </div>


                <div class="info-item">

                    <span class="info-label">
                        Adresse IP
                    </span>

                    <span
                        id="wifi-ip"
                        class="info-value"
                    >
                        --
                    </span>

                </div>


                <div class="info-item">

                    <span class="info-label">
                        Signal
                    </span>

                    <span
                        id="wifi-rssi"
                        class="info-value"
                    >
                        -- dBm
                    </span>

                </div>


                <div class="info-item">

                    <span class="info-label">
                        Hostname
                    </span>

                    <span
                        id="wifi-hostname"
                        class="info-value"
                    >
                        --
                    </span>

                </div>

            </div>

        </section>



        <!-- =================================================
             PILOTAGE
             ================================================= -->

        <section class="card control-card">

            <div class="card-header">

                <div>
                    <span class="card-icon">🎛️</span>
                    <h2>Pilotage</h2>
                </div>

            </div>


            <!-- LED -->

            <div class="control-group">

                <div class="control-label">

                    <span class="control-title">
                        LED
                    </span>

                    <span
                        id="led-state"
                        class="control-status"
                    >
                        ÉTEINTE
                    </span>

                </div>


                <div class="button-group">

                    <button
                        id="led-on"
                        class="button button-success"
                        type="button"
                    >
                        ON
                    </button>

                    <button
                        id="led-off"
                        class="button button-secondary"
                        type="button"
                    >
                        OFF
                    </button>

                    <button
                        id="led-test"
                        class="button button-secondary"
                        type="button"
                    >
                        TEST
                    </button>

                </div>

            </div>



            <!-- BUZZER -->

            <div class="control-group">

                <div class="control-label">

                    <span class="control-title">
                        Buzzer
                    </span>

                    <span
                        id="buzzer-state"
                        class="control-status"
                    >
                        INACTIF
                    </span>

                </div>


                <div class="button-group">

                    <button
                        id="buzzer-test"
                        class="button button-warning"
                        type="button"
                    >
                        🔊 TEST
                    </button>

                    <button
                        id="buzzer-off"
                        class="button button-secondary"
                        type="button"
                    >
                        STOP
                    </button>

                </div>

            </div>

        </section>



        <!-- =================================================
             CONSIGNES
             ================================================= -->

        <section class="card">

            <div class="card-header">

                <div>
                    <span class="card-icon">🎯</span>
                    <h2>Consignes</h2>
                </div>

            </div>


            <div class="setpoints">


                <!-- CONSIGNE S1 -->

                <div class="setpoint">

                    <label for="setpoint-1">
                        S1
                    </label>

                    <div class="input-unit">

                        <input
                            id="setpoint-1"
                            type="number"
                            step="0.1"
                            value="20.0"
                        >

                        <span>°C</span>

                    </div>

                    <button
                        class="button button-primary setpoint-save"
                        data-sensor="1"
                        type="button"
                    >
                        OK
                    </button>

                </div>



                <!-- CONSIGNE S2 -->

                <div class="setpoint">

                    <label for="setpoint-2">
                        S2
                    </label>

                    <div class="input-unit">

                        <input
                            id="setpoint-2"
                            type="number"
                            step="0.1"
                            value="20.0"
                        >

                        <span>°C</span>

                    </div>

                    <button
                        class="button button-primary setpoint-save"
                        data-sensor="2"
                        type="button"
                    >
                        OK
                    </button>

                </div>



                <!-- CONSIGNE S3 -->

                <div class="setpoint">

                    <label for="setpoint-3">
                        S3
                    </label>

                    <div class="input-unit">

                        <input
                            id="setpoint-3"
                            type="number"
                            step="0.1"
                            value="20.0"
                        >

                        <span>°C</span>

                    </div>

                    <button
                        class="button button-primary setpoint-save"
                        data-sensor="3"
                        type="button"
                    >
                        OK
                    </button>

                </div>



                <!-- CONSIGNE S4 -->

                <div class="setpoint">

                    <label for="setpoint-4">
                        S4
                    </label>

                    <div class="input-unit">

                        <input
                            id="setpoint-4"
                            type="number"
                            step="0.1"
                            value="20.0"
                        >

                        <span>°C</span>

                    </div>

                    <button
                        class="button button-primary setpoint-save"
                        data-sensor="4"
                        type="button"
                    >
                        OK
                    </button>

                </div>

            </div>

        </section>



        <!-- =================================================
             ALERTES
             ================================================= -->

        <section class="card">

            <div class="card-header">

                <div>
                    <span class="card-icon">⚠️</span>
                    <h2>Alertes</h2>
                </div>

            </div>


            <div class="alert-list">


                <!-- ALERTE TEMPÉRATURE HAUTE -->

                <div class="alert-row">

                    <div>

                        <span class="alert-title">
                            Température haute
                        </span>

                        <span class="alert-description">
                            Déclenchement au-dessus de la consigne
                        </span>

                    </div>


                    <label class="switch">

                        <input
                            id="alert-high"
                            type="checkbox"
                            checked
                        >

                        <span class="slider"></span>

                    </label>

                </div>



                <!-- ALERTE TEMPÉRATURE BASSE -->

                <div class="alert-row">

                    <div>

                        <span class="alert-title">
                            Température basse
                        </span>

                        <span class="alert-description">
                            Déclenchement sous la consigne
                        </span>

                    </div>


                    <label class="switch">

                        <input
                            id="alert-low"
                            type="checkbox"
                            checked
                        >

                        <span class="slider"></span>

                    </label>

                </div>



                <!-- ALERTE BUZZER -->

                <div class="alert-row">

                    <div>

                        <span class="alert-title">
                            Alerte sonore
                        </span>

                        <span class="alert-description">
                            Utiliser le buzzer en cas d'alerte
                        </span>

                    </div>


                    <label class="switch">

                        <input
                            id="alert-buzzer"
                            type="checkbox"
                            checked
                        >

                        <span class="slider"></span>

                    </label>

                </div>



                <!-- ALERTE LED -->

                <div class="alert-row">

                    <div>

                        <span class="alert-title">
                            Alerte LED
                        </span>

                        <span class="alert-description">
                            Utiliser la LED en cas d'alerte
                        </span>

                    </div>


                    <label class="switch">

                        <input
                            id="alert-led"
                            type="checkbox"
                            checked
                        >

                        <span class="slider"></span>

                    </label>

                </div>

            </div>

        </section>



        <!-- =================================================
             SYSTÈME
             ================================================= -->

        <section class="card system-card">

            <div class="card-header">

                <div>
                    <span class="card-icon">⚙️</span>
                    <h2>Système</h2>
                </div>

            </div>


            <div class="system-actions">

                <button
                    id="refresh"
                    class="button button-secondary"
                    type="button"
                >
                    🔄 Actualiser
                </button>


                <button
                    id="reboot"
                    class="button button-danger"
                    type="button"
                >
                    ⟳ Redémarrer l'ESP
                </button>

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
            v1.2 DEV
        </span>

        <span id="last-update">
            Dernière mise à jour : --
        </span>

    </footer>

</div>


<script src="/script.js"></script>

</body>
</html>
)rawliteral";

#endif