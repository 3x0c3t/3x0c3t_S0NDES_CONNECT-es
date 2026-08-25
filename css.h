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
        clamp(8px, 1.2vw, 20px);

    display: flex;
    flex-direction: column;

    gap:
        clamp(8px, 1vw, 16px);
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

    border: 1px solid #292f38;

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
        clamp(20px, 2.2vw, 32px);

    font-weight: 700;

    line-height: 1;
}


.brand-subtitle
{
    margin-top: 4px;

    color: #8e98a6;

    font-size:
        clamp(10px, 1vw, 13px);
}


.links
{
    display: flex;

    align-items: center;

    gap: 12px;

    white-space: nowrap;
}


.links a
{
    color: #7f8b99;

    text-decoration: none;

    font-size:
        clamp(10px, .9vw, 13px);
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

    border: 1px solid #292f38;

    border-radius:
        clamp(8px, 1vw, 14px);

    padding:
        clamp(10px, 1.2vw, 18px);

    min-width: 0;
}


.panel-title
{
    margin-bottom:
        clamp(8px, .8vw, 12px);

    font-size:
        clamp(14px, 1.4vw, 20px);

    font-weight: 700;
}


/* ============================================================
   SYSTEM
   ============================================================ */

.system-grid
{
    display: grid;

    grid-template-columns:
        minmax(0, 2fr)
        minmax(180px, 1fr);

    gap:
        clamp(8px, 1vw, 16px);
}


.status-content
{
    display: grid;

    grid-template-columns:
        repeat(4, minmax(0, 1fr));

    gap: 8px;

    color: #cbd1d8;

    font-size:
        clamp(12px, 1vw, 15px);
}


.status-content p
{
    margin: 0;

    padding: 8px;

    background: #11151a;

    border-radius: 7px;
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
   BUTTONS
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

    border: 1px solid #343b46;

    background: #252b33;

    color: #ffffff;

    border-radius: 7px;

    min-height: 36px;

    padding:
        6px 12px;

    font-size:
        clamp(12px, 1vw, 15px);

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
    border-color: #a33434;
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
        clamp(10px, 1vw, 18px);
}


.control-group
{
    min-width: 0;
}


.control-label
{
    color: #9da7b3;

    font-size:
        clamp(11px, .9vw, 14px);

    margin-bottom: 7px;
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
            minmax(
                220px,
                1fr
            )
        );

    gap:
        clamp(8px, 1vw, 14px);
}


.sensor-card
{
    background: #11151a;

    border: 1px solid #292f38;

    border-radius: 9px;

    padding:
        clamp(10px, 1vw, 16px);

    min-width: 0;
}


.sensor-header
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 8px;

    margin-bottom: 8px;
}


.sensor-name
{
    font-weight: 700;

    font-size:
        clamp(13px, 1.2vw, 17px);
}


.sensor-state
{
    font-size:
        clamp(10px, .8vw, 12px);
}


.sensor-temperature
{
    font-size:
        clamp(26px, 3vw, 46px);

    font-weight: 700;

    line-height: 1;

    margin:
        8px 0 14px;
}


.sensor-setpoint
{
    display: flex;

    align-items: center;

    justify-content: space-between;

    gap: 8px;
}


.setpoint-value
{
    font-size:
        clamp(15px, 1.4vw, 21px);

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

    font-size: 20px;

    cursor: pointer;
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
        clamp(9px, .75vw, 11px);

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
        padding: 6px;

        gap: 6px;
    }


    .header
    {
        padding: 8px 10px;
    }


    .links
    {
        gap: 7px;
    }


    .system-grid
    {
        gap: 6px;
    }


    .panel
    {
        padding: 9px;
    }


    .panel-title
    {
        margin-bottom: 7px;
    }


    .status-content
    {
        grid-template-columns: 1fr 1fr;

        gap: 5px;
    }


    .status-content p
    {
        padding: 6px;
    }


    .button
    {
        min-height: 34px;

        padding: 5px 9px;
    }


    .sensor-grid
    {
        grid-template-columns:
            repeat(2, minmax(0, 1fr));

        gap: 6px;
    }


    .sensor-card
    {
        padding: 8px;
    }


    .sensor-temperature
    {
        font-size: 28px;

        margin:
            6px 0 10px;
    }

}


/* ============================================================
   TRES PETITS ECRANS
   ============================================================ */

@media (max-width: 380px)
{

    .brand-title
    {
        font-size: 18px;
    }


    .brand-subtitle
    {
        display: none;
    }


    .links a
    {
        font-size: 9px;
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
   ECRANS TV / GRAND FORMAT
   ============================================================ */

@media (min-width: 1400px)
{

    .app
    {
        max-width: 1800px;
    }


    .system-grid
    {
        grid-template-columns:
            minmax(0, 3fr)
            minmax(280px, 1fr);
    }


    .sensor-grid
    {
        grid-template-columns:
            repeat(
                4,
                minmax(0, 1fr)
            );
    }

}


/* ============================================================
   MODE PAYSAGE MOBILE
   ============================================================ */

@media
    (max-height: 600px)
    and
    (orientation: landscape)
{

    .app
    {
        gap: 5px;
    }


    .header
    {
        padding: 5px 9px;
    }


    .panel
    {
        padding: 7px;
    }


    .panel-title
    {
        margin-bottom: 5px;
    }


    .sensor-temperature
    {
        font-size: 24px;

        margin: 4px 0 7px;
    }


    .button
    {
        min-height: 30px;

        padding: 4px 8px;
    }

}

)rawliteral";

#endif