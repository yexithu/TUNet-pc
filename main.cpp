#include "loginui.h"
#include "accountui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginUi w;
    w.show();

    return a.exec();
}
