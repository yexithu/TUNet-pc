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

void IpUi::logoutClicked()
{
    emit logoutRequest(order);
}
