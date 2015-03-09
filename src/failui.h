#ifndef FAILUI_H
#define FAILUI_H

#include <QDialog>
#include <QFile>

namespace Ui {
class FailUi;
}

class FailUi : public QDialog
{
    Q_OBJECT

public:
    explicit FailUi(QString, QWidget *parent = 0);
    ~FailUi();

private:
    Ui::FailUi *ui;
};

#endif // FAILUI_H
