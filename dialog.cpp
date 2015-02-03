#include "dialog.h"
#include "ui_dialog.h"
#include <QKeyEvent>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
//    qDebug("Dialog()");

    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

    changeTexts();
    changeScore();
    changeRatio();

    refresh = new QTimer(this);
    connect(refresh, SIGNAL(timeout()), this, SLOT(onRefresh()));
    refresh->start(200);
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

    ui->lbFoul1->setEnabled(p.command1Foul < 6);
    ui->lbFoul2->setEnabled(p.command2Foul < 6);
}


void Dialog::onRefresh()
{
    QString str;
    int t;
    if (p.timer->isActive())
        t = p.timer->remainingTime();
    else
        t = p.remainingTime;
    int h = t / 3600000;
    int m = t % 3600000 / 60000;
    int s = t % 60000 / 1000;
    int ms = t % 1000;
    str.sprintf("%1d:%02d:%02d.%03d", h, m, s, ms);
//    str.sprintf("%02d:%02d", m, s);
    ui->lbTimer->setText(str);
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

void Dialog::calculateStyle()
{
    int w = this->geometry().width();
    int h = this->geometry().height();
    float coff = w / 640.0;

    int size1 = (int) (p.champNameFontSize * coff);
    int size2 = (int) (p.commandFontSize * coff);
    int size3 = (int) (p.matchFontSize * coff);
    int size4 = (int) (p.scoreFontSize * coff);
    int size5 = (int) (p.foulFontSize * coff);
    int size6 = (int) (p.timerFontSize * coff);
    int size7 = (int) (2.0 * coff);
    int size8 = (int) (7.0 * coff);
    int size9 = (int) (15.0 * coff);
//    qDebug("%d, %d, %d, %d, %d, %d", size1, size2, size3, size4, size5, size6);

    static const QString fmt = QString("\
* {\n\
font: 900 %5px \"Arial\";\n\
background-color: \"%1\";\n\
color: \"%2\";\n\
margin: %12px;\n\
border-color: \"%2\";\n\
border-width: %11px;\n\
border-style: solid;\n\
border-radius: %12px;\n\
}\n\
#lbChampName {font-size: %5px;}\n\
#lbCommand1 {font-size: %6px; background-color: \"%3\"}\n\
#lbMatch    {font-size: %7px;}\n\
#lbCommand2 {font-size: %6px; background-color: \"%4\"}\n\
#lbFoul1    {font-size: %9px;}\n\
#lbScore1   {font-size: %8px;}\n\
#lbScoreDivisor {font-size: %8px;}\n\
#lbScore2   {font-size: %8px;}\n\
#lbFoul2    {font-size: %9px;}\n\
#lbTimer    {font-size: %10px;}\n\
\n\
#Dialog, #lbScoreDivisor {\n\
border-width: 0;\n\
}\n\
#lbLogo {\n\
border-color: \"%1\";\n\
}\n\
#lbFoul1, #lbFoul2 {\n\
margin: %13px;\n\
}\n\
#lbFoul1:enabled, #lbFoul2:enabled {\n\
background-color: \"#c0439163\";\n\
}\n\
#lbFoul1:disabled, #lbFoul2:disabled {\n\
background-color: \"#c098514e\";\n\
}");

    const QString style = fmt
            .arg(p.background).arg(p.color).arg(p.command1Bkg).arg(p.command2Bkg)
            .arg(size1).arg(size2).arg(size3).arg(size4).arg(size5).arg(size6)
            .arg(size7).arg(size8).arg(size9);

    this->setStyleSheet(style);

}
