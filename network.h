#ifndef NETWORK_H
#define NETWORK_H

#include "info.h"
#include <QObject>
#include <QtNetwork>

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
	RequestType requestType; 
public slots:
	void loginSlot(QString, QString);
    void logoutSlot();
	void querySlot();

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
