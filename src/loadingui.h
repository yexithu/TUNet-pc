#ifndef LOADINGUI_H
#define LOADINGUI_H

#include <QWidget>
#include <QFile>

namespace Ui {
class LoadingUi;
}

class LoadingUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingUi(QWidget *parent = 0);
    ~LoadingUi();

private:
    Ui::LoadingUi *ui;
};

#endif // LOADINGUI_H