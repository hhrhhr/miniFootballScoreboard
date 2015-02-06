#include "panel.h"

/*

 * {
    font-family: "Arial Black"
    font-size: 30px;
    font-style: normal;
    font-weight: bold;

    background-color: "#312448";
    color: "#ffffff";

    margin: 2px;
    border-color: "#ffffff";
    border-width: 2px;
    border-style: solid;
    border-radius: 10px;
}
#Dialog, #lbScoreDivisor {
    border-width: 0;
}
#lbLogo {
    border-color: rgb(49, 36, 72);
}
#lbFoul1, #lbFoul2 {
    margin: 15px;
}
#lbFoul1:enabled, #lbFoul2:enabled {
    background-color: "#c0439163";
}
#lbFoul1:disabled, #lbFoul2:disabled {
    background-color: "#c098514e";
}

*/

void Panel::init()
{
    logoPath = ":/logo.png";

    champName = "Чемпионат Антарктиды 2022";
    command1 = "Зеленые Тюлени";
    command2 = "Синие Пингвины";

    fontName = "Arial";
    fontWeight = "bold";
    fontStyle = "normal";
    font2Name = "Tahoma";
    font2Weight = "normal";
    font2Style = "italic";

    match = 1;
    command1Foul = 0;
    command1Score = 0;
    command2Score = 0;
    command1Foul = 0;

    champNameFontSz = 30;
    commandFontSz = 25;
    matchFontSz = 40;
    scoreFontSz = 65;
    foulFontSz = 45;
    timerFontSz = 80;

    color = "#ffffff";
    background = "#312448";

    command1Clr = color;
    command1Bkg = "#005500";
    command2Clr = color;
    command2Bkg = "#00007f";

    timerClr = "#00ff7f";

    foulGreenBkg = "#00aa00";
    foulRedBkg = "#aa0000";

    ratio = 4.0 / 3.0;

    timer = new QElapsedTimer();
    isTimerBack = true;
    tmpTime = 0;
    timeout = 0;
    timeFormat = "mm:ss";
}
