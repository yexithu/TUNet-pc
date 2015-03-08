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

#include <QDebug>
void AccountUi::infoSlot(Info info)
{
    qDebug()<<info.accountInfo->totalAccurateTraffic;
    qDebug()<<info.accountInfo->loginTime;
    qDebug()<<info.accountInfo->balance;
    double tmp1=10;
    double tmp2=20;
    double tmp3=30;
    QString flow = QString::number(tmp1, 'f', 2)+"GB";
    QString time = QString::number(tmp2, 'f', 0)+":"+QString::number(tmp2, 'f', 0)+":"+QString::number(tmp2, 'f', 0);
    QString money = QString::number(tmp3, 'f', 2)+"RMB";
    ui->flowNumber->setText(flow);
    ui->timeNumber->setText(time);
    ui->moneyNumber->setText(money);

}

void AccountUi::logoutFail(Info info)
{
}
