#ifndef NETWORK_H
#define NETWORK_H

#include "controller.h"

class Network
{
public:
    Network();
    ~Network();
    void login(QString username, QString password); // 利用post方式向网站发出登陆请求
    void logout();                                  // 利用get方式向网站发出登出请求
    void query(QString username, QString password); // 利用post方式向usereg发出登陆请求

private:
    QNetworkAccessManager *loginManager;
    QNetworkAccessManager *logoutManager;
    QNetworkAccessManager *queryManager;

/*
 * 由于QNetworkAccessManager会自己发射finished(QNetworkReply*)信号，因此这几行不用写
 *
signals:
    void loginFinished(QString respond);
    void logoutFinished(QString respond);
    void queryFinished(QString respond);
*/

//  各QNetworkAccessManager发出finished()信号后的接受槽，用于显示登陆/登出/流量控制等信息
private slots:
    void loginReplyFinished(QNetworkReply *);
    void logoutReplyFinished(QNetworkReply *);
    void queryFinished(QNetworkReply *);
};

#endif // NETWORK_H
