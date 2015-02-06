#-------------------------------------------------
#
# Project created by QtCreator 2015-02-01T02:48:18
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scoreboard
TEMPLATE = app


SOURCES += main.cpp\
    widget.cpp \
    panel.cpp \
    dialog.cpp

HEADERS  += widget.h \
    panel.h \
    dialog.h

FORMS    += widget.ui \
    dialog.ui

RESOURCES += \
    res.qrc

win32 {
    RC_FILE = scoreboard.rc
}

