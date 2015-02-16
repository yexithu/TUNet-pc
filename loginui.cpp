#include <cstdio>
#include <algorithm>

#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    LoginUi::loadInfo();
    ui->password->setEchoMode(QLineEdit::Password);
    connect(ui->autoLogin, SIGNAL(stateChanged(int)),
            this, SLOT(selectSavePassword(int)));
    connect(ui->savePassword, SIGNAL(stateChanged(int)),
            this, SLOT(disselectAutoLogin(int)));
    connect(ui->loginButton, SIGNAL(clicked()),
            this, SLOT(saveInfo()));
}

LoginUi::~LoginUi()
{
    delete ui;
}

void LoginUi::selectSavePassword(int state)
{
    if (state == Qt::Checked)
        ui->savePassword->setCheckState(Qt::Checked);
}

void LoginUi::disselectAutoLogin(int state)
{
    if (state == Qt::Unchecked)
        ui->autoLogin->setCheckState(Qt::Unchecked);
}

void LoginUi::loadInfo()
{
    if (settings.value("savePassword", false).toBool())
        ui->savePassword->setCheckState(Qt::Checked);
    if (settings.value("autoLogin", false).toBool())
        ui->autoLogin->setCheckState(Qt::Checked);
    ui->username->setText(settings.value("username", "").toString());
    ui->password->setText(settings.value("password", "").toString());
}

void LoginUi::saveInfo()
{
    settings.setValue("savePassword", ui->savePassword->checkState() == Qt::Checked);
    settings.setValue("autoLogin", ui->autoLogin->checkState() == Qt::Checked);
    settings.setValue("username", ui->username->text());
    if (ui->savePassword->checkState() == Qt::Checked)
        settings.setValue("password", ui->password->text());
    else
        settings.setValue("password", "");
}
