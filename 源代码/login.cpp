#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "cusRegister.h"
#include "hotelRegister.h"
#include "databasesl.h"
#include "mainwindow.h"
#include "mainwindowforhotellogin.h"
#include "mainwindowforplatformmanager.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QAction *pLeadingAction = new QAction(this);
    pLeadingAction->setIcon(QIcon(":/myimages/icon/账号.png"));
    ui->userNameInput->addAction(pLeadingAction, QLineEdit::LeadingPosition);
    QAction *pLeadingAction2 = new QAction(this);
    pLeadingAction2->setIcon(QIcon(":/myimages/icon/密码.png"));
    ui->passwordInput->addAction(pLeadingAction2, QLineEdit::LeadingPosition);
    this->setWindowFlags(Qt::FramelessWindowHint);
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginButton_clicked()//点击登陆按钮
{
    if(!(ui->hotelButton->isChecked()||ui->customerButton->isChecked()||ui->SystemButton->isChecked()))//未选择登陆方式 弹出警告
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("未选择登陆方式！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        if(ui->SystemButton->isChecked())
        {
            if(ui->userNameInput->text() == "cinyou"&&ui->passwordInput->text() == "123")
            {
                QLinkedList<Hotel> hllfpm = hotelLinkedListForPlatformManagerCreate();
                QLinkedList<Hotel> hL = hotelLinkedListCreate();
                MainWindowForPlatformManager *mfpm = new MainWindowForPlatformManager(hllfpm,hL);
                mfpm->show();
                this->close();
            }
            else
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("用户名或密码错误！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
        }
        else
        {
            //判断账号密码是否对应
            bool check = registerDatabaseCheck(ui->userNameInput->text(),ui->passwordInput->text(),ui->customerButton->isChecked());
            if(ui->customerButton->isChecked()&&check) //选择顾客登陆且账号密码正确
           {
               //打开顾客主菜单 关闭登陆窗口
               QLinkedList<Hotel> hL = hotelLinkedListCreate();
               QLinkedList<Room> rL = roomLinkedListCreate();
               QLinkedList<Order> oL = orderLinkedListCreate();
               QLinkedList<Hotel> hLf = hotelLinkedListForPlatformManagerCreate();
               QLinkedList<Customer> cl = customerLinkedListCreate();
               QLinkedList<HotelManager> hml= hotelManagerLinkedListCreate();
               MainWindow *w = new MainWindow(cl,hml,hLf,hL,rL,oL,NULL,ui->userNameInput->text());
               w->show();
               this->close();
           }
           else if(ui->hotelButton->isChecked()&&check)  //选择酒店登陆且账号密码正确
           {
               //打开酒店主菜单 关闭登陆窗口
               QLinkedList<Hotel> hL = hotelLinkedListCreate();
               QLinkedList<Order> oL = orderLinkedListCreate();
               QLinkedList<Hotel> hLf = hotelLinkedListForPlatformManagerCreate();
               QLinkedList<Customer> cl = customerLinkedListCreate();
               QLinkedList<HotelManager> hml= hotelManagerLinkedListCreate();
               MainWindowForHotelLogin *mh = new MainWindowForHotelLogin(cl,hml,hLf,hL,oL,NULL,ui->userNameInput->text(),getHotelName(ui->userNameInput->text()));
               mh->show();
               this->close();
           }
           else//清除账号密码
           {
               ui->userNameInput->clear();
               ui->passwordInput->clear();
           }
        }
    }
}

void Login::on_registerButton_clicked()//点击注册按钮
{
    if(ui->customerButton->isChecked())//顾客注册
    {
        cusRegister *cR = new cusRegister(this);
        this->close();
        cR->show();
    }
    else if(ui->hotelButton->isChecked())//酒店注册
    {
        hotelRegister *hR = new hotelRegister(this);
        this->close();
        hR->show();
    }
    else if(ui->SystemButton->isChecked())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("系统管理员无法注册！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else//未选择方式 弹出警告
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("未选择注册方式！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
}

void Login::on_exitButton_clicked()
{
    qApp->exit(0);
}



