#ifndef ADDORDER_H
#define ADDORDER_H

/****************************README*************************************/
/*************************添加订单的窗口**********************************/
/***************同一个顾客在一家酒店最多存在一个未完成的订单*******************/
/****************************END****************************************/

#include <QDialog>
#include "hotel.h"
#include "order.h"
#include "room.h"
#include <QString>
#include <QLinkedList>

namespace Ui {
class AddOrder;
}

class AddOrder : public QDialog
{
    Q_OBJECT

public:
    explicit AddOrder(QString logingUsername,QLinkedList<Hotel> &hotelList,QLinkedList<Room> &roomList,QLinkedList<Order> &orderList,QWidget *parent = 0);
    ~AddOrder();
    QString m_logingUsername;
    QLinkedList<Hotel> &m_hotelList;//酒店链表
    QLinkedList<Room> &m_roomList;//客房链表
    QLinkedList<Order> &m_orderList;//订单链表


private slots:
    void on_checkButton_clicked();

    void on_endDate_userDateChanged(const QDate &date);

    void on_beginDate_userDateChanged(const QDate &date);

    void on_hotelNameInput_textChanged(const QString &arg1);

private:
    Ui::AddOrder *ui;
};

#endif // ADDORDER_H
