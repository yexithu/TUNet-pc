#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include "aboutui.h"
#include "info.h"
#include <QWidget>

namespace Ui {
class AccountUi;
}

class AccountUi : public QWidget
{
    Q_OBJECT

public:
    explicit AccountUi(QWidget *parent = 0);
    ~AccountUi();

private:
    Ui::AccountUi *ui;
    AboutUi *aboutUi;

signals:
    void logoutSignal();

private slots:
    void logoutClicked();

public slots:
    void infoSlot(Info);
    void logoutFail(Info);
};

#endif // ACCOUNTUI_H
