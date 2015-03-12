#include <QFile>
#include <QDebug>
#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ui->setupUi(this);
    aboutUi = new AboutUi;
    timer = new QTimer;
    QFile *file = new QFile(":qss/qss/accountui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    connect(ui->aboutButton, SIGNAL(clicked()),
            aboutUi, SLOT(exec()));
    connect(ui->logoutButton, SIGNAL(clicked()),
            this, SLOT(logoutClicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timeIncrement()));

    ip[0] = new IpUi(0);
    ip[1] = new IpUi(1);
    ip[2] = new IpUi(2);
    ui->verticalLayout_2->addWidget(ip[0]);
    ui->verticalLayout_2->addWidget(ip[1]);
    ui->verticalLayout_2->addWidget(ip[2]);

    this->setFixedSize(320, 340);
    ui->extendWidget->setVisible(false);
    ui->extendButton->setCheckable(true);

    connect(ui->extendButton, SIGNAL(toggled(bool)),
            this, SLOT(adjustWindow(bool)));
}

AccountUi::~AccountUi()
{
    delete ui;
}

void AccountUi::logoutClicked()
{
    emit logoutSignal();
}

void AccountUi::infoSlot(Info info)
{

    QString flowText, moneyText;
    if (info.infoType == Info::LoginInfo) {
        flowText = ">=" + info.accountInfo.ipInfo[0].trafficForm(info.accountInfo.roughTraffic);
        moneyText = "Loading...";
    }
    else {
        flowText = info.accountInfo.ipInfo[0].trafficForm(info.accountInfo.totalAccurateTraffic);
        moneyText = QString::number(info.accountInfo.balance, 'f', 2) + "RMB";
    }
    ui->username->setText(info.accountInfo.userName);
    ui->flowNumber->setText(flowText);
    ui->moneyNumber->setText(moneyText);

    for (int i = 0; i < std::min(info.accountInfo.onlineIpCount, 3); ++i)
        ip[i]->showIp(info.accountInfo.ipInfo[i]);

    for (int i = std::max(info.accountInfo.onlineIpCount, 0); i < 3; ++i)
        ip[i]->hideIp();

}

void AccountUi::checkResultSlot(Info info)
{
    int timeReceived = info.accountInfo.loginTime;
    if (onlineTime != timeReceived) {
        onlineTime = timeReceived;
        timer->start(1000); 
    }
}

QString timeForm(int k)
{
    if (k < 10)
        return "0" + QString::number(k);
    else
        return QString::number(k);
}

void AccountUi::timeIncrement()
{
    if (onlineTime >= 0) {
        onlineTime++;
        QString timeText = timeForm(onlineTime / 60 / 60) + ":" + timeForm(onlineTime / 60 % 60) + ":" + timeForm(onlineTime % 60);
        ui->timeNumber->setText(timeText);
    }
    else {
        ui->timeNumber->setText("Loading...");
    }
}

void AccountUi::logoutFailSlot(Info info)
{
    logoutFail = new FailUi(info.accountInfo.error);
    logoutFail->exec();
    logoutFail->deleteLater();
}

void AccountUi::adjustWindow(bool state)
{
    ui->extendWidget->setVisible(state);
    if (state)
        this->setFixedSize(320, 425);
    else
        this->setFixedSize(320, 340);
}

void AccountUi::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
