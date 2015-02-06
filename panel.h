#ifndef PANEL_H
#define PANEL_H

#include <QString>
#include <QElapsedTimer>
#include <QRgb>

class Panel
{
public:
    static QString logoPath;

    static QString champName;
    static QString command1;
    static QString command2;

    static QString fontName;
    static QString fontWeight;
    static QString fontStyle;
    static QString font2Name;
    static QString font2Weight;
    static QString font2Style;

    static quint8 match;
    static quint8 command1Foul;
    static quint8 command1Score;
    static quint8 command2Score;
    static quint8 command2Foul;

    static quint8 champNameFontSz;
    static quint8 commandFontSz;
    static quint8 matchFontSz;
    static quint8 scoreFontSz;
    static quint8 foulFontSz;
    static quint8 timerFontSz;

    static QString color;
    static QString background;

    static QString command1Clr;
    static QString command1Bkg;
    static QString command2Clr;
    static QString command2Bkg;

    static QString timerClr;

    static QString foulGreenBkg;
    static QString foulRedBkg;

    static float ratio;

    static QElapsedTimer *timer;    // монолитный таймер
    static bool isTimerBack;        // обратный или прямой
    static int timeout;             // заданное время
    static int tmpTime;             //
    static QString timeFormat;

    static void init();
};

#endif // PANEL_H
