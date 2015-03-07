#include "aboutui.h"
#include "loginui.h"
#include "loadingui.h"
#include "accountui.h"
#include "controller.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lab µ");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication a(argc, argv);
    Controller controller;
    return a.exec();
}
