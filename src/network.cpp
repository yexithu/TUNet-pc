#include "network.h"

Network::Network()
{
    manager = new QNetworkAccessManager;
}

Network::~Network()
{
}

void Network::querySlot(QString username, QString password)
{
    //Generate MD5 hash of the password
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();

    //设置queryInfo类型以及实例化queryInfo
    queryInfo.infoType = Info::QueryInfo;
    queryInfo.accountInfo = new AccountInfo;
    queryInfo.accountInfo->userName = username;  //设置queryInfo的用户名

    QByteArray postData;
    QNetworkRequest request;
    postData.append("action=login");
    postData.append("&user_login_name=" + username);
    postData.append("&user_password=" + hashedPassword);
    request.setUrl(QUrl("http://usereg.tsinghua.edu.cn/do.php"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, postData.length());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    queryReply = manager->post(request, postData);
    connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
    requestType = Network::FirstQueryRequest;
}

void Network::queryFinished()
{
    QNetworkReply *reply = queryReply;
    QString replyString;
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    replyString = codec->toUnicode((reply->readAll()));
    //读取reply
    switch (requestType) {
    case Network::FirstQueryRequest: {
        if (replyString == "ok") {
            requestType = Network::SecondQueryRequest;
            QNetworkRequest secondQueryRequest;
            secondQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/user_info.php"));
            queryReply = manager->get(secondQueryRequest);
            connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
        }
        break;
    }

    case Network::SecondQueryRequest: {
        getUserInfo(replyString);
        requestType = Network::ThirdQueryRequest;
        QNetworkRequest thirdQueryRequest;
        thirdQueryRequest.setUrl(QUrl("http://usereg.tsinghua.edu.cn/online_user_ipv4.php"));
        queryReply = manager->get(thirdQueryRequest);
        connect(queryReply, SIGNAL(finished()), this, SLOT(queryFinished()));
        break;
    }
            
    case Network::ThirdQueryRequest: {
        getIpInfo(replyString);
        emit infoSignal(queryInfo);
        requestType = FirstQueryRequest;
        break;
    }
            
    default: {
        break;
    }    
    }
    reply->deleteLater();
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
    queryInfo.accountInfo->balance = temp.left(temp.length() - 3).toDouble();
    //获取登陆时流量
    temp = all[36].toPlainText();
    for (int i = 0; i < temp.length(); i++) {
        if (temp[i] == '(') {
            temp = temp.left(i);
            break;
        }
    }
    queryInfo.accountInfo->roughTraffic = temp.toDouble();
    frame->deleteLater();
}

void Network::getIpInfo(const QString &replyString)
{
    //移除注释
    QString replyStringPlus = replyString;
    replyStringPlus.remove("<!--", Qt::CaseSensitive);
    replyStringPlus.remove("-->", Qt::CaseSensitive);
    QWebPage page;
    QWebFrame *frame = page.mainFrame();
    frame->setHtml(replyStringPlus);

    QWebElement doc = frame->documentElement();
    QWebElement body = doc.findFirst("body");
    QWebElementCollection all = body.findAll("td");
    QString temp;

    queryInfo.accountInfo->onlineIpCount = (all.count() - 23) / 20;
    queryInfo.accountInfo->ipInfo = new IpInfo[queryInfo.accountInfo->onlineIpCount];
    queryInfo.accountInfo->totalAccurateTraffic = queryInfo.accountInfo->roughTraffic;
    for (int i = 0; i < queryInfo.accountInfo->onlineIpCount; i++) {
        //ip地址
        temp = all[27 + 20 * i].toPlainText();
        int dotAdress[3];
        for (int k = 0, j = 0; k < temp.length(); k++) {
            if (temp[k] == '.') {
                dotAdress[j] = k;
                j++;
            }
        }
        queryInfo.accountInfo->ipInfo[i].ipv4_Ip[0] = temp.left(dotAdress[0]).toInt();
        queryInfo.accountInfo->ipInfo[i].ipv4_Ip[1] = temp.mid(dotAdress[0] + 1, dotAdress[1] - dotAdress[0] - 1).toInt();
        queryInfo.accountInfo->ipInfo[i].ipv4_Ip[2] = temp.mid(dotAdress[1] + 1, dotAdress[2] - dotAdress[1] - 1).toInt();
        queryInfo.accountInfo->ipInfo[i].ipv4_Ip[3] = temp.mid(dotAdress[2] + 1).toInt();
        
        //入流量
        temp = all[28 + 20 * i].toPlainText();
        queryInfo.accountInfo->ipInfo[i].accurateTraffic = temp.left(temp.length() - 1).toDouble();
        if (temp[temp.length() - 1] == 'K') {
            queryInfo.accountInfo->ipInfo[i].accurateTraffic *= 1000;
        }
        if (temp[temp.length() - 1] == 'M') {
            queryInfo.accountInfo->ipInfo[i].accurateTraffic *= (1000 * 1000);
        }
        if (temp[temp.length() - 1] == 'G') {
            queryInfo.accountInfo->ipInfo[i].accurateTraffic *= (1000 * 1000 * 1000);
        }
        queryInfo.accountInfo->totalAccurateTraffic += queryInfo.accountInfo->ipInfo[i].accurateTraffic;

        //时间
        temp = all[38 + 20 * i].toPlainText();
        queryInfo.accountInfo->ipInfo[i].onlineTime[0] = temp.mid(temp.length() - 8, 2).toInt();
        queryInfo.accountInfo->ipInfo[i].onlineTime[1] = temp.mid(temp.length() - 5, 2).toInt();
        queryInfo.accountInfo->ipInfo[i].onlineTime[2] = temp.mid(temp.length() - 2, 2).toInt();
        //mac
        temp = all[41 + 20 * i].toPlainText();
        queryInfo.accountInfo->ipInfo[i].macAdress = temp;
    }
    frame->deleteLater();
}

void Network::loginSlot(QString username, QString password)
{
    //Generate MD5 hash of the password
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(password.toLatin1());
    QString hashedPassword = hash.result().toHex();
    //Get local MAC address. Cannot get correct MAC when there are some virtual machine.
    QList<QNetworkInterface> interfaceList = QNetworkInterface::allInterfaces();
    QString mac;

    foreach(QNetworkInterface networkInterface, interfaceList) {
        bool isRunning = networkInterface.flags().testFlag(QNetworkInterface::IsRunning);
        bool isLoopback = networkInterface.flags().testFlag(QNetworkInterface::IsLoopBack);
        bool isP2P = networkInterface.flags().testFlag(QNetworkInterface::IsPointToPoint);
        if (isRunning || !isLoopback || !isP2P) {
            mac = networkInterface.hardwareAddress();
            break;
        }
    }

    //Generate request packet and send it
    QString data = "username=" + username + "&password=" + hashedPassword + "&mac=" + mac + "&drop=0&type=1&n=100";
    QNetworkRequest request(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    loginReply = manager->post(request, data.toLatin1());
    connect(loginReply, SIGNAL(finished()), this, SLOT(loginFinished()));

}

void Network::logoutSlot()
{
    logoutReply = manager->get(QNetworkRequest(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_logout")));
    connect(logoutReply, SIGNAL(finished()), this, SLOT(logoutFinished()));
}

void Network::checkSlot()
{
    checkReply = manager->post(QNetworkRequest(QUrl("http://net.tsinghua.edu.cn/cgi-bin/do_login")),
                               "action=check_online");
    connect(checkReply, SIGNAL(finished()), this, SLOT(checkFinished()));
}

void Network::loginFinished()
{
    QNetworkReply *reply = loginReply;
    loginInfo.infoType = Info::LoginInfo;
    loginInfo.accountInfo = new AccountInfo;
    AccountInfo *info = loginInfo.accountInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        QList<QString> temp = dataReceived.split(',');
        quint64 uid = temp[0].toULongLong();
        if (uid == 0) {
            info->error = temp[0];
            emit loginFail(loginInfo);
        }
        else {
            info->roughTraffic = temp[2].toDouble();
            emit loginSucceed(loginInfo);
        }
    }
    else {
        info->error = reply->errorString();
        emit loginFail(loginInfo);
    }
    reply->deleteLater();
}

void Network::logoutFinished()
{
    QNetworkReply *reply = logoutReply;
    Info logoutInfo;
    logoutInfo.infoType = Info::LogoutInfo;
    logoutInfo.accountInfo = new AccountInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString result = reply->readAll();
        if (result == "logout_ok") {
            emit logoutSucceed();
            return;
        }
        logoutInfo.accountInfo->error = result;
        emit logoutFail(logoutInfo);
    }
    else {
        logoutInfo.accountInfo->error = reply->errorString();
        emit logoutFail(logoutInfo);
    }
    reply->deleteLater();
}

void Network::checkFinished()
{
    QNetworkReply *reply = checkReply;
    Info checkInfo;
    checkInfo.infoType = Info::CheckInfo;
    checkInfo.accountInfo = new AccountInfo;
    AccountInfo *info = checkInfo.accountInfo;
    if (reply->error() == QNetworkReply::NoError) {
        QString dataReceived = reply->readAll();
        if (dataReceived == "") {
            info->error = "not_logged_in";
            emit checkResult(checkInfo);
        }
        else {
            QList<QString> temp = dataReceived.split(',');
            info->balance = temp[2].toDouble();
            info->loginTime = temp[4].toLong();
            emit checkResult(checkInfo);
        }
    }
    else {
        info->error = reply->errorString();
        emit checkResult(checkInfo);
    }
    reply->deleteLater();
}
