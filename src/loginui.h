#ifndef LOGINUI_H
#define LOGINUI_H

#include "info.h"
#include "ipui.h"
#include "failui.h"

#include <QWidget>
#include <QtNetwork>
#include <QSettings>
#include <QCloseEvent>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();
    QString username;
    QString password;

signals:
    void loginSignal(QString username, QString password);

private:
    IpUi *ip[3];
    Ui::LoginUi *ui;
    QString url;
    QSettings settings;
    FailUi *loginFail;

private slots:
    void selectSavePassword(int state);
    void disselectAutoLogin(int state);
    void loadInfo();
    void saveInfo();
    void loginClicked();
    void adjustWindow(bool state);

public slots:
    void loginFailDialog(Info);

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOGINUI_H
