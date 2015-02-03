#ifndef PANEL_H
#define PANEL_H

#include <QString>
#include <QTimer>
#include <QRgb>

class Panel
{
public:
    static QString logoPath;

    static QString champName;
    static QString command1;
    static QString command2;

    static quint8 match;
    static quint8 command1Score;
    static quint8 command2Score;
    static quint8 command1Foul;
    static quint8 command2Foul;

    static quint8 champNameFontSize;
    static quint8 commandFontSize;
    static quint8 matchFontSize;
    static quint8 scoreFontSize;
    static quint8 foulFontSize;
    static quint8 timerFontSize;

    static QString background;
    static QString color;
    static QString command1Bkg;
    static QString command2Bkg;

    static float ratio;

    static QTimer *timer;
    static int remainingTime;

    static void init();
};

#endif // PANEL_H
