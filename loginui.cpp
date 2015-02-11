#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager;
    connect(manager, SIGNAL(finished(QNetworkReply*)),this, SLOT(replyFinished(QNetworkReply*)));
}

LoginUi::~LoginUi()
{
    delete ui;
}

void LoginUi::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString ureply = codec->toUnicode(reply->readAll());
    qDebug() << ureply;
}

void LoginUi::on_loginButton_clicked()
{
    username = ui->username->text();
    password = ui->password->text();
    url = "http://net.tsinghua.edu.cn/cgi-bin/do_login";
    loginPost(url,username,password);
}

void LoginUi::loginPost(QString url, QString uname, QString pass)
{
//    password = MD5(password);
    QString _content = "username=" + username + "&password" + password + "&drop=0&type=1&n=100";
    QByteArray content = _content.toLatin1();
    int contentLength = content.length();
    QNetworkRequest req;
    req.setUrl(QUrl(url));
    req.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    req.setHeader(QNetworkRequest::ContentLengthHeader, contentLength);
    manager->post(req,content);
}
