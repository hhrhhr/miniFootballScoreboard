#include "widget.h"
#include <QApplication>

QString Panel::logoPath;
QString Panel::champName;
QString Panel::command1;
QString Panel::command2;
quint8 Panel::match;
quint8 Panel::command1Score;
quint8 Panel::command2Score;
quint8 Panel::command1Foul;
quint8 Panel::command2Foul;
quint8 Panel::champNameFontSize;
quint8 Panel::commandFontSize;
quint8 Panel::matchFontSize;
quint8 Panel::scoreFontSize;
quint8 Panel::foulFontSize;
quint8 Panel::timerFontSize;
QString Panel::background;
QString Panel::color;
QString Panel::command1Bkg;
QString Panel::command2Bkg;
QString Panel::timerColor;
QString Panel::foulGreenColor;
QString Panel::foulRedColor;
float Panel::ratio;
QTimer *Panel::timer;
int Panel::remainingTime;
int Panel::elapsedTime;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Widget w;
    w.show();

    return a.exec();
}
