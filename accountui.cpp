#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ui->setupUi(this);
}

AccountUi::~AccountUi()
{
    delete ui;
}

AccountUi::logoutSignal()
{
}
