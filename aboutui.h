#ifndef ABOUTUI_H
#define ABOUTUI_H

#include <QWidget>

namespace Ui {
class AboutUi;
}

class AboutUi : public QWidget
{
    Q_OBJECT

public:
    explicit AboutUi(QWidget *parent = 0);
    ~AboutUi();

private:
    Ui::AboutUi *ui;
};

#endif // ABOUTUI_H
