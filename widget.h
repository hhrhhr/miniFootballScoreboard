#ifndef WIDGET_H
#define WIDGET_H

#include "dialog.h"
#include <QWidget>
#include <QTimer>
#include <QColorDialog>
#include <QToolButton>
#include "panel.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

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
    void on_cbFullScreen_toggled(bool checked);

    void on_btApplyScore_clicked();
    void on_btResetScore_clicked();
    void on_btStart_clicked();
    void on_btStop_clicked();
    void on_btStart2_clicked();
    void on_btStop2_clicked();
    void on_btStart3_clicked();
    void on_btStop3_clicked();

    void onTimeout();
    void onRefresh();

    void on_tbSelectBkg_clicked();

    void on_tbSelectClr_clicked();

    void on_tbSelectCmd1Bkg_clicked();

    void on_tbSelectCmd2Bkg_clicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Panel p;
    Dialog *f;
    Ui::Widget *ui;

    QTimer *refresh;
    int activeTimer;

    void selectColor(QToolButton *b, QString &elem);
};

#endif // WIDGET_H
