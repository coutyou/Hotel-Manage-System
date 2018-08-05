#include "peopleinfochange.h"
#include "ui_peopleinfochange.h"
#include "people.h"
#include "databasesl.h"

PeopleInfoChange::PeopleInfoChange(QLinkedList<Customer> &customerList,QLinkedList<HotelManager> &hotelManagerList,bool isCus,QString logingUsername,QWidget *parent) :
    QDialog(parent),m_logingUsername(logingUsername),m_isCus(isCus),m_customerList(customerList),m_hotelManagerList(hotelManagerList),
    ui(new Ui::PeopleInfoChange)
{
    ui->setupUi(this);
}

PeopleInfoChange::~PeopleInfoChange()
{
    delete ui;
}

void PeopleInfoChange::on_checkButton_clicked()//点击确认更改按钮
{
    if(m_isCus)//若是顾客
    {
        QLinkedList<Customer>::iterator iter;//创建迭代器找到对应的节点
        Customer curCus;
        for (iter=m_customerList.begin();iter!=m_customerList.end();iter++)
        {
           if((*iter).GetUsername() == m_logingUsername)
           {
               curCus = (*iter);
               break;
           }
        }
         if(ui->passwordInput->text().isEmpty())
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("密码不能为空！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(ui->phonenumInput->text().isEmpty())
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号不能为空！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(ui->nameInput->text().isEmpty())
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名不能为空！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(ui->idInput->text().isEmpty())
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号不能为空！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(ui->phonenumInput->text().size() != 11)
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号长度错误！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(ui->idInput->text().size() != 18)
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号长度错误！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(!IsNumber(ui->phonenumInput->text()))
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效手机号输入！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(!IsChinese(ui->nameInput->text()))
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名输入非纯中文！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else if(!IsId(ui->idInput->text()))
        {
             QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效身份证号输入！"),QMessageBox::Ok,this);
             message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
             message.exec();
        }
        else
        {
            Customer c(m_logingUsername,ui->passwordInput->text(),ui->phonenumInput->text(),ui->nameInput->text(),ui->idInput->text(),ui->sexComboBox->currentIndex());
            curCus.ChangeInfo(c,m_customerList);
            QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("信息修改成功！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
            message.exec();
            this->close();
        }
    }
    else//若是酒店管理员
    {
        QLinkedList<HotelManager>::iterator iter;//创建迭代器找到对应的节点
        HotelManager curHM;
        for (iter=m_hotelManagerList.begin();iter!=m_hotelManagerList.end();iter++)
        {
           if((*iter).GetUsername() == m_logingUsername)
           {
               curHM = (*iter);
               break;
           }
        }
        if(ui->passwordInput->text().isEmpty())
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("密码不能为空！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(ui->phonenumInput->text().isEmpty())
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号不能为空！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(ui->nameInput->text().isEmpty())
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名不能为空！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(ui->idInput->text().isEmpty())
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号不能为空！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(ui->phonenumInput->text().size() != 11)
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号长度错误！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(ui->idInput->text().size() != 18)
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号长度错误！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(!IsNumber(ui->phonenumInput->text()))
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效手机号输入！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(!IsChinese(ui->nameInput->text()))
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名输入非纯中文！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else if(!IsId(ui->idInput->text()))
       {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效身份证号输入！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
       }
       else
       {
            HotelManager h(getHotelName(m_logingUsername),m_logingUsername,ui->passwordInput->text(),ui->phonenumInput->text(),ui->nameInput->text(),ui->idInput->text(),ui->sexComboBox->currentIndex());
            curHM.ChangeInfo(h,m_hotelManagerList);
            QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("信息修改成功！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
            message.exec();
            this->close();
       }
    }
}
