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

    ui->sbChampName->setValue(p.champNameFontSize);
    ui->sbCommand->setValue(p.commandFontSize);
    ui->sbMatch->setValue(p.matchFontSize);
    ui->sbFoul->setValue(p.foulFontSize);
    ui->sbScore->setValue(p.scoreFontSize);
    ui->sbTimer->setValue(p.timerFontSize);

    QString c;
    c.sprintf("background-color: \"%s\";", p.background.toLatin1().data());
    ui->tbSelectBkg->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.color.toLatin1().data());
    ui->tbSelectClr->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.command1Bkg.toLatin1().data());
    ui->tbSelectCmd1Bkg->setStyleSheet(c);
    c.sprintf("background-color: \"%s\";", p.command2Bkg.toLatin1().data());
    ui->tbSelectCmd2Bkg->setStyleSheet(c);

    ui->btOpenLogo->setFocus();

    this->move(200, 50);

    f = new Dialog();
    f->move(this->geometry().topRight());
    f->show();


    p.remainingTime = 0;
    activeTimer = 1;

    connect(p.timer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    refresh = new QTimer(this);
    connect(refresh, SIGNAL(timeout()), this, SLOT(onRefresh()));
    refresh->start(500);

}

Widget::~Widget()
{
//    qDebug("~Widget()");

    delete f;
    delete ui;
}

