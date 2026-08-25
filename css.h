#ifndef CSS_H
#define CSS_H

const char cssStyle[] PROGMEM = R"rawliteral(

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
    background: #101318;
    color: #f2f4f7;

    font-family:
        Arial,
        Helvetica,
        sans-serif;

    font-size: 16px;

    overflow-x: hidden;
}


/* ============================================================
   APPLICATION
   ============================================================ */

.app
{
    width: 100%;
    max-width: 1800px;
    min-height: 100dvh;

    margin: 0 auto;

    padding:
        clamp(6px, 1vw, 18px);

    display: flex;
    flex-direction: column;

    gap:
        clamp(6px, .8vw, 12px);
}


/* ============================================================
   HEADER
   ============================================================ */

.header
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 12px;

    padding:
        clamp(8px, 1vw, 14px)
        clamp(10px, 1.5vw, 20px);

    background: #181c22;

    border:
        1px solid #292f38;

    border-radius:
        clamp(8px, 1vw, 14px);
}

.brand
{
    min-width: 0;
}

.brand-title
{
    font-size:
        clamp(19px, 2vw, 30px);

    font-weight: 700;

    line-height: 1;
}

.brand-subtitle
{
    margin-top: 4px;

    color: #8e98a6;

    font-size:
        clamp(10px, .8vw, 13px);
}

.links
{
    display: flex;

    align-items: center;

    gap: 10px;

    white-space: nowrap;
}

.links a
{
    color: #737d89;

    text-decoration: none;

    font-size:
        clamp(9px, .8vw, 12px);
}

.links a:hover
{
    color: #ffffff;
}


/* ============================================================
   PANELS
   ============================================================ */

.panel
{
    background: #181c22;

    border:
        1px solid #292f38;

    border-radius:
        clamp(8px, 1vw, 14px);

    padding:
        clamp(9px, 1vw, 16px);

    min-width: 0;
}

.panel-title
{
    margin-bottom:
        clamp(6px, .7vw, 10px);

    font-size:
        clamp(14px, 1.3vw, 19px);

    font-weight: 700;
}


/* ============================================================
   SYSTEME
   ============================================================ */

.system-grid
{
    display: grid;

    grid-template-columns:
        minmax(0, 2fr)
        minmax(190px, 1fr);

    gap:
        clamp(6px, .8vw, 12px);
}

.system-panel
{
    display: flex;

    flex-direction: column;

    justify-content: space-between;
}

.reboot-button
{
    width: 100%;
}


/* ============================================================
   STATUS
   ============================================================ */

.status-content
{
    display: grid;

    grid-template-columns:
        repeat(4, minmax(0, 1fr));

    gap: 6px;

    color: #cbd1d8;

    font-size:
        clamp(11px, .9vw, 14px);
}

.status-content p
{
    margin: 0;

    padding: 7px;

    background: #11151a;

    border-radius: 6px;
}

.status-content strong
{
    color: #ffffff;
}

.ok
{
    color: #4ade80;

    font-weight: 700;
}

.error
{
    color: #f87171;

    font-weight: 700;
}


/* ============================================================
   BOUTONS
   ============================================================ */

.button-row
{
    display: flex;

    flex-wrap: wrap;

    gap: 6px;
}

.button
{
    appearance: none;

    border:
        1px solid #343b46;

    background: #252b33;

    color: #ffffff;

    border-radius: 7px;

    min-height: 34px;

    padding:
        5px 11px;

    font-size:
        clamp(11px, .9vw, 14px);

    cursor: pointer;

    transition:
        background .15s,
        transform .1s;
}

.button:hover
{
    background: #303743;
}

.button:active
{
    transform: scale(.97);
}

.button-danger
{
    background: #7f2525;

    border-color:
        #a33434;
}

.button-danger:hover
{
    background: #9a2d2d;
}

.button-blue
{
    border-color: #245b91;
}

.button-green
{
    border-color: #287447;
}

.button-red
{
    border-color: #873131;
}

.button-orange
{
    border-color: #966127;
}


/* ============================================================
   PILOTAGE
   ============================================================ */

.control-groups
{
    display: grid;

    grid-template-columns:
        repeat(2, minmax(0, 1fr));

    gap:
        clamp(8px, 1vw, 16px);
}

.control-label
{
    color: #9da7b3;

    font-size:
        clamp(11px, .8vw, 13px);

    margin-bottom: 6px;
}


/* ============================================================
   RAFRAICHISSEMENT
   ============================================================ */

.refresh-settings
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 12px;
}

.refresh-description
{
    color: #7f8996;

    font-size:
        clamp(10px, .8vw, 13px);
}

.refresh-control
{
    display: flex;

    align-items: center;

    justify-content: flex-end;

    gap: 7px;

    white-space: nowrap;
}

.refresh-control label
{
    color: #9da7b3;

    font-size:
        clamp(11px, .8vw, 13px);
}

.refresh-control input
{
    width: 65px;

    height: 34px;

    padding:
        5px 8px;

    border:
        1px solid #343b46;

    border-radius: 7px;

    background: #11151a;

    color: #ffffff;

    text-align: center;

    font-size: 14px;
}

