#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include "panel.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void changeTexts();
    void changeRatio();
    void changeFonts();
    void changeScore();
    void setTimer(QString &time);

protected:
    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);

private:
    Panel p;
    Ui::Dialog *ui;

    void calculateStyle();
    void checkFouls();
};

#endif // DIALOG_H
