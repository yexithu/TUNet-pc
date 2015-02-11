#ifndef ACCOUNTUI_H
#define ACCOUNTUI_H

#include <QWidget>

namespace Ui {
class AccountUi;
}

class AccountUi : public QWidget
{
    Q_OBJECT

public:
    explicit AccountUi(QWidget *parent = 0);
    ~AccountUi();

private:
    Ui::AccountUi *ui;
};

#endif // ACCOUNTUI_H
