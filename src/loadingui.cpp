#include "loadingui.h"
#include "ui_loadingui.h"

LoadingUi::LoadingUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadingUi)
{
    ui->setupUi(this);

    QFile *file = new QFile(":qss/qss/loadingui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());
    file->deleteLater();
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    connect(ui->cancelButton, SIGNAL(clicked()), this, SIGNAL(loginAbort()));
}

LoadingUi::~LoadingUi()
{
    delete ui;
}

void LoadingUi::setUsername(QString name)
{
    ui->username->setText(name);
}

void LoadingUi::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
