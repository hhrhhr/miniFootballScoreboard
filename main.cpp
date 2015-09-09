#include "widget.h"
#include <QApplication>

QString Panel::logoPath;
QString Panel::champName;
QString Panel::command1;
QString Panel::command2;

QString Panel::fontName;
QString Panel::fontWeight;
QString Panel::fontStyle;
QString Panel::font2Name;
QString Panel::font2Weight;
QString Panel::font2Style;

quint8 Panel::match;
quint8 Panel::command1Score;
quint8 Panel::command2Score;
quint8 Panel::command1Foul;
quint8 Panel::command2Foul;

quint8 Panel::champNameFontSz;
quint8 Panel::commandFontSz;
quint8 Panel::matchFontSz;
quint8 Panel::scoreFontSz;
quint8 Panel::foulFontSz;
quint8 Panel::timerFontSz;

QString Panel::background;
QString Panel::color;
QString Panel::command1Clr;
QString Panel::command1Bkg;
QString Panel::command2Clr;
QString Panel::command2Bkg;

QString Panel::timerClr;

QString Panel::foulGreenBkg;
QString Panel::foulRedBkg;

float Panel::ratio;

QElapsedTimer *Panel::timer;
bool Panel::isTimerBack;
int Panel::tmpTime;
int Panel::timeout;
int Panel::timeout2;
QString Panel::timeFormat;

QString Panel::sound;
QString Panel::sound2;

//void Panel::init();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("DVZ");
    a.setApplicationVersion("0.9.0.0");
    a.setApplicationName("scoreboard");

    Widget w;
    w.show();

    return a.exec();
}
