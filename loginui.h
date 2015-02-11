#ifndef LOGINUI_H
#define LOGINUI_H

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class LoginUi;
}

class LoginUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoginUi(QWidget *parent = 0);
    ~LoginUi();
    void loginPost(QString url, QString uname, QString pass);

private slots:
    void on_loginButton_clicked();
    void replyFinished(QNetworkReply*);

private:
    Ui::LoginUi *ui;
    QNetworkAccessManager *manager;
    QString url;
    QString username;
    QString password;
};

#endif // LOGINUI_H
