#ifndef CSS_H
#define CSS_H

const char CSS_PAGE[] PROGMEM = R"rawliteral(

/* =========================================================
   RESET
   ========================================================= */

* {
    box-sizing: border-box;
}

html {
    margin: 0;
    padding: 0;
    width: 100%;
    min-height: 100%;
}

body {
    margin: 0;
    padding: 0;

    width: 100%;
    min-height: 100vh;

    font-family:
        system-ui,
        -apple-system,
        BlinkMacSystemFont,
        "Segoe UI",
        sans-serif;

    background: #f1f3f6;
    color: #1f2933;

    -webkit-text-size-adjust: 100%;
}



/* =========================================================
   APP
   ========================================================= */

.app {
    width: 100%;
    min-height: 100vh;

    display: flex;
    flex-direction: column;
}



/* =========================================================
   HEADER
   ========================================================= */

.header {
    width: 100%;

    padding:
        max(14px, env(safe-area-inset-top))
        16px
        14px
        16px;

    background: #111827;
    color: white;

    display: flex;
    flex-direction: column;
    gap: 10px;
}


.header-title {
    display: flex;
    align-items: center;
    justify-content: space-between;
    gap: 10px;
}


.header h1 {
    margin: 0;

    font-size: 1.25rem;
    font-weight: 700;

    line-height: 1.2;
}


.version {
    padding: 4px 8px;

    border-radius: 6px;

    background: #374151;

    font-size: 0.7rem;
    font-weight: 700;
}


.connection {
    display: flex;
    align-items: center;
    gap: 8px;

    font-size: 0.8rem;
    color: #d1d5db;
}


.status-dot {
    width: 9px;
    height: 9px;

    border-radius: 50%;

    background: #22c55e;

    flex: 0 0 auto;
}



/* =========================================================
   MAIN
   ========================================================= */

.main {
    width: min(100% - 20px, 1200px);

    margin: 0 auto;

    padding: 10px 0 20px;

    display: grid;

    grid-template-columns: 1fr;

    gap: 10px;
}



/* =========================================================
   CARD
   ========================================================= */

.card {
    width: 100%;

    background: white;

    border: 1px solid #e5e7eb;

    border-radius: 12px;

    padding: 14px;

    box-shadow:
        0 2px 6px rgba(0, 0, 0, 0.05);
}


.card-header {
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 10px;

    margin-bottom: 14px;
}


.card-header > div {
    display: flex;
    align-items: center;
    gap: 8px;
}


.card-icon {
    font-size: 1.2rem;
}


.card h2 {
    margin: 0;

    font-size: 1rem;
    font-weight: 700;
}



/* =========================================================
   BADGES
   ========================================================= */

.badge {
    display: inline-flex;

    align-items: center;
    justify-content: center;

    padding: 4px 7px;

    border-radius: 5px;

    background: #e5e7eb;
    color: #374151;

    font-size: 0.65rem;
    font-weight: 700;
}


.badge-ok {
    background: #dcfce7;
    color: #166534;
}



/* =========================================================
   TEMPERATURES
   ========================================================= */

.temperature-grid {
    display: grid;

    grid-template-columns: repeat(2, minmax(0, 1fr));

    gap: 8px;
}


.sensor {
    min-width: 0;

    padding: 12px;

    border-radius: 9px;

    background: #f8fafc;

    border: 1px solid #e5e7eb;
}


.sensor-header {
    display: flex;

    justify-content: space-between;
    align-items: center;

    gap: 5px;

    margin-bottom: 7px;
}


.sensor-name {
    font-size: 0.75rem;
    font-weight: 700;

    color: #4b5563;
}


.sensor-state {
    font-size: 0.6rem;
    font-weight: 700;

    color: #16a34a;
}


.sensor-value {
    display: flex;
    align-items: baseline;

    white-space: nowrap;

    font-size: clamp(1.35rem, 7vw, 2rem);

    font-weight: 700;

    line-height: 1;
}


.unit {
    margin-left: 3px;

    font-size: 0.8rem;
    font-weight: 500;

    color: #6b7280;
}



