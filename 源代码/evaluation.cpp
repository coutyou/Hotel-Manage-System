#include "evaluation.h"
#include "ui_evaluation.h"
#include <QMessageBox>

Evaluation::Evaluation(QString logingUsername,QLinkedList<Hotel> &hotelList,QLinkedList<Order> &orderList,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_hotelList(hotelList),m_orderList(orderList),
    ui(new Ui::Evaluation)
{
    ui->setupUi(this);
}

Evaluation::~Evaluation()
{
    delete ui;
}

void Evaluation::on_submitButton_clicked()
{
    QLinkedList<Order>::iterator iter1;
    int flag = 0;//判断顾客在该酒店是否有已完成未评价订单
    for (iter1=m_orderList.begin();iter1!=m_orderList.end();iter1++)
    {
       if((*iter1).GetHotelname() == ui->hotelNameInput->text()&&(*iter1).GetUsername() == m_logingUsername
               &&(*iter1).m_checkInStatus == 2&&(*iter1).m_evaluateStatus == 0)
       {
           (*iter1).m_evaluateStatus = 1;//更改订单链表信息
           flag = 1;
           break;
       }
    }
    if(flag == 0)//若无可评价订单
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("在该酒店无可评价订单！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else//若有可评价订单
    {
        //查找对应的酒店 更改评分与次数
        QLinkedList<Hotel>::iterator iter;
        for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
        {
           if((*iter).GetHotelname() == ui->hotelNameInput->text())
           {
               (*iter).m_evaluation = ((*iter).m_evaluation*(*iter).m_evaluationTimes+ui->evaluationInputBox->value())/((*iter).m_evaluationTimes+1);
               (*iter).m_evaluationTimes++;
               break;
           }
        }
        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("评价成功！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
        message.exec();
        this->close();
    }
}
