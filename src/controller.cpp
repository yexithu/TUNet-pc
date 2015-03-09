#include "controller.h"

Controller::Controller()
{
    network = new Network;
    loginUi = new LoginUi;
    loadingUi = new LoadingUi;
    accountUi = new AccountUi;
    timer = new QTimer;
    timer->stop();
    loginUi->show();
    trayIcon = new QSystemTrayIcon;
    trayIcon->setIcon(QIcon(":/imgs/images/logo.png"));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), accountUi, SLOT(showNormal()));
    //登陆
    connect(loginUi, SIGNAL(loginSignal(QString, QString)),
            network, SLOT(loginSlot(QString, QString)));
    connect(loginUi, SIGNAL(loginSignal(QString, QString)),
            this, SLOT(onLoginStart(QString)));

    //登陆成功
    connect(network, SIGNAL(loginSucceed(Info)),
            accountUi, SLOT(infoSlot(Info)));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(onLoginSucceed()));
    connect(network, SIGNAL(loginSucceed(Info)),
            this, SLOT(setTimer()));
    
    //登录失败
    connect(network, SIGNAL(loginFail(Info)),
            loginUi, SLOT(loginFailDialog(Info)));
    connect(network, SIGNAL(loginFail(Info)),
            this, SLOT(onLoginFail()));
    //Abort login
    connect(loadingUi, SIGNAL(loginAbort()), network, SLOT(loginAbortSlot()));

    //定时查询
    connect(timer, SIGNAL(timeout()),
            this, SLOT(onTimeOut()));
    connect(this, SIGNAL(checkSignal()), network, SLOT(checkSlot()));
    connect(network, SIGNAL(checkResult(Info)), accountUi, SLOT(checkResultSlot(Info)));
    connect(this, SIGNAL(querySignal(QString, QString)),
            network, SLOT(querySlot(QString, QString)));
    connect(network, SIGNAL(infoSignal(Info)),
            accountUi, SLOT(infoSlot(Info)));

    //断开
    connect(accountUi, SIGNAL(logoutSignal()),
            network, SLOT(logoutSlot()));

    //断开成功
    connect(network, SIGNAL(logoutSucceed()),
            loginUi, SLOT(show()));
    connect(network, SIGNAL(logoutSucceed()),
            accountUi, SLOT(hide()));
    connect(network, SIGNAL(logoutSucceed()),
            timer, SLOT(stop()));

    //断开失败
    connect(network, SIGNAL(logoutFail(Info)),
            accountUi, SLOT(logoutFailSlot(Info)));

}

void Controller::setTimer()
{
    timer->start(30000);
}

void Controller::onTimeOut()
{
    emit checkSignal();
    emit querySignal(loginUi->username, loginUi->password);
}

void Controller::onLoginStart(QString username)
{
    loginUi->setEnabled(false);
    loadingUi->setUsername(username);
    loadingUi->show();
}

void Controller::onLoginSucceed()
{
    trayIcon->show();
    loginUi->setEnabled(true);
    loginUi->hide();
    loadingUi->hide();
    accountUi->show();
    emit checkSignal();
    emit querySignal(loginUi->username, loginUi->password);
}

void Controller::onLoginFail()
{
    loginUi->setEnabled(true);
    loadingUi->hide();
}

Controller::~Controller()
{
}
