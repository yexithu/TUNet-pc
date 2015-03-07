#include "aboutui.h"
#include "loginui.h"
#include "loadingui.h"
#include "accountui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("Lab µ");
    QCoreApplication::setOrganizationDomain("lab.mu");
    QCoreApplication::setApplicationName("tunet");
    QApplication::setStyle("windowxp");
    QApplication a(argc, argv);
    AccountUi about;
    about.show();
    LoginUi about1;
    about1.show();
    AboutUi about2;
    about2.show();
    LoadingUi about3;
    about3.show();

    return a.exec();
}
