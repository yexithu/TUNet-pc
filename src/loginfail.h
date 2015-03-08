#ifndef LOGINFAIL_H
#define LOGINFAIL_H

#include <QDialog>
#include <QFile>

namespace Ui {
class LoginFail;
}

class LoginFail : public QDialog
{
    Q_OBJECT

public:
    explicit LoginFail(QString, QWidget *parent = 0);
    ~LoginFail();

private:
    Ui::LoginFail *ui;
};

#endif // LOGINFAIL_H
