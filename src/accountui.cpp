#include <QFile>

#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ui->setupUi(this);

    aboutUi = new AboutUi;
    timer = new QTimer;
    timer->start(1000);
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

void AccountUi::infoSlot(Info info)
{
    double flow = info.accountInfo->totalAccurateTraffic/1000/1000/1000;
    double money = info.accountInfo->balance;
    QString flowText = QString::number(flow, 'f', 2) + "GB";
    QString moneyText = QString::number(money, 'f', 2) + "RMB";
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
    }
    delete info.accountInfo;
}

void AccountUi::timeIncrement()
{
    onlineTime++;
    QString timeText = timeForm(onlineTime / 60 / 60) + ":" + timeForm(onlineTime / 60 % 60) + ":" + timeForm(onlineTime % 60);
    ui->timeNumber->setText(timeText);
}

void AccountUi::logoutFailSlot(Info info)
{
    logoutFail = new FailUi(info.accountInfo->error);
    logoutFail->exec();
    delete info.accountInfo;
    logoutFail->deleteLater();
}
