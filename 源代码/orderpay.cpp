#include "orderpay.h"
#include "ui_orderpay.h"
#include "order.h"

OrderPay::OrderPay(QString logingUsername,QLinkedList<Order> &orderList,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_orderList(orderList),
    ui(new Ui::OrderPay)
{
    ui->setupUi(this);
}

OrderPay::~OrderPay()
{
    delete ui;
}

void OrderPay::on_checkButton_clicked()
{
    int flag = 0;//用于判断是否有未支付订单
    QLinkedList<Order>::iterator iter1;
    for (iter1=m_orderList.begin();iter1!=m_orderList.end();iter1++)
    {
       if((*iter1).GetHotelname() == ui->hotelNameInput->text()&&(*iter1).GetUsername() == m_logingUsername&&(*iter1).m_paymentStatus == 0)
       {
           (*iter1).m_paymentStatus = 1;//修改支付状态为已支付
           flag = 1;
           break;
       }
    }
    if(flag == 0)//若无未支付订单，弹出警告
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("在该酒店无未支付订单！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else//否则弹出支付成功提醒
    {
        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("订单付款成功！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
        message.exec();
        this->close();
    }
}