.refresh-control span
{
    color: #9da7b3;

    font-size:
        clamp(10px, .8vw, 13px);
}


/* ============================================================
   SONDES
   ============================================================ */

.sensor-grid
{
    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(220px, 1fr)
        );

    gap:
        clamp(6px, .8vw, 12px);
}

.sensor-card
{
    background: #11151a;

    border:
        1px solid #292f38;

    border-radius: 9px;

    padding:
        clamp(9px, 1vw, 14px);

    min-width: 0;
}

.sensor-header
{
    display: flex;

    align-items: center;

    justify-content: space-between;

    gap: 8px;

    margin-bottom: 6px;
}

.sensor-name
{
    font-weight: 700;

    font-size:
        clamp(13px, 1.1vw, 16px);
}

.sensor-state
{
    font-size:
        clamp(9px, .7vw, 11px);

    font-weight: 700;
}

.sensor-temperature
{
    font-size:
        clamp(25px, 2.8vw, 42px);

    font-weight: 700;

    line-height: 1;

    margin:
        7px 0 10px;
}

.sensor-setpoint
{
    display: flex;

    align-items: center;

    justify-content: space-between;

    gap: 8px;

    padding-top: 7px;

    border-top:
        1px solid #252b33;
}

.setpoint-label
{
    color: #8e98a6;

    font-size:
        clamp(10px, .8vw, 12px);
}

.setpoint-value
{
    font-size:
        clamp(15px, 1.3vw, 20px);

    font-weight: 700;
}

.setpoint-buttons
{
    display: flex;

    gap: 5px;
}

.setpoint-button
{
    width: 34px;
    height: 34px;

    border: 0;

    border-radius: 6px;

    background: #252b33;

    color: #ffffff;

    font-size: 19px;

    cursor: pointer;
}

.setpoint-button:hover
{
    background: #343b46;
}

.sensor-ok
{
    color: #4ade80;
}

.sensor-low
{
    color: #60a5fa;
}

.sensor-high
{
    color: #f87171;
}


/* ============================================================
   FOOTER
   ============================================================ */

.footer
{
    display: flex;

    justify-content: space-between;

    color: #626c78;

    font-size:
        clamp(8px, .7vw, 10px);

    padding:
        2px 4px;
}


/* ============================================================
   TABLET
   ============================================================ */

@media (max-width: 900px)
{
    .system-grid
    {
        grid-template-columns: 1fr;
    }

    .status-content
    {
        grid-template-columns:
            repeat(2, minmax(0, 1fr));
    }

    .control-groups
    {
        grid-template-columns: 1fr;
    }
}


/* ============================================================
   MOBILE
   ============================================================ */

@media (max-width: 600px)
{
    .app
    {
        padding: 5px;

        gap: 5px;
    }

    .header
    {
        padding: 7px 9px;
    }

    .links
    {
        gap: 6px;
    }

    .panel
    {
        padding: 8px;
    }

    .status-content
    {
        gap: 4px;
    }

    .status-content p
    {
        padding: 5px;
    }

    .button
    {
        min-height: 32px;

        padding:
            4px 8px;
    }

    .refresh-settings
    {
        align-items: flex-start;

        flex-direction: column;
    }

    .refresh-control
    {
        width: 100%;

        justify-content: flex-start;

        flex-wrap: wrap;
    }

    .sensor-grid
    {
        grid-template-columns:
            repeat(2, minmax(0, 1fr));

        gap: 5px;
    }

    .sensor-card
    {
        padding: 7px;
    }

    .sensor-temperature
    {
        font-size: 27px;

        margin:
            5px 0 8px;
    }

    .setpoint-button
    {
        width: 31px;
        height: 31px;
    }
}


/* ============================================================
   PETITS MOBILES
   ============================================================ */

@media (max-width: 380px)
{
    .brand-title
    {
        font-size: 17px;
    }

    .brand-subtitle
    {
        display: none;
    }

    .links a
    {
        font-size: 8px;
    }

    .sensor-grid
    {
        grid-template-columns: 1fr;
    }

    .status-content
    {
        grid-template-columns: 1fr;
    }
}


/* ============================================================
   TV / GRAND ECRAN
   ============================================================ */

@media (min-width: 1400px)
{
    .sensor-grid
    {
        grid-template-columns:
            repeat(4, minmax(0, 1fr));
    }
}


/* ============================================================
   PAYSAGE MOBILE / ECRAN BAS
   ============================================================ */

@media
    (max-height: 600px)
    and
    (orientation: landscape)
{
    .app
    {
        gap: 4px;
    }

    .header
    {
        padding:
            5px 8px;
    }

    .panel
    {
        padding: 6px;
    }

    .panel-title
    {
        margin-bottom: 4px;
    }

    .sensor-temperature
    {
        font-size: 23px;

        margin:
            3px 0 6px;
    }

    .button
    {
        min-height: 29px;

        padding:
            3px 7px;
    }
}

)rawliteral";

#endif