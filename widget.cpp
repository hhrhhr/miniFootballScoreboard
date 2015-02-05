#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QPixmap>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
//    qDebug("Widget()");

    p.init();
    f = NULL;

    ui->setupUi(this);

    ui->lineChampName->setText(p.champName);
    ui->lineCommand1->setText(p.command1);
    ui->lineCommand2->setText(p.command2);

    ui->sbMatchN->setValue(p.match);
    ui->sbFoul1->setValue(p.command1Foul);
    ui->sbScore1->setValue(p.command1Score);
    ui->sbScore2->setValue(p.command2Score);
    ui->sbFoul2->setValue(p.command2Foul);

    ui->cbFont->setCurrentFont(QFont(p.fontName));
    ui->cbFont2->setCurrentFont(QFont(p.font2Name));
    ui->tbFontBold->setChecked(QString::compare(p.fontWeight, "bold") == 0);
    ui->tbFont2Bold->setChecked(QString::compare(p.font2Weight, "bold") == 0);
    ui->tbFontItalic->setChecked(QString::compare(p.fontStyle, "italic") == 0);
    ui->tbFont2Italic->setChecked(QString::compare(p.font2Style, "italic") == 0);

    ui->sbChampName->setValue(p.champNameFontSz);
    ui->sbCommand->setValue(p.commandFontSz);
    ui->sbMatch->setValue(p.matchFontSz);
    ui->sbFoul->setValue(p.foulFontSz);
    ui->sbScore->setValue(p.scoreFontSz);
    ui->sbTimer->setValue(p.timerFontSz);

    QString c;
    c.sprintf("background-color: \"%s\";", p.background.toLatin1().data());
    ui->tbSelectBkg->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.color.toLatin1().data());
    ui->tbSelectClr->setStyleSheet(c);

    c.sprintf("background-color: \"%s\";", p.command1Clr.toLatin1().data());
    ui->tbSelectCmd1Clr->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.command1Bkg.toLatin1().data());
    ui->tbSelectCmd1Bkg->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.command2Clr.toLatin1().data());
    ui->tbSelectCmd2Clr->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.command2Bkg.toLatin1().data());
    ui->tbSelectCmd2Bkg->setStyleSheet(c);

    c.sprintf("background-color: \"%s\";", p.timerClr.toLatin1().data());
    ui->tbSelecTmrClr->setStyleSheet(c);

    c.sprintf("background-color: \"%s\";", p.foulGreenBkg.toLatin1().data());
    ui->tbSelectFoulClrGreen->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.foulRedBkg.toLatin1().data());
    ui->tbSelectFoulClrRed->setStyleSheet(c);

    ui->leTimeFormat->setText(p.timeFormat);
    ui->rbTimerBack->setChecked(p.isTimerBack);

    ui->btOpenLogo->setFocus();

    this->move(200, 50);

    f = new Dialog();
    f->move(this->geometry().topRight());
    f->show();

    p.remainingTime = 0;
    activeTimer = 1;

    refresh = new QTimer(this);
    connect(refresh, SIGNAL(timeout()), this, SLOT(onRefresh()));
    refresh->start(333);

}

Widget::~Widget()
{
//    qDebug("~Widget()");

    delete f;
    delete ui;
}

void Widget::on_btOpenLogo_clicked()
{
    QString path =
            QFileDialog::getOpenFileName(this,
                                         QString("Выберите логотип"),
                                         QDir::currentPath(),
                                         QString("Images (*.bmp *.png *.jpg *.jpeg)"));
    if (!path.isEmpty()) {
        p.logoPath = path;
        ui->lbLogo->setStyleSheet(QString("image: url(\"%1\");").arg(path));
    }
}

void Widget::on_btApply_clicked()
{
    p.champName = ui->lineChampName->text();
    p.command1 = ui->lineCommand1->text();
    p.command2 = ui->lineCommand2->text();
    f->changeTexts();
}

void Widget::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    f->close();
}

