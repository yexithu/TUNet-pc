#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "network.h"
#include <QTimer>
class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();

private:
	QTimer *timer;
    Network *network;
    LoginUi *loginUi;
    AccountUi *accountUi;
private slots:
	void setTimer();
};

#endif // CONTROLLER_H
