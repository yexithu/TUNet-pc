#ifndef LOGINUI_H
#define LOGINUI_H

#include "info.h"

#include <QWidget>
#include <QtNetwork>
#include <QSettings>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();

signals:
    void loginSignal(QString username, QString password);

private:
    Ui::LoginUi *ui;
    QString url;
    QString username;
    QString password;
    QSettings settings;

private slots:
    void selectSavePassword(int state);
    void disselectAutoLogin(int state);
    void loadInfo();
    void saveInfo();
    void loginClicked();

public slots:
    void loginFail(Info);
};

#endif // LOGINUI_H
