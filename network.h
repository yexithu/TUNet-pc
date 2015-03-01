#ifndef NETWORK_H
#define NETWORK_H

#include "info.h"
#include <QObject>
#include <QNetworkAccessManager>

class Network : public QObject
{
    Q_OBJECT

public:
    Network();
    ~Network();

private:
    QNetworkAccessManager *manager;

public slots:
    void loginSlot(QString, QString);
    void logoutSlot();

signals:
    void infoSignal(Info);
    void logoutSucceed();
    void loginFail(Info);
    void logoutFail(Info);

};

#endif // NETWORK_H