/* =========================================================
   INFO WIFI
   ========================================================= */

.info-grid {
    display: grid;

    grid-template-columns: 1fr 1fr;

    gap: 8px;
}


.info-item {
    min-width: 0;

    padding: 10px;

    background: #f8fafc;

    border-radius: 8px;

    border: 1px solid #e5e7eb;
}


.info-label {
    display: block;

    margin-bottom: 4px;

    color: #6b7280;

    font-size: 0.65rem;
    font-weight: 600;
}


.info-value {
    display: block;

    overflow: hidden;

    text-overflow: ellipsis;
    white-space: nowrap;

    font-size: 0.8rem;
    font-weight: 600;
}



/* =========================================================
   CONTROLES
   ========================================================= */

.control-group {
    padding: 12px 0;

    border-top: 1px solid #e5e7eb;
}


.control-group:first-child {
    border-top: 0;
}


.control-label {
    display: flex;

    justify-content: space-between;
    align-items: center;

    gap: 10px;

    margin-bottom: 9px;
}


.control-title {
    font-size: 0.85rem;
    font-weight: 700;
}


.control-status {
    font-size: 0.65rem;

    color: #6b7280;
}


.button-group {
    display: grid;

    grid-template-columns:
        repeat(3, minmax(0, 1fr));

    gap: 7px;
}



/* =========================================================
   BOUTONS
   ========================================================= */

.button {
    min-height: 42px;

    padding: 8px 10px;

    border: 0;
    border-radius: 8px;

    font-family: inherit;

    font-size: 0.75rem;
    font-weight: 700;

    cursor: pointer;

    transition:
        transform 0.08s ease,
        opacity 0.15s ease;
}


.button:active {
    transform: scale(0.97);
}


.button:disabled {
    opacity: 0.5;

    cursor: not-allowed;
}


.button-primary {
    background: #2563eb;
    color: white;
}


.button-success {
    background: #16a34a;
    color: white;
}


.button-warning {
    background: #f59e0b;
    color: white;
}


.button-danger {
    background: #dc2626;
    color: white;
}


.button-secondary {
    background: #e5e7eb;
    color: #374151;
}



/* =========================================================
   CONSIGNES
   ========================================================= */

.setpoints {
    display: grid;

    grid-template-columns: 1fr;

    gap: 8px;
}


.setpoint {
    display: grid;

    grid-template-columns:
        35px
        minmax(0, 1fr)
        48px;

    align-items: center;

    gap: 7px;
}


.setpoint label {
    font-size: 0.8rem;
    font-weight: 700;
}


.input-unit {
    position: relative;

    min-width: 0;
}


.input-unit input {
    width: 100%;

    height: 42px;

    padding:
        8px
        35px
        8px
        10px;

    border:
        1px solid #d1d5db;

    border-radius: 8px;

    background: white;

    color: #111827;

    font-family: inherit;

    font-size: 0.9rem;
}


.input-unit span {
    position: absolute;

    right: 10px;
    top: 50%;

    transform: translateY(-50%);

    color: #6b7280;

    font-size: 0.7rem;

    pointer-events: none;
}


.setpoint .button {
    min-height: 42px;

    padding: 5px;
}



/* =========================================================
   ALERTES
   ========================================================= */

.alert-list {
    display: flex;

    flex-direction: column;
}


.alert-row {
    min-height: 58px;

    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 12px;

    padding: 9px 0;

    border-top: 1px solid #e5e7eb;
}


.alert-row:first-child {
    border-top: 0;
}


.alert-title {
    display: block;

    font-size: 0.8rem;
    font-weight: 700;
}


.alert-description {
    display: block;

    margin-top: 2px;

    color: #6b7280;

    font-size: 0.65rem;
}



/* =========================================================
   SWITCH
   ========================================================= */

.switch {
    position: relative;

    display: block;

    width: 44px;
    height: 24px;

    flex: 0 0 auto;
}


.switch input {
    position: absolute;

    opacity: 0;

    width: 0;
    height: 0;
}


.slider {
    position: absolute;

    inset: 0;

    background: #d1d5db;

    border-radius: 999px;

    cursor: pointer;

    transition: 0.2s;
}


