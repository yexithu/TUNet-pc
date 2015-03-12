#include "ipui.h"
#include "ui_ipui.h"

IpUi::IpUi(int orderNumber, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IpUi)
{
    ui->setupUi(this);

    QFile *file = new QFile(":qss/qss/ipui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();

    order = orderNumber;
    connect(ui->logout, SIGNAL(clicked()),
            this, SLOT(logoutClicked()));
}

IpUi::~IpUi()
{
	delete ui;
}

void IpUi::showIp(IpInfo info)
{
    ui->name->show();
    ui->time->show();
    ui->traffic->show();
    ui->logout->show();
    ui->name->setText(info.macAdress);
    ui->time->setText(info.timeForm(info.onlineTime[0]) + ":" +
                      info.timeForm(info.onlineTime[1]) + ":" +
                      info.timeForm(info.onlineTime[2]));
    ui->traffic->setText(info.trafficForm(info.accurateTraffic));
}

void IpUi::hideIp()
{
    ui->name->hide();
    ui->time->hide();
    ui->traffic->hide();
    ui->logout->hide();
}

void IpUi::logoutClicked()
{
    emit logoutRequest(order);
}
