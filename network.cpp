#include "network.h"

Network::Network()
{
    manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(replyFinished(QNetworkReply*)));
}

Network::~Network()
{
}

void Network::loginSlot(QString username, QString password)
{
}

void Network::logoutSlot()
{
}

void Network::querySlot(QString username, QString password)
{
    //设置info类型以及实例化info
    info->infoType = Info::QueryInfo;
    info->accountInfo = new AccountInfo;
    info->accountInfo->userName = username;//设置info的用户名

    QByteArray postData;
    QNetworkRequest request;
    postData.append("action=login"); postData.append("&" + username); postData.append("&" + password);
    request.setUrl(QUrl("http://usereg.tsinghua.edu.cn/do.php"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    manager->post(request, postData);
    requestType = Network::FirstQueryRequest;
}

void Network::replyFinished(QNetworkReply* reply)
{
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply

    switch (requestType)
    {
    case Network::LoginRequest:
        break;
    case Network::LogoutRequest:
        break;
    case Network::FirstQueryRequest:
        if (replyString == "ok")
        {
            requestType = Network::SecondQueryRequest;
            QNetworkRequest requestPlus;
            requestPlus.setUrl(QUrl("http://usereg.tsinghua.edu.cn/user_info.php"));
            manager->get(requestPlus);
        }
        break;
    case Network::SecondQueryRequest:
        
        break;
    case Network::ThirdQueryRequest:
        break;
    default:
        break;
    }
}


//解析http://usereg.tsinghua.edu.cn/user_info.php
//并修改信息
void Network::getUserInfo(const QString &replyString)
{
    QWebPage page;
    QWebFrame *frame = page.mainFrame();
    frame->setHtml(replyString);

    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");
    info->accountInfo->balance;
}

void Network::getIpInfo(const QString &replyString)
{
}