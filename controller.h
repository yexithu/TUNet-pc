#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "loginui.h"

class Controller
{
public:
    Controller();
    ~Controller();

private slots:
    loginControl(QString username, QString password);
};

#endif // CONTROLLER_H
