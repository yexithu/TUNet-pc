#include "controller.h"

Controller::Controller()
{
    network = new Network;
    loginUi = new LoginUi;
    accountUi = new AccountUi;

    //登陆
    connect(loginUi, SIGNAL(loginSignal(QString, QString)),
            network, SLOT(loginSlot(QString, QString)));

    //登陆成功
    connect(network, SIGNAL(infoSignal(Info)),
            accountUi, SLOT(infoSlot(Info)));
    connect(network, SIGNAL(infoSignal(Info)),
            loginUi, SLOT(hide()));
    connect(network, SIGNAL(infoSignal(Info)),
            accountUi, SLOT(show()));

    //登录失败
    connect(network, SIGNAL(loginFail(Info)),
            loginUi, SLOT(loginFail(Info)));
    connect(network, SIGNAL(loginFail(Info)),
            loginUi, SLOT(show()));
    connect(network, SIGNAL(loginFail(Info)),
            accountUi, SLOT(hide()));


    //断开
    connect(accountUi, SIGNAL(logoutSignal()),
            network, SLOT(logoutSlot()));

    //断开成功
    connect(network, SIGNAL(logoutSucceed()),
            loginUi, SLOT(show()));
    connect(network, SIGNAL(logoutSucceed()),
            accountUi, SLOT(hide()));

    //断开失败
    connect(network, SIGNAL(logoutFail(Info)),
            accountUi, SLOT(logoutFail(Info)));
}

Controller::~Controller()
{
}
