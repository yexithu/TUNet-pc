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
}

AccountUi::~AccountUi()
{
    delete ui;
}

void AccountUi::logoutClicked()
{
    emit logoutSignal();
}

QString timeForm(int k)
{
    if (k < 10)
        return "0" + QString::number(k);
    else
        return QString::number(k);
}

QString trafficForm(double flow)
{
    if (flow < 1E3) {
        return QString::number(flow, 'f', 0) + "B";
    }
    else if (flow < 1E6) {
        return QString::number(flow/1E3, 'f', 2) + "KB";
    }
    else if (flow < 1E9) {
        return QString::number(flow/1E6, 'f', 2) + "MB";
    }
    else{
        return QString::number(flow/1E9, 'f', 2) + "GB";
    }
}
void AccountUi::infoSlot(Info info)
{
    QString flowText, moneyText;
    if (info.infoType == Info::LoginInfo) {
        flowText = ">=" + trafficForm(info.accountInfo->roughTraffic);
        moneyText = "Loading...";
    }
    else {
        flowText = trafficForm(info.accountInfo->totalAccurateTraffic);
        moneyText = QString::number(info.accountInfo->balance, 'f', 2) + "RMB";
    }
    ui->username->setText(info.accountInfo->userName);
    ui->flowNumber->setText(flowText);
    ui->moneyNumber->setText(moneyText);
    delete info.accountInfo;
}

void AccountUi::checkResultSlot(Info info)
{
    int timeReceived = info.accountInfo->loginTime;
    if (onlineTime != timeReceived) {
        onlineTime = timeReceived;
        timer->start(1000);
    }
    delete info.accountInfo;
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
    logoutFail = new FailUi(info.accountInfo->error);
    logoutFail->exec();
    delete info.accountInfo;
    logoutFail->deleteLater();
}
