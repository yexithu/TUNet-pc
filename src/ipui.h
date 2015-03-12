#ifndef IPUI_H
#define IPUI_H

#include "info.h"

#include <QWidget>
#include <QFile>
#include <qtimer.h>

namespace Ui {
class IpUi;
}

class IpUi : public QWidget
{
    Q_OBJECT

public:
    explicit IpUi(int, QWidget *parent = 0);
    ~IpUi();
    void showIp(IpInfo);
    void hideIp();

private:
    int order;
    Ui::IpUi *ui;

signals:
    void logoutRequest(int);

private slots:
    void logoutClicked();
};

#endif // IPUI_H
