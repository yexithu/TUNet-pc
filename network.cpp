#include "network.h"

Network::Network()
{
    loginManager = new QNetworkAccessManager;
    logoutManager = new QNetworkAccessManager;
    queryManager = new QNetworkAccessManager;
}

Network::~Network()
{
}

void Network::login(QString username, QString password)
{
}

void Network::logout()
{
}

void Network::query(QString username, QString password)
{
}


void Network::loginReplyFinished(QNetworkReply *reply)
{
}

void Network::logoutReplyFinished(QNetworkReply *reply)
{
}

void Network::queryFinished(QNetworkReply *reply)
{
}