void Widget::on_btOpenLogo_clicked()
{
    p.logoPath =
            QFileDialog::getOpenFileName(this,
                                         QString("Выберите логотип"),
                                         QDir::currentPath(),
                                         QString("Images (*.png *.jpg);;PNG (*.png);;JPEG (*.jpg)"));

    ui->lbLogo->setStyleSheet(QString("image: url(\"%1\");").arg(p.logoPath));
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
    p.champNameFontSize = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbCommand_valueChanged(int arg1)
{
    p.commandFontSize = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbMatch_valueChanged(int arg1)
{
    p.matchFontSize = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbScore_valueChanged(int arg1)
{
    p.scoreFontSize = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbFoul_valueChanged(int arg1)
{
    p.foulFontSize = arg1;
    if (f) f->changeFonts();
}

void Widget::on_sbTimer_valueChanged(int arg1)
{
    p.timerFontSize = arg1;
    if (f) f->changeFonts();
}


void Widget::on_rb43_toggled(bool checked)
{
    if (f and checked) {
        p.ratio =  4.0 / 3.0;
        f->changeRatio();
    }
}

void Widget::on_rb1610_toggled(bool checked)
{
    if (f and checked) {
        p.ratio =  16.0 / 10.0;
        f->changeRatio();
    }
}

void Widget::on_rb169_toggled(bool checked)
{
    if (f and checked) {
        p.ratio =  16.0 / 9.0;
        f->changeRatio();
    }
}

void Widget::on_cbFullScreen_toggled(bool checked)
{
    if (checked) {
        f->setWindowState(f->windowState() | Qt::WindowFullScreen);
        f->changeFonts();
        this->raise();
        ui->rb43->setEnabled(false);
        ui->rb1610->setEnabled(false);
        ui->rb169->setEnabled(false);
    } else {
        f->setWindowState(f->windowState() & ~Qt::WindowFullScreen);
        f->changeFonts();
        ui->rb43->setEnabled(true);
        ui->rb1610->setEnabled(true);
        ui->rb169->setEnabled(true);
    }
}

void Widget::on_btResetScore_clicked()
{
    if (f) {
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

        f->changeScore();

        ui->btStart->setFocus();
    }
}

void Widget::on_btApplyScore_clicked()
{
    if (f) {
        p.match = ui->sbMatchN->value();
        p.command1Foul = ui->sbFoul1->value();
        p.command1Score = ui->sbScore1->value();
        p.command2Score = ui->sbScore2->value();
        p.command2Foul = ui->sbFoul2->value();
        f->changeScore();

        if (activeTimer == 1) {
            ui->btStart->setFocus();
        } else if (activeTimer == 2) {
            ui->btStart2->setFocus();
        } else if (activeTimer == 3) {
            ui->btStart3->setFocus();
        } else {
            qDebug("!!!!!!!!!!!!!!");
        }
    }
}

void Widget::on_btStart_clicked()
{
    ui->btStop->setEnabled(true);
    ui->btStop2->setEnabled(false);
    ui->btStop3->setEnabled(false);

//    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(false);
    ui->btStart3->setEnabled(false);

    ui->btResetScore->setEnabled(false);

    if (p.timer->isActive()) {
        ui->btStart->setText(QString("Старт"));
        p.remainingTime = p.timer->remainingTime();
        p.timer->stop();
    } else {
        ui->btStart->setText(QString("Пауза"));
        if (p.remainingTime > 0) {
            p.timer->start(p.remainingTime);
        } else {
            QTime t = ui->timeEdit->time();
            int ms = t.hour() * 3600 + t.minute() * 60 + t.second();
            ms *= 1000;
            p.remainingTime = ms;
            activeTimer = 1;
            ui->dial->setMaximum(ms);
            ui->dial->setTickInterval((int) ms / 8);
            p.timer->start(ms);
        }
    }

    ui->btStart->setFocus();
}

void Widget::on_btStop_clicked()
{
    p.timer->stop();
    p.remainingTime = 0;
    ui->dial->setValue(0);

    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStop3->setEnabled(false);

    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(true);
    ui->btStart3->setEnabled(true);

    ui->btStart->setText(QString("Старт"));
    ui->btStart2->setText(QString("Старт"));
    ui->btStart3->setText(QString("Старт"));

    ui->btResetScore->setEnabled(true);

    ui->btStart->setFocus();
}


void Widget::on_btStart2_clicked()
{
    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(true);
    ui->btStop3->setEnabled(false);

    ui->btStart->setEnabled(false);
//    ui->btStart2->setEnabled(false);
    ui->btStart3->setEnabled(false);

    ui->btResetScore->setEnabled(false);

    if (p.timer->isActive()) {
        ui->btStart2->setText(QString("Старт"));
        p.remainingTime = p.timer->remainingTime();
        p.timer->stop();
    } else {
        ui->btStart2->setText(QString("Пауза"));
        if (p.remainingTime > 0) {
            p.timer->start(p.remainingTime);
        } else {
            QTime t = ui->timeEdit2->time();
            int ms = t.hour() * 3600 + t.minute() * 60 + t.second();
            ms *= 1000;
            p.remainingTime = ms;
            activeTimer = 2;
            ui->dial2->setMaximum(ms);
            ui->dial2->setTickInterval((int) ms / 8);
            p.timer->start(ms);
        }
    }

    ui->btStart2->setFocus();
}

void Widget::on_btStop2_clicked()
{
    p.timer->stop();
    p.remainingTime = 0;
    ui->dial2->setValue(0);

    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStop3->setEnabled(false);

    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(true);
    ui->btStart3->setEnabled(true);

    ui->btStart->setText(QString("Старт"));
    ui->btStart2->setText(QString("Старт"));
    ui->btStart3->setText(QString("Старт"));

    ui->btResetScore->setEnabled(true);

    ui->btStart2->setFocus();
}

void Widget::on_btStart3_clicked()
{
    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStop3->setEnabled(true);

    ui->btStart->setEnabled(false);
    ui->btStart2->setEnabled(false);
//    ui->btStart3->setEnabled(false);

    ui->btResetScore->setEnabled(false);

    if (p.timer->isActive()) {
        ui->btStart3->setText(QString("Старт"));
        p.remainingTime = p.timer->remainingTime();
        p.timer->stop();
    } else {
        ui->btStart3->setText(QString("Пауза"));
        if (p.remainingTime > 0) {
            p.timer->start(p.remainingTime);
        } else {
            QTime t = ui->timeEdit3->time();
            int ms = t.hour() * 3600 + t.minute() * 60 + t.second();
            ms *= 1000;
            p.remainingTime = ms;
            activeTimer = 3;
            ui->dial3->setMaximum(ms);
            ui->dial3->setTickInterval((int) ms / 8);
            p.timer->start(ms);
        }
    }

    ui->btStart3->setFocus();
}

void Widget::on_btStop3_clicked()
{
    p.timer->stop();
    p.remainingTime = 0;
    ui->dial3->setValue(0);

    ui->btStop->setEnabled(false);
    ui->btStop2->setEnabled(false);
    ui->btStop3->setEnabled(false);

    ui->btStart->setEnabled(true);
    ui->btStart2->setEnabled(true);
    ui->btStart3->setEnabled(true);

    ui->btStart->setText(QString("Старт"));
    ui->btStart2->setText(QString("Старт"));
    ui->btStart3->setText(QString("Старт"));

    ui->btResetScore->setEnabled(true);

    ui->btStart->setFocus();
}


void Widget::onTimeout()
{
//    p.timer = 0;
    if (activeTimer == 1) {
        on_btStop_clicked();
        on_btStart2_clicked();
    } else if (activeTimer == 2) {
        on_btStop2_clicked();
        ++p.match;
        ui->sbMatchN->stepUp();
        f->changeScore();
        on_btStart3_clicked();
    } else if (activeTimer == 3) {
        on_btStop3_clicked();
        activeTimer = 1;
    } else {
        qDebug("!!!!!!!!!!!!!!");
    }
}

void Widget::onRefresh()
{
    if (p.timer->isActive()) {
        int r = p.timer->remainingTime();
        if (activeTimer == 1) {
            ui->dial->setValue(r);
        } else if (activeTimer == 2) {
            ui->dial2->setValue(r);
        } else if (activeTimer == 3) {
            ui->dial3->setValue(r);
        } else {
            qDebug("!!!!!!!!!!!!!!");
        }
    }
}

void Widget::selectColor(QToolButton *b, QString &elem)
{
    QColor color = QColorDialog::getColor(elem, this, "Выберите цвет");

    if (color.isValid()) {
        elem = color.name();

        qDebug("%s", elem.toLatin1().data());

        QString c;
        c.sprintf("background-color: \"%s\";", elem.toLatin1().data());
        b->setStyleSheet(c);
    }

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

void Widget::on_tbSelectCmd2Bkg_clicked()
{
    selectColor(ui->tbSelectCmd2Bkg, p.command2Bkg);
}
