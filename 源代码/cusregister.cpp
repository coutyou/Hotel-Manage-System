#include "cusRegister.h"
#include "ui_cusregister.h"
#include "login.h"
#include "databasesl.h"
#include <QMessageBox>
#include <QIcon>

cusRegister::cusRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::cusRegister)
{
    ui->setupUi(this);
}

cusRegister::~cusRegister()
{
    delete ui;
}

void cusRegister::on_returnButton_clicked()//点击返回按钮
{
    //关闭注册界面打开登陆界面
    this->close();
    Login *lg = new Login();
    lg->exec();
}


void cusRegister::on_checkButton_clicked()
{
    if(ui->usernameInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("用户名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->passwordInput->text().isEmpty())
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
        //调用保存函数 关闭注册窗口 新建登陆窗口
        registerDatabaseSave(ui->usernameInput->text(),ui->passwordInput->text(),ui->phonenumInput->text(),
                             ui->nameInput->text(),ui->sexComboBox->currentIndex(),ui->idInput->text(),1);
        this->close();
        Login *lg = new Login();
        lg->exec();
    }
}
