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
    info.infoType = Info::QueryInfo;
    info.accountInfo = new AccountInfo;
    info.accountInfo->userName = username;//设置info的用户名

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
    {
        if (replyString == "ok")
        {
            requestType = Network::SecondQueryRequest;
            QNetworkRequest secondQueryRequest;
            secondQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/user_info.php"));
            manager->get(secondQueryRequest);
        }
        break;
    }
    case Network::SecondQueryRequest:
    {
        requestType = Network::ThirdQueryRequest;
        QNetworkRequest thirdQueryRequest;
        thirdQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));
        manager->get(thirdQueryRequest);
        break;
    }
    case Network::ThirdQueryRequest:
    {
        getIpInfo(replyString);
        emit infoSignal(info);
        requestType = LoginRequest;
        break;
    }
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
    QString temp;
    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");

    //获取余额
    temp = all[42].toPlainText();
    info.accountInfo->balance = temp.left(temp.length() - 3).toDouble();
    //获取登陆时流量
    temp = all[36].toPlainText();
    for (int i = 0; i < temp.length(); i++)
    {
        if (temp[i] == '(')
        {
            temp = temp.left(i);
            break;
        }
    }
    info.accountInfo->roughTraffic = temp.toDouble();
}

void Network::getIpInfo(const QString &replyString)
{
    //移除注释
    QString replyStringPlus = replyString;
    replyStringPlus.remove("<!--", Qt::CaseSensitive);
    replyStringPlus.remove("<!--", Qt::CaseSensitive);
    QWebPage page;
    QWebFrame *frame = page.mainFrame();
    frame->setHtml(replyStringPlus);

    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");
    QString temp;

    info.accountInfo->onlineIpCount = (all.count() - 23) / 20;
    info.accountInfo->ipInfo = new IpInfo[info.accountInfo->onlineIpCount];
    info.accountInfo->totalAccurateTraffic = info.accountInfo->roughTraffic;
    for (int i = 0; i < info.accountInfo->onlineIpCount; i++)
    {
        //ip地址
        temp = all[27 + 20 * i].toPlainText();
        int dotAdress[3];
        for (int k = 0, j = 0; k < temp.length(); k++)
        {
            if (temp[k] == '.')
            {
                dotAdress[j] = k;
                j++;
            }
        }
        info.accountInfo->ipInfo[i].ipv4_Ip[0] = temp.left(dotAdress[0]).toInt();
        info.accountInfo->ipInfo[i].ipv4_Ip[1] = temp.mid(dotAdress[0] + 1, dotAdress[1] - dotAdress[0] - 1).toInt();
        info.accountInfo->ipInfo[i].ipv4_Ip[2] = temp.mid(dotAdress[1] + 1, dotAdress[2] - dotAdress[1] - 1).toInt();
        info.accountInfo->ipInfo[i].ipv4_Ip[3] = temp.mid(dotAdress[2] + 1).toInt();
        
        //入流量
        temp = all[28 + 20 * i].toPlainText();
        info.accountInfo->ipInfo[i].accurateTraffic = temp.left(temp.length() - 1).toDouble();
        if (temp[temp.length() - 1] == 'K')  info.accountInfo->ipInfo[i].accurateTraffic *= 1024;
        if (temp[temp.length() - 1] == 'M')  info.accountInfo->ipInfo[i].accurateTraffic *= (1024 * 1024);
        if (temp[temp.length() - 1] == 'G')  info.accountInfo->ipInfo[i].accurateTraffic *= (1024 * 1024 * 1024);
        info.accountInfo->totalAccurateTraffic += info.accountInfo->ipInfo[i].accurateTraffic;

        //时间
        temp = all[38 + 20 * i].toPlainText();
        info.accountInfo->ipInfo[i].onlineTime[0] = temp.mid(temp.length() - 8, 2).toInt();
        info.accountInfo->ipInfo[i].onlineTime[1] = temp.mid(temp.length() - 5, 2).toInt();
        info.accountInfo->ipInfo[i].onlineTime[2] = temp.mid(temp.length() - 2, 2).toInt();
        //mac
        temp = all[41 + 20 * i].toPlainText();
        info.accountInfo->ipInfo[i].macAdress = temp;
    }


}