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
    font-size:
        clamp(14px, 1.4vw, 20px);

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

    margin-top: 10px;

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
        transform .1s,
        border-color .15s;
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
    border-color:
        #245b91;
}

.button-green
{
    border-color:
        #287447;
}

.button-red
{
    border-color:
        #873131;
}

.button-orange
{
    border-color:
        #966127;
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

    margin-top: 10px;
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
   RAFRAICHISSEMENT
   ============================================================ */

.refresh-control
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 15px;

    margin-top: 10px;
}

.refresh-control label
{
    color: #9da7b3;

    font-size:
        clamp(11px, .9vw, 14px);
}

.refresh-input
{
    display: flex;

    align-items: center;

    gap: 7px;
}

.refresh-input input
{
    width: 70px;

    height: 36px;

    padding:
        5px 8px;

    background: #11151a;

    border:
        1px solid #343b46;

    border-radius: 7px;

    color: #ffffff;

    font-size: 14px;

    text-align: center;
}

.refresh-input span
{
    color: #8e98a6;

    font-size: 13px;
}


/* ============================================================
   SONDES
   ============================================================ */

.sensors-panel
{
    padding:
        clamp(12px, 1.4vw, 20px);
}

.sensors-heading
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 15px;

    margin-bottom:
        clamp(10px, 1vw, 16px);
}

.sensors-subtitle
{
    margin-top: 3px;

    color: #687381;

    font-size:
        clamp(10px, .8vw, 12px);
}

.sensor-summary
{
    padding:
        7px 12px;

    border-radius: 20px;

    background: #11151a;

    border:
        1px solid #292f38;

    color: #9da7b3;

    font-size: 12px;

    white-space: nowrap;
}


/* ============================================================
   GRILLE DES SONDES
   ============================================================ */

.sensor-grid
{
    display: grid;

    grid-template-columns:
        repeat(
            auto-fit,
            minmax(
                240px,
                1fr
            )
        );

    gap:
        clamp(9px, 1vw, 14px);
}


/* ============================================================
   CARTE SONDE
   ============================================================ */

.sensor-card
{
    position: relative;

    overflow: hidden;

    background:
        linear-gradient(
            145deg,
            #171c22,
            #11151a
        );

    border:
        1px solid #292f38;

    border-radius: 12px;

    padding:
        clamp(11px, 1vw, 16px);

    min-width: 0;

    transition:
        border-color .2s,
        transform .15s,
        box-shadow .2s;
}

.sensor-card:hover
{
    transform:
        translateY(-1px);

    box-shadow:
        0 5px 18px
        rgba(0, 0, 0, .22);
}


/* ============================================================
   ETAT CARTE
   ============================================================ */

.sensor-card::before
{
    content: "";

    position: absolute;

    left: 0;
    top: 0;
    bottom: 0;

    width: 4px;

    background: #4ade80;
}

.sensor-card.state-orange::before
{
    background: #f59e0b;
}

.sensor-card.state-red::before
{
    background: #ef4444;
}

.sensor-card.state-gray::before
{
    background: #64748b;
}

.sensor-card.state-green
{
    border-color:
        rgba(74, 222, 128, .28);
}

.sensor-card.state-orange
{
    border-color:
        rgba(245, 158, 11, .35);
}

.sensor-card.state-red
{
    border-color:
        rgba(239, 68, 68, .40);
}


/* ============================================================
   EN-TETE CARTE
   ============================================================ */

.sensor-header
{
    display: flex;

    align-items: center;
    justify-content: space-between;

    gap: 8px;
}

.sensor-name
{
    display: flex;

    align-items: center;

    gap: 7px;

    font-size:
        clamp(13px, 1.1vw, 16px);

    font-weight: 700;
}

.sensor-icon
{
    font-size: 17px;
}

.sensor-state
{
    padding:
        4px 8px;

    border-radius: 20px;

    background: #17251d;

    color: #4ade80;

    font-size: 9px;

    font-weight: 700;

    letter-spacing: .4px;

    white-space: nowrap;
}

.state-orange .sensor-state
{
    background: #2b2110;

    color: #f59e0b;
}

.state-red .sensor-state
{
    background: #2b1515;

    color: #ef4444;
}

.state-gray .sensor-state
{
    background: #20252c;

    color: #94a3b8;
}


/* ============================================================
   TEMPERATURE
   ============================================================ */

.sensor-temperature
{
    display: flex;

    align-items: baseline;

    gap: 5px;

    margin:
        14px 0 10px;
}

