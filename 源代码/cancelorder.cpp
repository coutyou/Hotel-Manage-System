#include "cancelorder.h"
#include "ui_cancelorder.h"
#include <QMessageBox>

CancelOrder::CancelOrder(QString logingUsername,QLinkedList<Order> &orderList,QLinkedList<Hotel> &hotelList,QLinkedList<Room> &roomList,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_orderList(orderList),m_hotelList(hotelList),m_roomList(roomList),
    ui(new Ui::CancelOrder)
{
    ui->setupUi(this);
}

CancelOrder::~CancelOrder()
{
    delete ui;
}

void CancelOrder::on_checkButton_clicked()
{
    QLinkedList<Order>::iterator iter1;
    int flag = 0;//判断顾客在该酒店是否有未入住且未取消订单
    QString roomType;
    for (iter1=m_orderList.begin();iter1!=m_orderList.end();iter1++)
    {
       if((*iter1).GetHotelname() == ui->hotelNameInput->text()&&(*iter1).GetUsername() == m_logingUsername
               &&((*iter1).m_paymentStatus == 0||(*iter1).m_paymentStatus == 1)&&(*iter1).m_checkInStatus == 0)
       {
           (*iter1).m_paymentStatus = -1;//更改订单链表信息
           roomType = (*iter1).GetRoomType();//得到客房种类
           flag = 1;
           break;
       }
    }
    if(flag == 0)//在该酒店不存在未入住且未取消订单
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("在该酒店不存在未完成订单！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else//更改酒店、客房链表信息
    {
        if(roomType == "SingleRoom")
        {
            QLinkedList<Hotel>::iterator iter;
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
            {
               if((*iter).GetHotelname() == ui->hotelNameInput->text())
               {
                   (*iter).m_SingleRoom.m_roomRestNum++;
                   break;
               }
            }
            QLinkedList<Room>::iterator oiter;
            for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量增加
            {
               if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "SingleRoom")
               {
                   (*oiter).m_roomRestNum++;
                   break;
               }
            }
        }
        else if(roomType == "DoubleRoom")
        {
            QLinkedList<Hotel>::iterator iter;
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
            {
               if((*iter).GetHotelname() == ui->hotelNameInput->text())
               {
                   (*iter).m_DoubleRoom.m_roomRestNum++;
                   break;
               }
            }
            QLinkedList<Room>::iterator oiter;
            for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量增加
            {
               if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "DoubleRoom")
               {
                   (*oiter).m_roomRestNum++;
                   break;
               }
            }
        }
        else if(roomType == "TripleRoom")
        {
            QLinkedList<Hotel>::iterator iter;
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
            {
               if((*iter).GetHotelname() == ui->hotelNameInput->text())
               {
                   (*iter).m_TripleRoom.m_roomRestNum++;
                   break;
               }
            }
            QLinkedList<Room>::iterator oiter;
            for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量增加
            {
               if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "TripleRoom")
               {
                   (*oiter).m_roomRestNum++;
                   break;
               }
            }
        }
        else if(roomType == "KingSizeRoom")
        {
            QLinkedList<Hotel>::iterator iter;
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
            {
               if((*iter).GetHotelname() == ui->hotelNameInput->text())
               {
                   (*iter).m_KingSizeRoom.m_roomRestNum++;
                   break;
               }
            }
            QLinkedList<Room>::iterator oiter;
            for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量增加
            {
               if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "KingSizeRoom")
               {
                   (*oiter).m_roomRestNum++;
                   break;
               }
            }
        }
        else if(roomType == "SuiteRoom")
        {
            QLinkedList<Hotel>::iterator iter;
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量增加
            {
               if((*iter).GetHotelname() == ui->hotelNameInput->text())
               {
                   (*iter).m_SuiteRoom.m_roomRestNum++;
                   break;
               }
            }
            QLinkedList<Room>::iterator oiter;
            for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量增加
            {
               if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "SuiteRoom")
               {
                   (*oiter).m_roomRestNum++;
                   break;
               }
            }
        }
        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单取消成功！\n若已付款我们将尽快退款！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
        message.exec();
        this->close();
    }
}
