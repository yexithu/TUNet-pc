#include <cstdio>
#include <algorithm>

#include "loginui.h"
#include "ui_loginui.h"

LoginUi::LoginUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginUi)
{
    ui->setupUi(this);
    LoginUi::loadInfo();
    connect(ui->autoLogin, SIGNAL(stateChanged(int)),
            this, SLOT(selectSavePassword(int)));
    connect(ui->savePassword, SIGNAL(stateChanged(int)),
            this, SLOT(disselectAutoLogin(int)));
    connect(ui->loginButton, SIGNAL(clicked()),
            this, SLOT(saveInfo()));
}

LoginUi::~LoginUi()
{
    delete ui;
}

void LoginUi::selectSavePassword(int state)
{
    if (state == Qt::Checked)
        ui->savePassword->setCheckState(Qt::Checked);
}

void LoginUi::disselectAutoLogin(int state)
{
    if (state == Qt::Unchecked)
        ui->autoLogin->setCheckState(Qt::Unchecked);
}

void LoginUi::loadInfo()
{
    FILE *input = fopen("TUNet-pc.log", "r");
    if (!input)
        return;

    char ch1, ch2, ch;
    fscanf(input, "%c", &ch1);
    if (ch1 == 'C')
        ui->savePassword->setCheckState(Qt::Checked);
    fscanf(input, "%c", &ch2);
    if (ch2 == 'C')
        ui->autoLogin->setCheckState(Qt::Checked);

    srand(42);
    fscanf(input, "%c", &ch);
    int usernameLength = ch ^ (rand() & 127);
    QString username = "";
    while (usernameLength--)
    {
        fscanf(input, "%c", &ch);
        username += (ch ^ (rand() & 127));
    }
    ui->username->setText(username);

    if (ch1 != 'C')
        return;
    fscanf(input, "%c", &ch);
    int passwordLength = ch ^ (rand() & 127);
    QString password = "";
    while (passwordLength--)
    {
        fscanf(input, "%c", &ch);
        password += (ch ^ (rand() & 127));
    }
    ui->password->setText(password);

    fclose(input);
}

void LoginUi::saveInfo()
{
    FILE *output = fopen("TUNet-pc.log", "w");

    if (ui->savePassword->checkState() == Qt::Checked)
        fprintf(output, "C");
    else
        fprintf(output, "U");
    if (ui->autoLogin->checkState() == Qt::Checked)
        fprintf(output, "C");
    else
        fprintf(output, "U");

    srand(42);
    int usernameLength = ui->username->text().length();
    fprintf(output, "%c", usernameLength ^ (rand() & 127));
    for (int i = 0; i < usernameLength; i++)
        fprintf(output, "%c", ui->username->text().at(i).toLatin1() ^ (rand() & 127));

    if (ui->savePassword->checkState() != Qt::Checked)
        return;
    int passwordLength = ui->password->text().length();
    fprintf(output, "%c", passwordLength ^ (rand() & 127));
    for (int i = 0; i < passwordLength; i++)
        fprintf(output, "%c", ui->password->text().at(i).toLatin1() ^ (rand() & 127));

    fclose(output);
}
