#include <QFile>

#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ui->setupUi(this);

    aboutUi = new AboutUi;

    QFile *file = new QFile(":qss/qss/accountui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());

    connect(ui->aboutButton, SIGNAL(clicked()),
            aboutUi, SLOT(exec()));
    connect(ui->logoutButton, SIGNAL(clicked()),
            this, SLOT(logoutClicked()));
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
    double flow = info.accountInfo->totalAccurateTraffic/1000/1000/1000;
    int time = this -> onlineTime;
    double money = info.accountInfo->balance;
    QString flowText = QString::number(flow, 'f', 2)+"GB";
    QString timeText = QString::number(time / 60 / 60)+":"+QString::number(time / 60 % 60)+":"+QString::number(time % 60);
    QString moneyText = QString::number(money, 'f', 2)+"RMB";
    ui->flowNumber->setText(flowText);
    ui->timeNumber->setText(timeText);
    ui->moneyNumber->setText(moneyText);

}

void AccountUi::logoutFail(Info info)
{
}
