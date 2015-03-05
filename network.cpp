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

void Network::querySlot(QString, QString)
{

}

void Network::replyFinished(QNetworkReply*)
{

}