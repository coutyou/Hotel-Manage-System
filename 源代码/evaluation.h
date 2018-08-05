#ifndef EVALUATION_H
#define EVALUATION_H

/****************************README*************************************/
/*************************评价订单的窗口**********************************/
/*******由于评分是酒店的属性，平台会任意选择用户在酒店完成的订单来进行评价操作*****/
/****************************END****************************************/

#include <QDialog>
#include "hotel.h"
#include "order.h"
#include "room.h"
#include <QString>
#include <QLinkedList>

namespace Ui {
class Evaluation;
}

class Evaluation : public QDialog
{
    Q_OBJECT

public:
    explicit Evaluation(QString logingUsername,QLinkedList<Hotel> &hotelList,QLinkedList<Order> &orderList,QWidget *parent = 0);
    ~Evaluation();
    QString m_logingUsername;
    QLinkedList<Hotel> &m_hotelList;//酒店链表
    QLinkedList<Order> &m_orderList;//订单链表

private slots:
    void on_submitButton_clicked();

private:
    Ui::Evaluation *ui;
};

#endif // EVALUATION_H
