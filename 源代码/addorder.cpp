#include "addorder.h"
#include "ui_addorder.h"
#include <QLinkedList>
#include <QMessageBox>
#include <QDateEdit>


AddOrder::AddOrder(QString logingUsername,QLinkedList<Hotel> &hotelList,QLinkedList<Room> &roomList,QLinkedList<Order> &orderList,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_hotelList(hotelList),m_roomList(roomList),m_orderList(orderList),
    ui(new Ui::AddOrder)
{
    ui->setupUi(this);
    ui->beginDate->setDate(QDate::currentDate());
    ui->endDate->setDate(QDate::currentDate());
}

AddOrder::~AddOrder()
{
    delete ui;
}

void AddOrder::on_checkButton_clicked()
{
    int day1 =  ui->beginDate->date().daysTo(ui->endDate->date());
    int day2 = QDate::currentDate().daysTo(ui->beginDate->date());
    if(day1 <= 0||day2 < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("日期无效！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        QLinkedList<Hotel>::iterator iter;
        Hotel curHotel;
        int flag = 0;//判断酒店是否存在
        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
        {
           if((*iter).GetHotelname() == ui->hotelNameInput->text())
           {
               curHotel = (*iter);//获得酒店信息
               flag = 1;//酒店存在
               break;
           }
        }
        if(flag == 0)//酒店不存在
        {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("该酒店名不存在！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
        }
        else
        {
            flag = 0;
            //判断是否有未完成订单
            QLinkedList<Order>::iterator iter1;
            for (iter1=m_orderList.begin();iter1!=m_orderList.end();iter1++)
            {
               if((*iter1).GetHotelname() == ui->hotelNameInput->text()&&(*iter1).GetUsername() == m_logingUsername
                       &&(!((*iter1).m_paymentStatus == -1||(*iter1).m_checkInStatus == 2)))
               {
                   flag = 1;
                   break;
               }
            }
            //若存在未完成订单 弹出警告
            if(flag == 1)
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("在该酒店最多存在一个未完成订单！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
            else
            {
                //若不存在未完成订单
                switch (ui->roomTypeBox->currentIndex())
                {
                case 0:
                    if(curHotel.m_SingleRoom.m_roomRestNum == 0)//若酒店客房不足 弹出警告
                    {
                        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("客房不足！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                        message.exec();
                    }
                    else//否则添加订单 减少客房余量
                    {
                        m_orderList<<Order(ui->beginDate->date(),ui->endDate->date(),ui->amountLabel->text().toFloat(),m_logingUsername,ui->hotelNameInput->text(),"SingleRoom",0,0,0);//添加订单
                        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量减少
                        {
                           if((*iter).GetHotelname() == ui->hotelNameInput->text())
                           {
                               (*iter).m_SingleRoom.m_roomRestNum--;
                               break;
                           }
                        }
                        QLinkedList<Room>::iterator oiter;
                        for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量减少
                        {
                           if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "SingleRoom")
                           {
                               (*oiter).m_roomRestNum--;
                               break;
                           }
                        }
                        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单添加成功！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                        message.exec();
                        this->close();
                    }
                    break;
                case 1:
                    if(curHotel.m_DoubleRoom.m_roomRestNum == 0)//若酒店客房不足 弹出警告
                    {
                        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("客房不足！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                        message.exec();
                    }
                    else//否则添加订单 减少客房余量
                    {
                        m_orderList<<Order(ui->beginDate->date(),ui->endDate->date(),ui->amountLabel->text().toFloat(),m_logingUsername,ui->hotelNameInput->text(),"DoubleRoom",0,0,0);//添加订单
                        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量减少
                        {
                           if((*iter).GetHotelname() == ui->hotelNameInput->text())
                           {
                               (*iter).m_DoubleRoom.m_roomRestNum--;
                               break;
                           }
                        }
                        QLinkedList<Room>::iterator oiter;
                        for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量减少
                        {
                           if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "DoubleRoom")
                           {
                               (*oiter).m_roomRestNum--;
                               break;
                           }
                        }
                        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单添加成功！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                        message.exec();
                        this->close();
                    }
                    break;
                case 2:
                    if(curHotel.m_TripleRoom.m_roomRestNum == 0)//若酒店客房不足 弹出警告
                    {
                        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("客房不足！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                        message.exec();
                    }
                    else//否则添加订单 减少客房余量
                    {
                        m_orderList<<Order(ui->beginDate->date(),ui->endDate->date(),ui->amountLabel->text().toFloat(),m_logingUsername,ui->hotelNameInput->text(),"TripleRoom",0,0,0);//添加订单
                        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量减少
                        {
                           if((*iter).GetHotelname() == ui->hotelNameInput->text())
                           {
                               (*iter).m_TripleRoom.m_roomRestNum--;
                               break;
                           }
                        }
                        QLinkedList<Room>::iterator oiter;
                        for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量减少
                        {
                           if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "TripleRoom")
                           {
                               (*oiter).m_roomRestNum--;
                               break;
                           }
                        }
                        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单添加成功！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                        message.exec();
                        this->close();
                    }
                    break;
                case 3:
                    if(curHotel.m_KingSizeRoom.m_roomRestNum == 0)//若酒店客房不足 弹出警告
                    {
                        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("客房不足！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                        message.exec();
                    }
                    else//否则添加订单 减少客房余量
                    {
                        m_orderList<<Order(ui->beginDate->date(),ui->endDate->date(),ui->amountLabel->text().toFloat(),m_logingUsername,ui->hotelNameInput->text(),"KingSizeRoom",0,0,0);//添加订单
                        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量减少
                        {
                           if((*iter).GetHotelname() == ui->hotelNameInput->text())
                           {
                               (*iter).m_KingSizeRoom.m_roomRestNum--;
                               break;
                           }
                        }
                        QLinkedList<Room>::iterator oiter;
                        for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量减少
                        {
                           if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "KingSizeRoom")
                           {
                               (*oiter).m_roomRestNum--;
                               break;
                           }
                        }
                        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单添加成功！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                        message.exec();
                        this->close();
                    }
                    break;
                case 4:
                    if(curHotel.m_SuiteRoom.m_roomRestNum == 0)//若酒店客房不足 弹出警告
                    {
                        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("客房不足！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                        message.exec();
                    }
                    else//否则添加订单 减少客房余量
                    {
                        m_orderList<<Order(ui->beginDate->date(),ui->endDate->date(),ui->amountLabel->text().toFloat(),m_logingUsername,ui->hotelNameInput->text(),"SuiteRoom",0,0,0);//添加订单
                        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)//酒店链表客房余量减少
                        {
                           if((*iter).GetHotelname() == ui->hotelNameInput->text())
                           {
                               (*iter).m_SuiteRoom.m_roomRestNum--;
                               break;
                           }
                        }
                        QLinkedList<Room>::iterator oiter;
                        for (oiter=m_roomList.begin();oiter!=m_roomList.end();oiter++)//客房链表客房余量减少
                        {
                           if((*oiter).GetHotelname() == ui->hotelNameInput->text()&&(*oiter).GetRoomType() == "SuiteRoom")
                           {
                               (*oiter).m_roomRestNum--;
                               break;
                           }
                        }
                        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单添加成功！"),QMessageBox::Ok,this);
                        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
                        message.exec();
                        this->close();
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void AddOrder::on_endDate_userDateChanged(const QDate &date)
{
    QLinkedList<Hotel>::iterator iter;
    Hotel curHotel;
    int flag = 0;//判断酒店是否存在
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == ui->hotelNameInput->text())
       {
           curHotel = (*iter);//获得酒店信息
           flag = 1;//酒店存在
           break;
       }
    }
    if(flag == 0)//酒店不存在
    {
           ui->amountLabel->setText(QString::number(0));
    }
    else
    {
        float roomPrice;
        switch (ui->roomTypeBox->currentIndex())
        {
        case 0:
            roomPrice = curHotel.m_SingleRoom.m_fixedPrice*(1-curHotel.m_SingleRoom.m_discount);
            break;
        case 1:
            roomPrice = curHotel.m_DoubleRoom.m_fixedPrice*(1-curHotel.m_DoubleRoom.m_discount);
            break;
        case 2:
            roomPrice = curHotel.m_TripleRoom.m_fixedPrice*(1-curHotel.m_TripleRoom.m_discount);
            break;
        case 3:
            roomPrice = curHotel.m_KingSizeRoom.m_fixedPrice*(1-curHotel.m_KingSizeRoom.m_discount);
            break;
        case 4:
            roomPrice = curHotel.m_SuiteRoom.m_fixedPrice*(1-curHotel.m_SuiteRoom.m_discount);
            break;
        default:
            break;
        }
        int day =  ui->beginDate->date().daysTo(date);
        if(day < 0)
        {
            ui->amountLabel->setText(QString::number(0));
        }
        else
        {
            ui->amountLabel->setText(QString::number(day*roomPrice));
        }
    }
}

void AddOrder::on_beginDate_userDateChanged(const QDate &date)
{
    QLinkedList<Hotel>::iterator iter;
    Hotel curHotel;
    int flag = 0;//判断酒店是否存在
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == ui->hotelNameInput->text())
       {
           curHotel = (*iter);//获得酒店信息
           flag = 1;//酒店存在
           break;
       }
    }
    if(flag == 0)//酒店不存在
    {
           ui->amountLabel->setText(QString::number(0));
    }
    else
    {
        float roomPrice;
        switch (ui->roomTypeBox->currentIndex())
        {
        case 0:
            roomPrice = curHotel.m_SingleRoom.m_fixedPrice*(1-curHotel.m_SingleRoom.m_discount);
            break;
        case 1:
            roomPrice = curHotel.m_DoubleRoom.m_fixedPrice*(1-curHotel.m_DoubleRoom.m_discount);
            break;
        case 2:
            roomPrice = curHotel.m_TripleRoom.m_fixedPrice*(1-curHotel.m_TripleRoom.m_discount);
            break;
        case 3:
            roomPrice = curHotel.m_KingSizeRoom.m_fixedPrice*(1-curHotel.m_KingSizeRoom.m_discount);
            break;
        case 4:
            roomPrice = curHotel.m_SuiteRoom.m_fixedPrice*(1-curHotel.m_SuiteRoom.m_discount);
            break;
        default:
            break;
        }
        int day =  date.daysTo(ui->endDate->date());
        if(day < 0)
        {
            ui->amountLabel->setText(QString::number(0));
        }
        else
        {
            ui->amountLabel->setText(QString::number(day*roomPrice));
        }
    }
}

void AddOrder::on_hotelNameInput_textChanged(const QString &arg1)
{
    QLinkedList<Hotel>::iterator iter;
    Hotel curHotel;
    int flag = 0;//判断酒店是否存在
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == arg1)
       {
           curHotel = (*iter);//获得酒店信息
           flag = 1;//酒店存在
           break;
       }
    }
    if(flag == 0)//酒店不存在
    {
           ui->amountLabel->setText(QString::number(0));
    }
    else
    {
        float roomPrice;
        switch (ui->roomTypeBox->currentIndex())
        {
        case 0:
            roomPrice = curHotel.m_SingleRoom.m_fixedPrice*(1-curHotel.m_SingleRoom.m_discount);
            break;
        case 1:
            roomPrice = curHotel.m_DoubleRoom.m_fixedPrice*(1-curHotel.m_DoubleRoom.m_discount);
            break;
        case 2:
            roomPrice = curHotel.m_TripleRoom.m_fixedPrice*(1-curHotel.m_TripleRoom.m_discount);
            break;
        case 3:
            roomPrice = curHotel.m_KingSizeRoom.m_fixedPrice*(1-curHotel.m_KingSizeRoom.m_discount);
            break;
        case 4:
            roomPrice = curHotel.m_SuiteRoom.m_fixedPrice*(1-curHotel.m_SuiteRoom.m_discount);
            break;
        default:
            break;
        }
        int day =  ui->beginDate->date().daysTo(ui->endDate->date());
        if(day < 0)
        {
            ui->amountLabel->setText(QString::number(0));
        }
        else
        {
            ui->amountLabel->setText(QString::number(day*roomPrice));
        }
    }
}
