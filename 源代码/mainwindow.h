#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/****************************README*************************************/
/*****************为顾客登陆准备的主界面 ，设置为默认的主界面******************/
/****************************END****************************************/

#include "login.h"
#include <QMainWindow>
#include <QLinkedList>
#include "order.h"
#include "hotel.h"
#include "people.h"
#include "room.h"
#include <QDesktopWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QLinkedList<Customer> customerList,QLinkedList<HotelManager> hotelManagerList,QLinkedList<Hotel> hotelNotCheckedList,QLinkedList<Hotel> hotelList,
                        QLinkedList<Room> roomList,QLinkedList<Order> orderList,QWidget *parent = 0,QString logingUsername = "");
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString m_logingUsername;//正在登陆的用户名
    QLinkedList<Hotel> m_hotelList;//酒店链表
    QLinkedList<Hotel> m_hotelNotCheckedList;//未通过审核酒店链表
    QLinkedList<Room> m_roomList;//客房链表
    QLinkedList<Order> m_orderList;//订单链表
    QLinkedList<Customer> m_customerList;
    QLinkedList<HotelManager> m_hotelManagerList;
    void closeEvent(QCloseEvent *event);//关闭时确认

private slots:
    void on_action_Q_triggered();

    void on_action_O_triggered();

    void on_action_C_triggered();

    void on_action_P_triggered();

    void on_action_K_triggered();

    void on_action_A_triggered();

    void on_action_J_triggered();

    void on_action_N_triggered();

    void on_action_H_triggered();

    void on_action_B_triggered();

    void on_action_D_triggered();

    void on_action_E_triggered();

    void on_action_V_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
