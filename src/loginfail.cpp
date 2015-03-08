#include "loginfail.h"
#include "ui_loginfail.h"

#include <QDebug>

LoginFail::LoginFail(QString message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginFail)
{
    ui->setupUi(this);

    QFile *file = new QFile(":qss/qss/loginfail.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    ui->text->setText(message);
    connect(ui->okButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

LoginFail::~LoginFail()
{
    delete ui;
}
