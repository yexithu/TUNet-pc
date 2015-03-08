#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include "aboutui.h"
#include "info.h"
#include "loginfail.h"
#include <QWidget>
#include <qtimer.h>

namespace Ui {
class AccountUi;
}

class AccountUi : public QWidget
{
    Q_OBJECT
public:
    explicit AccountUi(QWidget *parent = 0);
    ~AccountUi();

public:
    int onlineTime = 0;

private:
    Ui::AccountUi *ui;
    AboutUi *aboutUi;
    LoginFail *logoutFail;
    QTimer *timer;

signals:
    void logoutSignal();

private slots:
    void logoutClicked();
    void timeIncrement();

public slots:
    void infoSlot(Info);
    void checkResultSlot(Info);
    void logoutFailSlot(Info);
};

#endif // ACCOUNTUI_H
