#include "network.h"

Network::Network()
{
    manager = new QNetworkAccessManager;
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
