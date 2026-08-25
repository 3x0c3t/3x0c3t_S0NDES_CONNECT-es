#ifndef CSS_H
#define CSS_H

const char CSS_PAGE[] PROGMEM = R"rawliteral(

/* ============================================================
   RESET
   ============================================================ */

*,
*::before,
*::after
{
    box-sizing: border-box;
}

html,
body
{
    margin: 0;
    padding: 0;
    width: 100%;
    min-height: 100%;
}

body
{
    font-family: Arial, Helvetica, sans-serif;
    background: #101214;
    color: #f1f1f1;
}


/* ============================================================
   PAGE
   ============================================================ */

.page
{
    width: 100%;
    min-height: 100vh;

    display: flex;
    flex-direction: column;

    padding: clamp(8px, 1.5vw, 24px);
    gap: clamp(8px, 1.2vw, 18px);
}


/* ============================================================
   HEADER
   ============================================================ */

.header
{
    width: 100%;

    display: flex;
    align-items: center;
    justify-content: space-between;

    gap: 12px;

    padding: clamp(10px, 1.5vw, 18px);

    background: #181b1f;
    border: 1px solid #2d3238;
    border-radius: 12px;
}

.header-title
{
    font-size: clamp(18px, 2vw, 30px);
    font-weight: bold;
}

.header-links
{
    display: flex;
    gap: 10px;

    font-size: clamp(10px, 1vw, 14px);
}

.header-links a
{
    color: #8ea7ff;
    text-decoration: none;
    opacity: 0.8;
}

.header-links a:hover
{
    opacity: 1;
    text-decoration: underline;
}


/* ============================================================
   STATUS WIFI
   ============================================================ */

.status-row
{
    width: 100%;

    display: grid;

    grid-template-columns: minmax(0, 1fr) auto;

    gap: 12px;
}

.status
{
    min-width: 0;

    padding: clamp(10px, 1.3vw, 18px);

    background: #181b1f;
    border: 1px solid #2d3238;
    border-radius: 12px;
}

.status p
{
    margin: 4px 0;

    font-size: clamp(12px, 1.2vw, 17px);
}


/* ============================================================
   BOUTONS
   ============================================================ */

button
{
    border: 0;
    border-radius: 8px;

    padding: 10px 16px;

    font-size: clamp(12px, 1vw, 15px);

    cursor: pointer;

    background: #30363d;
    color: white;
}

button:hover
{
    filter: brightness(1.2);
}

button:active
{
    transform: scale(0.98);
}

.btn-reboot
{
    align-self: stretch;

    min-width: 110px;

    background: #9b2c2c;
}


/* ============================================================
   CONTENU PRINCIPAL
   ============================================================ */

.main
{
    width: 100%;

    display: grid;

    grid-template-columns:
        minmax(0, 1fr)
        minmax(0, 1fr);

    gap: clamp(8px, 1.2vw, 18px);

    flex: 1;
}


/* ============================================================
   BLOCS
   ============================================================ */

.panel
{
    min-width: 0;

    padding: clamp(10px, 1.4vw, 20px);

    background: #181b1f;
    border: 1px solid #2d3238;
    border-radius: 12px;
}

.panel-title
{
    margin: 0 0 12px 0;

    font-size: clamp(16px, 1.5vw, 22px);
}


/* ============================================================
   TEMPERATURES
   ============================================================ */

#temperatures
{
    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(110px, 1fr)
        );

    gap: clamp(8px, 1vw, 14px);
}

.temperature
{
    min-width: 0;

    padding: clamp(10px, 1.2vw, 18px);

    text-align: center;

    background: #22272e;

    border-radius: 10px;

    font-size: clamp(15px, 1.5vw, 24px);

    font-weight: bold;
}


/* ============================================================
   PILOTAGE
   ============================================================ */

.controls
{
    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(100px, 1fr)
        );

    gap: 8px;
}

.controls button
{
    width: 100%;
}


/* ============================================================
   CONSIGNES
   ============================================================ */

.setpoints
{
    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(130px, 1fr)
        );

    gap: 10px;

    margin-top: 12px;
}

.sensor
{
    padding: 12px;

    background: #22272e;

    border-radius: 10px;
}

.sensor-title
{
    margin-bottom: 8px;

    font-weight: bold;

    font-size: clamp(13px, 1.1vw, 17px);
}

.sensor input
{
    width: 100%;

    padding: 8px;

    border: 1px solid #444b53;
    border-radius: 6px;

    background: #101214;
    color: white;

    font-size: 16px;
}


/* ============================================================
   ETATS
   ============================================================ */

.ok
{
    color: #55d66f;
    font-weight: bold;
}

.error
{
    color: #ff6464;
    font-weight: bold;
}


/* ============================================================
   FOOTER
   ============================================================ */

.footer
{
    text-align: center;

    font-size: clamp(9px, 0.8vw, 12px);

    opacity: 0.5;

    padding: 4px;
}


/* ============================================================
   MOBILE
   ============================================================ */

@media (max-width: 700px)
{
    .page
    {
        padding: 6px;
        gap: 6px;
    }

    .header
    {
        flex-direction: column;
        align-items: stretch;
        text-align: center;
    }

    .header-links
    {
        justify-content: center;
    }

    .status-row
    {
        grid-template-columns: 1fr;
    }

    .btn-reboot
    {
        width: 100%;
        min-height: 42px;
    }

    .main
    {
        grid-template-columns: 1fr;
    }
}


/* ============================================================
   PETITS ECRANS
   ============================================================ */

@media (max-width: 420px)
{
    .page
    {
        padding: 4px;
        gap: 4px;
    }

    .header,
    .status,
    .panel
    {
        border-radius: 8px;
        padding: 9px;
    }

    .temperature
    {
        padding: 9px;
        font-size: 16px;
    }
}


/* ============================================================
   TV / GRAND ECRAN
   ============================================================ */

@media (min-width: 1600px)
{
    .page
    {
        max-width: 1800px;
        margin: auto;
    }
}

)rawliteral";

#endif