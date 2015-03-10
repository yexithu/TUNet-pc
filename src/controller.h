#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "loadingui.h"
#include "network.h"
#include <QTimer>
#include <QAction>
#include <QMenu>

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
    QMenu *trayMenu;
    QSystemTrayIcon *trayIcon;
    enum kind{change, login, loading, account} last;

signals:
    void querySignal(QString, QString);
    void checkSignal();

private slots:
    void setTimer();
    void onTimeOut();
    void onLoginStart(QString);
    void onLoginSucceed();
    void onLogoutSucceed();
    void onLoginFail();
    void showUi(kind);
    void creatTrayMenu();
    void quit();
    void showHide();
    void trayIconClicked(QSystemTrayIcon::ActivationReason);
};

#endif // CONTROLLER_H
