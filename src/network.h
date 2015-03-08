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
    QNetworkReply *queryReply, *loginReply, *logoutReply, *checkReply;

    enum RequestType
    {
        FirstQueryRequest=0,
        SecondQueryRequest,
        ThirdQueryRequest,
    };

    RequestType requestType = FirstQueryRequest; 
    Info queryInfo, loginInfo;
    void getUserInfo(const QString &replyString);
    void getIpInfo(const QString &replyString);

public slots:
    void loginSlot(QString, QString);
    void logoutSlot();
    void querySlot(QString, QString);
    void checkSlot();  //Check whether logged in, and get conneted time.
    void loginAbortSlot(); //Abort login

private slots:
    void queryFinished();
    void loginFinished();
    void logoutFinished();
    void checkFinished();

signals:
    void infoSignal(Info);
    void loginSucceed(Info);
    void logoutSucceed();
    void loginFail(Info);
    void logoutFail(Info);
    void checkResult(Info);
};

#endif // NETWORK_H
