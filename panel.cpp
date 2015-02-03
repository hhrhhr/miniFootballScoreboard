#include "panel.h"

/*

 * {
font: 900 30px "Arial";
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
    logoPath = QString(":/logo.png");

    champName = QString("Чемпионат Антарктиды 2022");
    command1 = QString("Зеленые Тюлени");
    command2 = QString("Синие Пингвины");

    match = 1;
    command1Score = 0;
    command2Score = 0;
    command1Foul = 0;
    command1Foul = 0;

    champNameFontSize = 20;
    commandFontSize = 30;
    matchFontSize = 45;
    scoreFontSize = 70;
    foulFontSize = 55;
    timerFontSize = 90;

    background = "#312448";
    color = "#ffffff";
    command1Bkg = "#005500";
    command2Bkg = "#00007f";

    ratio = 4.0 / 3.0;
    timer = new QTimer();
    timer->setSingleShot(true);
    remainingTime = 0;
}
