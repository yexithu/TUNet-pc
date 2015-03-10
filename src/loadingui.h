#ifndef LOADINGUI_H
#define LOADINGUI_H

#include <QWidget>
#include <QFile>
#include <QCloseEvent>

namespace Ui {
class LoadingUi;
}

class LoadingUi : public QWidget
{
    Q_OBJECT

public:
    explicit LoadingUi(QWidget *parent = 0);
    ~LoadingUi();
    void setUsername(QString);

signals:
    void loginAbort();

private:
    Ui::LoadingUi *ui;

protected:
    void closeEvent(QCloseEvent *event);
};

#endif // LOADINGUI_H
