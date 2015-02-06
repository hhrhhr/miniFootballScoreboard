#include "panel.h"

void Panel::init()
{
    qDebug("Panel::init()");

    readSettings();
    match = 1;
    command1Foul = 0;
    command1Score = 0;
    command2Score = 0;
    command1Foul = 0;
    ratio = 4.0 / 3.0;

    timer = new QElapsedTimer();
    tmpTime = 0;
}

void Panel::readSettings()
{
    qDebug("Panel::readSettings()");
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationName());

    logoPath = settings.value("logoPath", ":/logo.png").toString();

    champName = settings.value("champName", "Чемпионат Антарктиды 2022").toString();
    command1 = settings.value("command1", "Зеленые Тюлени").toString();
    command2 = settings.value("command2", "Синие Пингвины").toString();

    fontName = settings.value("fontName", "Arial Black").toString();
    fontWeight = settings.value("fontWeight", "bold").toString();
    fontStyle = settings.value("fontStyle", "normal").toString();
    font2Name = settings.value("font2Name", "Tahoma").toString();
    font2Weight = settings.value("font2Weight", "normal").toString();
    font2Style = settings.value("font2Style", "italic").toString();

    champNameFontSz = settings.value("champNameFontSz", 30).toUInt();
    commandFontSz = settings.value("commandFontSz", 25).toUInt();
    matchFontSz = settings.value("matchFontSz", 40).toUInt();
    scoreFontSz = settings.value("scoreFontSz", 65).toUInt();
    foulFontSz = settings.value("foulFontSz", 45).toUInt();
    timerFontSz = settings.value("timerFontSz", 80).toUInt();

    color = settings.value("color", "#ffffff").toString();
    background = settings.value("background", "#312448").toString();

    command1Clr = settings.value("command1Clr", color).toString();
    command1Bkg = settings.value("command1Bkg", "#005500").toString();
    command2Clr = settings.value("command2Clr", color).toString();
    command2Bkg = settings.value("command2Bkg", "#00007f").toString();

    timerClr = settings.value("timerClr", "#00ff7f").toString();

    foulGreenBkg = settings.value("foulGreenBkg", "#00aa00").toString();
    foulRedBkg = settings.value("foulRedBkg", "#aa0000").toString();

    isTimerBack = settings.value("isTimerBack", true).toBool();
    timeout = settings.value("timeout", 4000).toInt();
    timeout2 = settings.value("timeout2", 3000).toInt();
    timeFormat = settings.value("timeFormat", "mm:ss").toString();

    sound = settings.value("sound", "./media/hong.mp3").toString();
    sound2 = settings.value("sound2", "./media/siren.mp3").toString();
}

void Panel::saveSettings()
{
    qDebug("Panel::saveSettings()");
    QSettings settings(QSettings::IniFormat,
                       QSettings::UserScope,
                       QApplication::organizationName(),
                       QApplication::applicationName());

    settings.setValue("logoPath", logoPath);

    settings.setValue("champName", champName);
    settings.setValue("command1", command1);
    settings.setValue("command2", command2);

    settings.setValue("fontName", fontName);
    settings.setValue("fontWeight", fontWeight);
    settings.setValue("fontStyle", fontStyle);
    settings.setValue("font2Name", font2Name);
    settings.setValue("font2Weight", font2Weight);
    settings.setValue("font2Style", font2Style);

    settings.setValue("champNameFontSz", champNameFontSz);
    settings.setValue("commandFontSz", commandFontSz);
    settings.setValue("matchFontSz", matchFontSz);
    settings.setValue("scoreFontSz", scoreFontSz);
    settings.setValue("foulFontSz", foulFontSz);
    settings.setValue("timerFontSz", timerFontSz);

    settings.setValue("color", color);
    settings.setValue("background", background);

    settings.setValue("command1Clr", command1Clr);
    settings.setValue("command1Bkg", command1Bkg);
    settings.setValue("command2Clr", command2Clr);
    settings.setValue("command2Bkg", command2Bkg);

    settings.setValue("timerClr", timerClr);

    settings.setValue("foulGreenBkg", foulGreenBkg);
    settings.setValue("foulRedBkg", foulRedBkg);

    settings.setValue("isTimerBack", isTimerBack);
    settings.setValue("timeout", timeout);
    settings.setValue("timeout2", timeout2);

    settings.setValue("sound", sound);
    settings.setValue("sound2", sound2);
}
