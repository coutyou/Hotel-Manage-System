#ifndef MAINWINDOWFORPLATFORMMANAGER_H
#define MAINWINDOWFORPLATFORMMANAGER_H

/****************************README*************************************/
/*********************为平台管理员登陆准备的主界面**************************/
/****************************END***************************************/

#include <QMainWindow>
#include "hotel.h"
#include <QLinkedList>
#include <QCloseEvent>

namespace Ui {
class MainWindowForPlatformManager;
}

class MainWindowForPlatformManager : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindowForPlatformManager(QLinkedList<Hotel> hotelNotCheckedList,QLinkedList<Hotel> hotelList,QWidget *parent = 0);
    ~MainWindowForPlatformManager();
    QLinkedList<Hotel> m_hotelList;//酒店链表
    QLinkedList<Hotel> m_hotelNotCheckedList;//未通过审核酒店链表
    void closeEvent(QCloseEvent *event);//关闭时确认

private slots:
    void on_action_A_triggered();

    void on_action_S_triggered();

    void on_action_Q_triggered();

    void on_action_F_triggered();


    void on_action_V_triggered();

private:
    Ui::MainWindowForPlatformManager *ui;
};

#endif // MAINWINDOWFORPLATFORMMANAGER_H
