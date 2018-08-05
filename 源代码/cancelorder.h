#ifndef CANCELORDER_H
#define CANCELORDER_H

/****************************README*************************************/
/*************************取消订单的窗口**********************************/
/****************************END****************************************/


#include <QDialog>
#include "order.h"
#include "hotel.h"
#include "room.h"
#include <QString>
#include <QLinkedList>

namespace Ui {
class CancelOrder;
}

class CancelOrder : public QDialog
{
    Q_OBJECT

public:
    explicit CancelOrder(QString logingUsername,QLinkedList<Order> &orderList,QLinkedList<Hotel> &hotelList,QLinkedList<Room> &roomList,QWidget *parent = 0);
    ~CancelOrder();
    QString m_logingUsername;
    QLinkedList<Order> &m_orderList;//订单链表
    QLinkedList<Hotel> &m_hotelList;//酒店链表
    QLinkedList<Room> &m_roomList;//客房链表

private slots:
    void on_checkButton_clicked();

private:
    Ui::CancelOrder *ui;
};

#endif // CANCELORDER_H
