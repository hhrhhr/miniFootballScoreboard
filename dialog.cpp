#include "dialog.h"
#include "ui_dialog.h"
#include <QKeyEvent>
#include <QTime>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
//    qDebug("Dialog()");

    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    ui->lbTimer->setText(QTime(0, 0).toString(p.timeFormat));

    changeTexts();
    changeScore();
    changeRatio();

    refresh = new QTimer(this);
    connect(refresh, SIGNAL(timeout()), this, SLOT(onRefresh()));
    refresh->start(333);
}

Dialog::~Dialog()
{
//    qDebug("~Dialog()");
    delete ui;
}

void Dialog::changeTexts() {

    ui->lbLogo->setStyleSheet(QString("image: url(\"%1\");").arg(p.logoPath));

    ui->lbChampName->setText(p.champName);
    ui->lbCommand1->setText(p.command1);
    ui->lbCommand2->setText(p.command2);
}

void Dialog::changeRatio()
{
//    qDebug("%f", p.ratio);

    QRect g = this->geometry();
    g.setWidth(360 * p.ratio);
    this->setGeometry(g);
}

void Dialog::changeFonts()
{
    calculateStyle();
}

void Dialog::changeScore()
{
    ui->lbMatch->setText(QString::number(p.match));
    ui->lbFoul1->setText(QString::number(p.command1Foul));
    ui->lbScore1->setText(QString::number(p.command1Score));
    ui->lbScore2->setText(QString::number(p.command2Score));
    ui->lbFoul2->setText(QString::number(p.command2Foul));

    ui->lbFoul1->setEnabled(p.command1Foul < 5);
    ui->lbFoul2->setEnabled(p.command2Foul < 5);
}


void Dialog::onRefresh()
{
    if (p.timer->isValid()) {
        int t = p.timeout - p.timer->elapsed();
        if (t > 0) {
            if (!p.isTimerBack)
                t = p.timer->elapsed();
            ui->lbTimer->setText(QTime::fromMSecsSinceStartOfDay(t).toString(p.timeFormat));
        } else {
            ui->lbTimer->setText(QTime(0, 0).toString(p.timeFormat));
        }
    }
}

void Dialog::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    calculateStyle();
}

void Dialog::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape)
        return QDialog::keyPressEvent(e);
}

void Dialog::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e);
    this->setWindowState(this->windowState() ^ Qt::WindowFullScreen);
    changeFonts();
}

void Dialog::calculateStyle()
{
    int w = this->geometry().width();
    int h = this->geometry().height(); Q_UNUSED(h);
    float coff = w / 640.0;

    int size1 = (int) (p.champNameFontSz * coff);
    int size2 = (int) (p.commandFontSz * coff);
    int size3 = (int) (p.matchFontSz * coff);
    int size4 = (int) (p.scoreFontSz * coff);
    int size5 = (int) (p.foulFontSz * coff);
    int size6 = (int) (p.timerFontSz * coff);
    int size7 = (int) (2.0 * coff);
    int size8 = (int) (7.0 * coff);
    int size9 = (int) (15.0 * coff);
//    qDebug("%d, %d, %d, %d, %d, %d", size1, size2, size3, size4, size5, size6);

    static const QString fmt1 = QString("\
* {\n\
font: %1 %2 %3px \"%4\";\n\
background-color: \"%5\";\n\
color: \"%6\";\n\
margin: %7px;\n\
padding: 0;\n\
border-color: \"%8\";\n\
border-width: %9px;\n\
border-style: solid;\n\
border-radius: %10px;\n\
}\n\
#lbChampName, #lbCommand1, #lbCommand2 {font: %11 %12 %13px \"%14\"}\n\
#lbCommand1, #lbCommand2 {font-size: %15px;}\n\
#lbCommand1 {background-color: \"%16\"; color: \"%17\"}\n\
#lbCommand2 {background-color: \"%18\"; color: \"%19\"}\n\
");
    static const QString fmt2 = QString("\
#lbMatch {font-size: %1px;}\n\
#lbFoul1, #lbFoul2 {font-size: %2px; margin: %3px;}\n\
#lbFoul1:enabled, #lbFoul2:enabled {background-color: \"%4\";}\n\
#lbFoul1:disabled, #lbFoul2:disabled {background-color: \"%5\";}\n\
#lbScore1, #lbScore2, #lbScoreDivisor {font-size: %6px;}\n\
#lbTimer {font-size: %7px; color: \"%8\";}\n\
#Dialog, #lbScoreDivisor, #lbScore1, #lbScore2 {border-width: 0;}\n\
#lbLogo {border-color: \"%9\";}\n\
");

    const QString style = fmt1
            .arg(p.fontWeight).arg(p.fontStyle).arg(size1).arg(p.fontName).arg(p.background)
            .arg(p.color).arg(size7).arg(p.color).arg(size7).arg(size8)
            .arg(p.font2Weight).arg(p.font2Style).arg(size1).arg(p.font2Name).arg(size2)
            .arg(p.command1Bkg).arg(p.command1Clr).arg(p.command2Bkg).arg(p.command2Clr)
            .append(fmt2
            .arg(size3).arg(size5).arg(size9).arg(p.foulGreenBkg).arg(p.foulRedBkg)
            .arg(size4).arg(size6).arg(p.timerClr).arg(p.background));

//    qDebug("%s", style.toLatin1().data());

    this->setStyleSheet(style);

}
