#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "loadingui.h"
#include "network.h"
#include <QTimer>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();

private:
    QTimer *timer;
    Network *network;
    LoginUi *loginUi;
    LoadingUi *loadingUi;
    AccountUi *accountUi;

signals:
    void querySignal(QString, QString);
    void checkSignal();

private slots:
    void setTimer();
    void onTimeOut();
    void onLoginStart(QString);
    void onLoginSucceed();
    void onLoginFail();
};

#endif // CONTROLLER_H