.sensor-temperature-value
{
    font-size:
        clamp(30px, 3.2vw, 48px);

    font-weight: 700;

    line-height: .95;

    letter-spacing: -1.5px;
}

.sensor-temperature-unit
{
    color: #7f8b99;

    font-size:
        clamp(13px, 1vw, 16px);
}


/* ============================================================
   ECART
   ============================================================ */

.sensor-difference
{
    display: flex;

    justify-content: space-between;

    align-items: center;

    gap: 8px;

    margin-bottom: 7px;

    color: #8e98a6;

    font-size: 11px;
}

.sensor-difference strong
{
    color: #cbd1d8;

    font-size: 12px;
}


/* ============================================================
   BARRE ECART
   ============================================================ */

.sensor-bar
{
    height: 5px;

    overflow: hidden;

    background: #252b33;

    border-radius: 10px;

    margin-bottom: 13px;
}

.sensor-bar-fill
{
    height: 100%;

    width: 0%;

    background: #4ade80;

    border-radius: inherit;

    transition:
        width .25s,
        background .2s;
}

.state-orange .sensor-bar-fill
{
    background: #f59e0b;
}

.state-red .sensor-bar-fill
{
    background: #ef4444;
}


/* ============================================================
   CONSIGNE
   ============================================================ */

.sensor-setpoint
{
    padding-top: 10px;

    border-top:
        1px solid #252b33;
}

.sensor-setpoint-label
{
    color: #687381;

    font-size: 10px;

    margin-bottom: 6px;
}

.setpoint-control
{
    display: grid;

    grid-template-columns:
        34px
        minmax(70px, 1fr)
        34px;

    gap: 5px;

    align-items: center;
}

.setpoint-button
{
    width: 34px;
    height: 34px;

    padding: 0;

    border:
        1px solid #343b46;

    border-radius: 7px;

    background: #252b33;

    color: #ffffff;

    font-size: 20px;

    line-height: 1;

    cursor: pointer;

    transition:
        background .15s,
        transform .1s;
}

.setpoint-button:hover
{
    background: #303743;
}

.setpoint-button:active
{
    transform: scale(.94);
}

.setpoint-input
{
    width: 100%;

    min-width: 0;

    height: 34px;

    padding:
        4px 7px;

    background: #11151a;

    border:
        1px solid #343b46;

    border-radius: 7px;

    color: #ffffff;

    font-size: 15px;

    font-weight: 700;

    text-align: center;

    outline: none;
}

.setpoint-input:focus
{
    border-color:
        #64748b;

    box-shadow:
        0 0 0 2px
        rgba(100, 116, 139, .15);
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
            repeat(
                2,
                minmax(0, 1fr)
            );
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
        padding:
            8px 10px;
    }

    .links
    {
        gap: 7px;
    }

    .panel
    {
        padding: 9px;
    }

    .status-content
    {
        gap: 5px;
    }

    .status-content p
    {
        padding: 6px;
    }

    .button
    {
        min-height: 34px;

        padding:
            5px 9px;
    }

    .refresh-control
    {
        align-items: stretch;

        flex-direction: column;

        gap: 8px;
    }

    .refresh-input
    {
        width: 100%;
    }

    .refresh-input input
    {
        width: 70px;
    }

    .refresh-input .button
    {
        flex: 1;
    }

    .sensors-heading
    {
        align-items: flex-start;

        flex-direction: column;

        gap: 7px;
    }

    .sensor-summary
    {
        align-self: flex-start;
    }

    .sensor-grid
    {
        grid-template-columns:
            repeat(
                2,
                minmax(0, 1fr)
            );

        gap: 6px;
    }

    .sensor-card
    {
        padding: 9px;
    }

    .sensor-temperature
    {
        margin:
            12px 0 8px;
    }

    .sensor-temperature-value
    {
        font-size: 28px;
    }

    .sensor-state
    {
        padding:
            3px 5px;

        font-size: 8px;
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
   GRAND FORMAT
   ============================================================ */

@media (min-width: 1400px)
{
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
   PAYSAGE MOBILE
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
        padding:
            5px 9px;
    }

    .panel
    {
        padding: 7px;
    }

    .sensor-temperature
    {
        margin:
            7px 0;
    }

    .sensor-temperature-value
    {
        font-size: 25px;
    }

    .button
    {
        min-height: 30px;

        padding:
            4px 8px;
    }
}

)rawliteral";

#endif