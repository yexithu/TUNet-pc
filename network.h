#ifndef NETWORK_H
#define NETWORK_H

#include "info.h"
#include <QObject>
#include <QtNetwork>
#include <QtWebKit>
#include <QtWebKitWidgets>

class Network : public QObject
{
    Q_OBJECT

public:
    Network();
    ~Network();
private:
    QNetworkAccessManager *manager;
    enum RequestType
    {
        LoginRequest = 0,
        LogoutRequest,
        FirstQueryRequest,
        SecondQueryRequest,
        ThirdQueryRequest,
    };
    RequestType requestType = LoginRequest; 
    Info *info;

    void getUserInfo(const QString &replyString);
    void getIpInfo(const QString &replyString);
public slots:
    void loginSlot(QString, QString);
    void logoutSlot();
    void querySlot(QString, QString);

private slots:
    void replyFinished(QNetworkReply*);
signals:
    void infoSignal(Info);
    void loginSucceed(Info);
    void logoutSucceed();
    void loginFail(Info);
    void logoutFail(Info);

};

#endif // NETWORK_H
