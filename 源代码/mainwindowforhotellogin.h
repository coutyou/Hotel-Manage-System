#ifndef MAINWINDOWFORHOTELLOGIN_H
#define MAINWINDOWFORHOTELLOGIN_H

/****************************README*************************************/
/**********************为酒店管理员登陆准备的主界面**************************/
/****************************END****************************************/

#include <QMainWindow>
#include "order.h"
#include "hotel.h"
#include "people.h"
#include "room.h"
#include <QCloseEvent>

namespace Ui {
class MainWindowForHotelLogin;
}

class MainWindowForHotelLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForHotelLogin(QLinkedList<Customer> customerList,QLinkedList<HotelManager> hotelManagerList,QLinkedList<Hotel> hotelNotCheckedList,QLinkedList<Hotel> hotelList,
                                     QLinkedList<Order> orderList,QWidget *parent = 0,QString logingUsername = "",QString logingHotelname = "");
    explicit MainWindowForHotelLogin(QWidget *parent = 0);
    ~MainWindowForHotelLogin();
    QString m_logingUsername;//正在登陆的用户名
    QString m_logingHotelname;//正在登陆的酒店名
    QLinkedList<Hotel> m_hotelList;//酒店链表
    QLinkedList<Hotel> m_hotelNotCheckedList;//未通过审核酒店链表
    QLinkedList<Order> m_orderList;//订单链表
    QLinkedList<Customer> m_customerList;//顾客链表
    QLinkedList<HotelManager> m_hotelManagerList;//酒店管理员链表
    void closeEvent(QCloseEvent *event);//关闭时确认

private slots:
    void on_action_P_triggered();

    void on_action_C_triggered();

    void on_action_F_triggered();

    void on_action_Q_triggered();

    void on_action_A_triggered();

    void on_action_D_triggered();

    void on_action_E_triggered();

    void on_action_U_triggered();

    void on_action_V_triggered();

private:
    Ui::MainWindowForHotelLogin *ui;
};

#endif // MAINWINDOWFORHOTELLOGIN_H