.slider::before {
    content: "";

    position: absolute;

    width: 18px;
    height: 18px;

    left: 3px;
    top: 3px;

    background: white;

    border-radius: 50%;

    box-shadow:
        0 1px 3px rgba(0, 0, 0, 0.2);

    transition: 0.2s;
}


.switch input:checked + .slider {
    background: #2563eb;
}


.switch input:checked + .slider::before {
    transform: translateX(20px);
}



/* =========================================================
   SYSTÈME
   ========================================================= */

.system-actions {
    display: grid;

    grid-template-columns: 1fr;

    gap: 8px;
}


.system-actions .button {
    width: 100%;
}



/* =========================================================
   FOOTER
   ========================================================= */

.footer {
    width: min(100% - 20px, 1200px);

    margin: auto auto 0;

    padding:
        10px
        0
        max(14px, env(safe-area-inset-bottom));

    display: flex;

    flex-direction: column;

    align-items: center;

    gap: 3px;

    color: #6b7280;

    font-size: 0.6rem;

    text-align: center;
}



/* =========================================================
   TABLETTE
   ========================================================= */

@media (min-width: 600px) {

    .header {
        padding-left: 24px;
        padding-right: 24px;

        flex-direction: row;

        align-items: center;
        justify-content: space-between;
    }


    .main {
        width: min(100% - 32px, 1200px);

        padding-top: 16px;

        grid-template-columns:
            repeat(2, minmax(0, 1fr));
    }


    .temperatures-card {
        grid-column: 1 / -1;
    }


    .temperature-grid {
        grid-template-columns:
            repeat(4, minmax(0, 1fr));
    }


    .setpoints {
        grid-template-columns:
            repeat(2, minmax(0, 1fr));
    }


    .system-card {
        grid-column: 1 / -1;
    }


    .system-actions {
        grid-template-columns: 1fr 1fr;
    }


    .footer {
        width: min(100% - 32px, 1200px);

        flex-direction: row;

        justify-content: space-between;
    }
}



/* =========================================================
   DESKTOP
   ========================================================= */

@media (min-width: 900px) {

    .header {
        padding-left: 32px;
        padding-right: 32px;
    }


    .header h1 {
        font-size: 1.4rem;
    }


    .main {
        width: min(100% - 48px, 1200px);

        padding-top: 20px;
        padding-bottom: 24px;

        grid-template-columns:
            repeat(3, minmax(0, 1fr));

        gap: 14px;
    }


    .temperatures-card {
        grid-column: 1 / -1;
    }


    .system-card {
        grid-column: 1 / -1;
    }


    .card {
        padding: 16px;
    }


    .sensor-value {
        font-size: 2rem;
    }


    .setpoints {
        grid-template-columns: 1fr;
    }


    .footer {
        width: min(100% - 48px, 1200px);
    }
}



/* =========================================================
   GRAND ÉCRAN
   ========================================================= */

@media (min-width: 1200px) {

    .main {
        grid-template-columns:
            repeat(4, minmax(0, 1fr));
    }


    .temperatures-card {
        grid-column: 1 / -1;
    }


    .temperatures-card {
        padding-bottom: 18px;
    }


    .system-card {
        grid-column: 1 / -1;
    }
}



/* =========================================================
   ACCESSIBILITÉ
   ========================================================= */

@media (prefers-reduced-motion: reduce) {

    *,
    *::before,
    *::after {
        scroll-behavior: auto !important;

        transition: none !important;

        animation: none !important;
    }
}



/* =========================================================
   PETITS ÉCRANS
   ========================================================= */

@media (max-width: 360px) {

    .main {
        width: min(100% - 12px, 1200px);
    }


    .card {
        padding: 11px;
    }


    .temperature-grid {
        gap: 6px;
    }


    .sensor {
        padding: 9px;
    }


    .sensor-value {
        font-size: 1.25rem;
    }


    .button {
        font-size: 0.68rem;
    }


    .setpoint {
        grid-template-columns:
            28px
            minmax(0, 1fr)
            42px;
    }
}

)rawliteral";

#endif