void Widget::on_sbChampName_valueChanged(int arg1)
{
    p.champNameFontSz = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbCommand_valueChanged(int arg1)
{
    p.commandFontSz = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbMatch_valueChanged(int arg1)
{
    p.matchFontSz = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbScore_valueChanged(int arg1)
{
    p.scoreFontSz = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbFoul_valueChanged(int arg1)
{
    p.foulFontSz = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbTimer_valueChanged(int arg1)
{
    p.timerFontSz = arg1;
    if (f) f->changeFonts();
}


void Widget::on_rb43_toggled(bool checked)
{
    if (f and checked) {
        f->setWindowState(this->windowState() & ~Qt::WindowFullScreen);
        p.ratio =  4.0 / 3.0;
        f->changeRatio();
    }
}

void Widget::on_rb1610_toggled(bool checked)
{
    if (f and checked) {
        f->setWindowState(this->windowState() & ~Qt::WindowFullScreen);
        p.ratio =  16.0 / 10.0;
        f->changeRatio();
    }
}

void Widget::on_rb169_toggled(bool checked)
{
    if (f and checked) {
        f->setWindowState(this->windowState() & ~Qt::WindowFullScreen);
        p.ratio =  16.0 / 9.0;
        f->changeRatio();
    }
}

void Widget::on_btResetScore_clicked()
{
    p.match = 1;
    p.command1Foul = 0;
    p.command1Score = 0;
    p.command2Score = 0;
    p.command2Foul = 0;

    ui->sbMatchN->setValue(p.match);
    ui->sbFoul1->setValue(p.command1Foul);
    ui->sbScore1->setValue(p.command1Score);
    ui->sbScore2->setValue(p.command2Score);
    ui->sbFoul2->setValue(p.command2Foul);

    if (f)
        f->changeScore();

    ui->tbSetFocus->setText("<-");
    ui->btStart->setFocus();
}

void Widget::on_btApplyScore_clicked()
{
    p.match = ui->sbMatchN->value();
    p.command1Foul = ui->sbFoul1->value();
    p.command1Score = ui->sbScore1->value();
    p.command2Score = ui->sbScore2->value();
    p.command2Foul = ui->sbFoul2->value();

    if (f)
        f->changeScore();

    if (activeTimer == 1) {
        ui->btStart->setFocus();
    } else if (activeTimer == 2) {
        ui->btStart2->setFocus();
    } else {
        qDebug("!!!!!!!!!!!!!!");
    }
}

void Widget::on_btStart_clicked()
{
    ui->btStop->setEnabled(true);
    ui->btStop2->setEnabled(false);
    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(false);
    ui->btResetScore->setEnabled(false);
    ui->tbSetFocus->setText("<-");

    ui->gbInputData->setEnabled(false);
    ui->gbStyle->setEnabled(false);
    ui->gbTimer->setEnabled(false);

    if (p.timer->isValid()) {
        ui->btStart->setText(QString("Старт"));
        p.remainingTime = p.timeout - p.timer->elapsed();
        p.timer->invalidate();
    } else {
        ui->btStart->setText(QString("Пауза"));
        if (p.remainingTime > 0) {
            p.timeout = p.remainingTime;
            p.timer->start();
        } else {
            int ms = ui->timeEdit->time().msecsSinceStartOfDay();
            p.timeout = ms;
            p.remainingTime = ms;
            activeTimer = 1;
            p.timer->start();
        }
    }

    ui->btStart->setFocus();
}

void Widget::on_btStop_clicked()
{
    p.timer->invalidate();
    p.remainingTime = 0;
    ui->lbTimer->setText(QTime(0, 0).toString(ui->leTimeFormat->text()));

    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(true);
    ui->btResetScore->setEnabled(true);

    ui->gbInputData->setEnabled(true);
    ui->gbStyle->setEnabled(true);
    ui->gbTimer->setEnabled(true);

    ui->btStart->setText(QString("Старт"));
    ui->btStart2->setText(QString("Старт"));

    ui->btStart->setFocus();
}


void Widget::on_btStart2_clicked()
{
    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(true);
    ui->btStart->setEnabled(false);
    ui->btStart2->setEnabled(true);
    ui->btResetScore->setEnabled(false);
    ui->tbSetFocus->setText("->");

    ui->gbInputData->setEnabled(false);
    ui->gbStyle->setEnabled(false);
    ui->gbTimer->setEnabled(false);

    if (p.timer->isValid()) {
        ui->btStart2->setText(QString("Старт"));
        p.remainingTime = p.timeout - p.timer->elapsed();
        p.timer->invalidate();
    } else {
        ui->btStart2->setText(QString("Пауза"));
        if (p.remainingTime > 0) {
            p.timeout = p.remainingTime;
            p.timer->start();
        } else {
            int ms = ui->timeEdit2->time().msecsSinceStartOfDay();
            p.timeout = ms;
            p.remainingTime = ms;
            activeTimer = 2;
            p.timer->start();
        }
    }

    ui->btStart2->setFocus();
}

void Widget::on_btStop2_clicked()
{
    p.timer->invalidate();
    p.remainingTime = 0;
    ui->lbTimer2->setText(QTime(0, 0).toString(ui->leTimeFormat->text()));

    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(true);
    ui->btResetScore->setEnabled(true);

    ui->gbInputData->setEnabled(true);
    ui->gbStyle->setEnabled(true);
    ui->gbTimer->setEnabled(true);

    ui->btStart->setText(QString("Старт"));
    ui->btStart2->setText(QString("Старт"));

    ui->btStart2->setFocus();
}


void Widget::onTimeout()
{
    if (activeTimer == 1) {
        on_btStop_clicked();
        if (ui->rbTimerStop->isChecked()) {
            ui->btStart->setFocus();
        } else {
            ui->tbSetFocus->setText("->");
            on_btStart2_clicked();
        }
    } else if (activeTimer == 2) {
        on_btStop2_clicked();
        if (ui->rbTimer2Stop->isChecked()) {
            ui->btStart2->setFocus();
        } else {
            ui->tbSetFocus->setText("<-");
            on_btStart_clicked();
        }
    } else {
        qDebug("!!!!!!!!!!!!!!");
    }
}

void Widget::onRefresh()
{
    if (p.timer->isValid()) {
        int t = p.timeout - p.timer->elapsed();
        if (t > 0) {
            if (!p.isTimerBack)
                t = p.timer->elapsed();
            QString str = QTime::fromMSecsSinceStartOfDay(t).toString(p.timeFormat);

            if (activeTimer == 1) {
                ui->lbTimer->setText(str);
            } else if (activeTimer == 2) {
                ui->lbTimer2->setText(str);
            } else {
                qDebug("!!!!!!!!!!!!!!");
            }
        } else {
            onTimeout();
        }
    }
}

void Widget::selectColor(QToolButton *b, QString &elem)
{
    QColor color = QColorDialog::getColor(elem, this, "Выберите цвет", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        elem = color.name(QColor::HexArgb);
        QString c;
        c.sprintf("background-color: \"%s\";", elem.toLatin1().data());
        b->setStyleSheet(c);
    }
    if (f)
        f->changeFonts();
}

void Widget::on_tbSelectBkg_clicked()
{
    selectColor(ui->tbSelectBkg, p.background);
}

void Widget::on_tbSelectClr_clicked()
{
    selectColor(ui->tbSelectClr, p.color);
}

void Widget::on_tbSelectCmd1Bkg_clicked()
{
    selectColor(ui->tbSelectCmd1Bkg, p.command1Bkg);
}

void Widget::on_tbSelectCmd1Clr_clicked()
{
    selectColor(ui->tbSelectCmd1Clr, p.command1Clr);
}

void Widget::on_tbSelectCmd2Bkg_clicked()
{
    selectColor(ui->tbSelectCmd2Bkg, p.command2Bkg);
}

void Widget::on_tbSelectCmd2Clr_clicked()
{
    selectColor(ui->tbSelectCmd2Clr, p.command2Clr);
}

void Widget::on_tbSelecTmrClr_clicked()
{
    selectColor(ui->tbSelecTmrClr, p.timerClr);
}

void Widget::on_tbSelectFoulClrGreen_clicked()
{
    selectColor(ui->tbSelectFoulClrGreen, p.foulGreenBkg);
}

void Widget::on_tbSelectFoulClrRed_clicked()
{
    selectColor(ui->tbSelectFoulClrRed, p.foulRedBkg);
}


/* fonts */

void Widget::on_cbFont_currentFontChanged(const QFont &fnt)
{
    p.fontName = fnt.family();
    if (f)
        f->changeFonts();
}

void Widget::on_cbFont2_currentFontChanged(const QFont &fnt)
{
    p.font2Name = fnt.family();
    if (f)
        f->changeFonts();
}

void Widget::on_tbFontBold_toggled(bool checked)
{
    if (checked) {
        ui->tbFontBold->setStyleSheet("font-weight: bold;");
        p.fontWeight = "bold";
    } else {
        ui->tbFontBold->setStyleSheet("font-weight: normal;");
        p.fontWeight = "normal";
    }
    if (f)
        f->changeFonts();
}

void Widget::on_tbFontItalic_toggled(bool checked)
{
    if (checked) {
        ui->tbFontItalic->setStyleSheet("font-style: italic;");
        p.fontStyle = "italic";
    } else {
        ui->tbFontItalic->setStyleSheet("font-style: normal;");
        p.fontStyle = "normal";
    }
    if (f)
        f->changeFonts();
}

void Widget::on_tbFont2Bold_toggled(bool checked)
{
    if (checked) {
        ui->tbFont2Bold->setStyleSheet("font-weight: bold;");
        p.font2Weight = "bold";
    } else {
        ui->tbFont2Bold->setStyleSheet("font-weight: normal;");
        p.font2Weight = "normal";
    }
    if (f)
        f->changeFonts();
}

/* */

void Widget::on_tbFont2Italic_toggled(bool checked)
{
    if (checked) {
        ui->tbFont2Italic->setStyleSheet("font-style: italic;");
        p.font2Style = "italic";
    } else {
        ui->tbFont2Italic->setStyleSheet("font-style: normal;");
        p.font2Style = "normal";
    }
    if (f)
        f->changeFonts();
}

void Widget::on_tbSetFocus_clicked()
{
    if (activeTimer == 1) {
        ui->btStart->setFocus();
        ui->tbSetFocus->setText("<-");
    } else if (activeTimer == 2) {
        ui->btStart2->setFocus();
        ui->tbSetFocus->setText("->");
    } else {
        qDebug("!!!!!!!!!!!!!!");
    }
}

/* */

void Widget::on_timeEdit_timeChanged(const QTime &time)
{
    if (p.isTimerBack)
        ui->lbTimer->setText(time.toString(p.timeFormat));
    else
        ui->lbTimer->setText(QTime(0, 0).toString(p.timeFormat));
}

void Widget::on_timeEdit2_timeChanged(const QTime &time)
{
    if (p.isTimerBack)
        ui->lbTimer2->setText(time.toString(ui->leTimeFormat->text()));
    else
        ui->lbTimer2->setText(QTime(0, 0).toString(ui->leTimeFormat->text()));
}

void Widget::on_leTimeFormat_textChanged(const QString &arg1)
{
    p.timeFormat = arg1;
    if (p.isTimerBack) {
        ui->lbTimer->setText(ui->timeEdit->time().toString(arg1));
        ui->lbTimer2->setText(ui->timeEdit2->time().toString(arg1));
    } else {
        ui->lbTimer->setText(QTime(0, 0).toString(arg1));
        ui->lbTimer2->setText(QTime(0, 0).toString(arg1));
    }
}

void Widget::on_rbTimerBack_toggled(bool checked)
{
    p.isTimerBack = checked;
    if (checked) {
        ui->lbTimer->setText(ui->timeEdit->time().toString(p.timeFormat));
        ui->lbTimer2->setText(ui->timeEdit2->time().toString(p.timeFormat));
    } else {
        ui->lbTimer->setText(QTime(0, 0).toString(p.timeFormat));
        ui->lbTimer2->setText(QTime(0, 0).toString(p.timeFormat));
    }
}
