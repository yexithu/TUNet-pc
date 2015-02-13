#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"

class Controller
{
public:
    Controller();
    ~Controller();

private slots:
    void loginControl(QString username, QString password);
    void logoutControl();
    void loginRespond(QString respond);
    void queryRespond(QString respond);
    void logoutRespond(QString respond);
};

#endif // CONTROLLER_H
