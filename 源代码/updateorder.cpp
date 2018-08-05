#include "updateorder.h"
#include "ui_updateorder.h"
#include <QMessageBox>


UpdateOrder::UpdateOrder(QString logingUsername,QString logingHotelname,QLinkedList<Hotel> &hotelList,QLinkedList<Order> &orderList,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_logingHotelname(logingHotelname),m_hotelList(hotelList),m_orderList(orderList),
    ui(new Ui::UpdateOrder)
{
    ui->setupUi(this);
}

UpdateOrder::~UpdateOrder()
{
    delete ui;
}

void UpdateOrder::on_checkButton_clicked()
{
    int flag = 0;//判断顾客在该酒店是否有可更新的订单
    QLinkedList<Order>::iterator iter1;
    Order *o = NULL;
    for (iter1=m_orderList.begin();iter1!=m_orderList.end();iter1++)
    {
       if((*iter1).GetHotelname() == m_logingHotelname&&(*iter1).GetUsername() == ui->userNameInput->text()
               &&(!((*iter1).m_paymentStatus == -1)||((*iter1).m_checkInStatus == 2)))
       {
           o = &(*iter1);
           flag = 1;
           break;
       }
    }
    if(flag == 0)//若无可更新订单
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("该用户无可更新订单！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        switch (ui->updateTypeBox->currentIndex())
        {
        case 0://改为已付款
            if(o->m_paymentStatus == 0)
            {
                o->m_paymentStatus = 1;
                QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单状态更新成功！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                message.exec();
                this->close();
            }
            else
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("更新订单操作无效！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
            break;
        case 1://改为已取消
            if(o->m_checkInStatus == 0&&o->m_paymentStatus != -1)
            {
                o->m_paymentStatus = -1;//更改订单链表信息
                //更改酒店房间链表信息
                if(o->GetRoomType() == "SingleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname()== m_logingHotelname)
                       {
                           (*iter).m_SingleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "DoubleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_DoubleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "TripleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_TripleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "KingSizeRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_KingSizeRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "SuiteRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_SuiteRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单状态更新成功！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                message.exec();
                this->close();
            }
            else
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("更新订单操作无效！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
            break;
        case 2://改为正在入住
            if(o->m_checkInStatus == 0&&o->m_paymentStatus == 1)
            {
                o->m_checkInStatus = 1;
                QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单状态更新成功！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                message.exec();
                this->close();
            }
            else
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("更新订单操作无效！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
            break;
        case 3://改为已退房
            if(o->m_checkInStatus == 1)
            {
                o->m_checkInStatus = 2;
                //更改酒店房间链表信息
                if(o->GetRoomType() == "SingleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_SingleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "DoubleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_DoubleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "TripleRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_TripleRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "KingSizeRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_KingSizeRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                else if(o->GetRoomType() == "SuiteRoom")
                {
                    QLinkedList<Hotel>::iterator iter;
                    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
                    {
                       if((*iter).GetHotelname() == m_logingHotelname)
                       {
                           (*iter).m_SuiteRoom.m_roomRestNum++;
                           break;
                       }
                    }
                }
                QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单状态更新成功！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                message.exec();
                this->close();
            }
            else
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("更新订单操作无效！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
            break;
        default:
            break;
        }
    }
}
