#ifndef WIDGET_H
#define WIDGET_H

#include "dialog.h"
#include <QWidget>
#include <QCloseEvent>
#include <QElapsedTimer>
#include <QTimer>
#include <QColorDialog>
#include <QToolButton>
#include <QMediaPlayer>
#include "panel.h"

#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void toggleFScb(bool state);

private slots:
    void on_btOpenLogo_clicked();
    void on_btApply_clicked();

    void on_sbChampName_valueChanged(int arg1);
    void on_sbCommand_valueChanged(int arg1);
    void on_sbMatch_valueChanged(int arg1);
    void on_sbScore_valueChanged(int arg1);
    void on_sbFoul_valueChanged(int arg1);
    void on_sbTimer_valueChanged(int arg1);

    void on_rb43_toggled(bool checked);
    void on_rb1610_toggled(bool checked);
    void on_rb169_toggled(bool checked);

    void on_btApplyScore_clicked();
    void on_btResetScore_clicked();
    void on_btStart_clicked();
    void on_btStop_clicked();
    void on_btStart2_clicked();
    void on_btStop2_clicked();

    void onTimeout();
    void onRefresh();

    void on_tbSelectBkg_clicked();
    void on_tbSelectClr_clicked();
    void on_tbSelectCmd1Clr_clicked();
    void on_tbSelectCmd1Bkg_clicked();
    void on_tbSelectCmd2Clr_clicked();
    void on_tbSelectCmd2Bkg_clicked();
    void on_tbSelecTmrClr_clicked();
    void on_tbSelectFoulClrGreen_clicked();
    void on_tbSelectFoulClrRed_clicked();

    void on_cbFont_currentFontChanged(const QFont &fnt);
    void on_cbFont2_currentFontChanged(const QFont &fnt);
    void on_tbFontBold_toggled(bool checked);
    void on_tbFontItalic_toggled(bool checked);
    void on_tbFont2Bold_toggled(bool checked);
    void on_tbFont2Italic_toggled(bool checked);

    void on_tbSetFocus_clicked();

    void on_timeEdit_timeChanged(const QTime &time);
    void on_timeEdit2_timeChanged(const QTime &time);
    void on_leTimeFormat_textChanged(const QString &arg1);
    void on_rbTimerBack_toggled(bool checked);

    void on_tbSelectSound_clicked();
    void on_tbSelectSound2_clicked();
    void on_pbPlaySound_clicked();
    void on_pbPlaySound2_clicked();

    void onStateChanged(QMediaPlayer::State state);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Panel p;
    Dialog *f;
    Ui::Widget *ui;

    QTimer *refresh;
    int activeTimer;

    QMediaPlayer *player;

    void selectColor(QToolButton *b, QString &elem);
    void readSettings();
    void saveSettings();
};

#endif // WIDGET_H
