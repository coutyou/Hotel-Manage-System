#ifndef ORDERPAY_H
#define ORDERPAY_H

/****************************README*************************************/
/*************************订单付款的窗口**********************************/
/****************************END****************************************/

#include <QDialog>
#include "order.h"
#include <QLinkedList>
#include <QMessageBox>

namespace Ui {
class OrderPay;
}

class OrderPay : public QDialog
{
    Q_OBJECT

public:
    explicit OrderPay(QString logingUsername,QLinkedList<Order> &orderList,QWidget *parent = 0);
    ~OrderPay();
    QString m_logingUsername;
    QLinkedList<Order> &m_orderList;//订单链表

private slots:
    void on_checkButton_clicked();

private:
    Ui::OrderPay *ui;
};

#endif // ORDERPAY_H
