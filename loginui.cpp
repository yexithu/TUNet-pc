#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    connect(ui->autoLogin, SIGNAL(stateChanged(int)),
            this, SLOT(selectSavePassword(int)));
    connect(ui->savePassword, SIGNAL(stateChanged(int)),
            this, SLOT(disselectAutoLogin(int)));
}

void LoginUi::selectSavePassword(int state)
{
    if (state==Qt::Checked)
        ui->savePassword->setCheckState(Qt::Checked);
}

void LoginUi::disselectAutoLogin(int state)
{
    if (state==Qt::Unchecked)
        ui->autoLogin->setCheckState(Qt::Unchecked);
}

LoginUi::~LoginUi()
{
    delete ui;
}
