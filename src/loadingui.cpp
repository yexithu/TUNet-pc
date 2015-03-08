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

}

LoadingUi::~LoadingUi()
{
    delete ui;
}
