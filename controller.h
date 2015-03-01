#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"
#include "accountui.h"
#include "info.h"
#include "network.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller();
    ~Controller();

private:
    Network *network;
    LoginUi *loginUi;
    AccountUi *accountUi;
};

#endif // CONTROLLER_H
