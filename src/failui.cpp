#include "failui.h"
#include "ui_failui.h"

#include <QDebug>

FailUi::FailUi(QString message, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FailUi)
{
    ui->setupUi(this);

    QFile *file = new QFile(":qss/qss/failui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    ui->text->setText(message);
    connect(ui->okButton, SIGNAL(clicked()),
            this, SLOT(close()));
}

FailUi::~FailUi()
{
    delete ui;
}
