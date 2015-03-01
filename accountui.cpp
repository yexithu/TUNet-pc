#include <QFile>

#include "accountui.h"
#include "ui_accountui.h"

AccountUi::AccountUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountUi)
{
    ui->setupUi(this);

    aboutUi = new AboutUi;

    QFile *file = new QFile(":qss/qss/accountui.qss");
    file->open(QFile::ReadOnly);
    setStyleSheet(file->readAll());

    connect(ui->aboutButton, SIGNAL(clicked()),
            aboutUi, SLOT(exec()));
}

AccountUi::~AccountUi()
{
    delete ui;
}

void AccountUi::logoutClicked()
{
    emit logoutSignal();
}

void AccountUi::infoSlot(Info info)
{
}

void AccountUi::logoutFail(Info info)
{
}
