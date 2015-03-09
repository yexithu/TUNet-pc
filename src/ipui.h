#ifndef IPUI_H
#define IPUI_H

#include <QWidget>

namespace Ui {
class IpUi;
}

class IpUi : public QWidget
{
    Q_OBJECT

public:
    explicit IpUi(int, QWidget *parent = 0);
    ~IpUi();

private:
    int order;
    Ui::IpUi *ui;

signals:
    void logoutRequest(int);

private slots:
    void logoutClicked();
};

#endif // IPUI_H
