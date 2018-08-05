#ifndef UPDATEORDER_H
#define UPDATEORDER_H

/****************************README************************************/
/**************************订单更新界面**********************************/
/****************订单只能从上一种状态更新到接下来的一种状态*******************/
/****************************END***************************************/

#include <QDialog>
#include "order.h"
#include "hotel.h"
#include "room.h"
#include <QLinkedList>

namespace Ui {
class UpdateOrder;
}

class UpdateOrder : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateOrder(QString logingUsername,QString logingHotelname,QLinkedList<Hotel> &hotelList,QLinkedList<Order> &orderList,QWidget *parent = 0);
    ~UpdateOrder();
    QString m_logingUsername;//正在登陆的用户名
    QString m_logingHotelname;//正在登陆的酒店名
    QLinkedList<Hotel> &m_hotelList;//酒店链表
    QLinkedList<Order> &m_orderList;//订单链表

private slots:
    void on_checkButton_clicked();

private:
    Ui::UpdateOrder *ui;
};

#endif // UPDATEORDER_H
