#include "mainwindowforplatformmanager.h"
#include "ui_mainwindowforplatformmanager.h"
#include <QTableWidget>
#include "login.h"
#include <QMessageBox>
#include "databasesl.h"
#include "checkhotel.h"
#include <QPlainTextEdit>
#include <QScrollBar>


MainWindowForPlatformManager::MainWindowForPlatformManager(QLinkedList<Hotel> hotelNotCheckedList,QLinkedList<Hotel> hotelList,QWidget *parent) :
    QMainWindow(parent),m_hotelList(hotelList),m_hotelNotCheckedList(hotelNotCheckedList),
    ui(new Ui::MainWindowForPlatformManager)
{
    ui->setupUi(this);
}

MainWindowForPlatformManager::~MainWindowForPlatformManager()
{
    delete ui;
}

void MainWindowForPlatformManager::on_action_A_triggered()//点击添加审核通过酒店按钮
{
    CheckHotel *ch = new CheckHotel(m_hotelNotCheckedList,m_hotelList);
    ch->show();
}

void MainWindowForPlatformManager::on_action_S_triggered()//点击查看所有待审核酒店按钮
{
    //用迭代器访问链表中的每个酒店的数据 创建QTableWidget输出数据
    QTableWidget *tableWidget = new QTableWidget(m_hotelNotCheckedList.size(),30);//设置行列数
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置无法编辑
    //设置水平、垂直滑动条
    tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    tableWidget->verticalHeader()->setVisible(false);//隐藏列表头
    tableWidget->horizontalHeader()->setStretchLastSection(true);//打开自动填充
    tableWidget->setFrameShape(QFrame::NoFrame);
    tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置表头居中
    QFont font;//设置表头加粗
    font.setBold(true);
    tableWidget->horizontalHeader()->setFont(font);
    tableWidget->verticalHeader()->setFont(font);
    tableWidget->setAlternatingRowColors(true);//打开交替颜色
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(102,102,153);color: white;};}");//设置表头颜色
    //设置表格颜色
    tableWidget->setStyleSheet("alternate-background-color:rgb(204,204,204);background-color:rgb(255,255,255);selection-color:Black;selection-background-color:rgb(239,240,220);");
    tableWidget->setWindowIcon(QIcon(":/myimages/icon/酒店.png"));
    tableWidget->setWindowTitle("所有未审核酒店及其客房信息");//设置标题
    tableWidget->resize(1000, 800);//设置窗口大小
     QStringList header;//设置表头
     header<<"酒店名"<<"城市"<<"地区"<<"酒店电话"<<"评分"
           <<"单人间剩余房间数"<<"单人间定价"<<"单人间折扣"<<"单人间价格"<<"单人间介绍"
           <<"双人间剩余房间数"<<"双人间定价"<<"双人间折扣"<<"双人间价格"<<"双人间介绍"
           <<"三人间剩余房间数"<<"三人间定价"<<"三人间折扣"<<"三人间价格"<<"三人间介绍"
           <<"大床间剩余房间数"<<"大床间定价"<<"大床间折扣"<<"大床间价格"<<"大床间介绍"
           <<"套间剩余房间数"<<"套间定价"<<"套间折扣"<<"套间价格"<<"套间介绍";
     tableWidget->setHorizontalHeaderLabels(header);
     tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
     QLinkedList<Hotel>::iterator iter;
     int i = 0;
     for (iter=m_hotelNotCheckedList.begin();iter!=m_hotelNotCheckedList.end();iter++)
     {
         tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetHotelname()));
         tableWidget->setItem(i,1,new QTableWidgetItem((*iter).m_city));
         tableWidget->setItem(i,2,new QTableWidgetItem((*iter).m_district));
         tableWidget->setItem(i,3,new QTableWidgetItem((*iter).m_hotelPhonenum));
         tableWidget->setItem(i,4,new QTableWidgetItem(QString::number((*iter).m_evaluation)));
         tableWidget->setItem(i,5,new QTableWidgetItem(QString::number((*iter).m_SingleRoom.m_roomRestNum)));
         tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((*iter).m_SingleRoom.m_fixedPrice)));
         tableWidget->setItem(i,7,new QTableWidgetItem(QString::number((*iter).m_SingleRoom.m_discount)));
         tableWidget->setItem(i,8,new QTableWidgetItem(QString::number(((*iter).m_SingleRoom.m_fixedPrice)*(1-(*iter).m_SingleRoom.m_discount))));
         tableWidget->setItem(i,9,new QTableWidgetItem((*iter).m_SingleRoom.m_description));
         tableWidget->setItem(i,10,new QTableWidgetItem(QString::number((*iter).m_DoubleRoom.m_roomRestNum)));
         tableWidget->setItem(i,11,new QTableWidgetItem(QString::number((*iter).m_DoubleRoom.m_fixedPrice)));
         tableWidget->setItem(i,12,new QTableWidgetItem(QString::number((*iter).m_DoubleRoom.m_discount)));
         tableWidget->setItem(i,13,new QTableWidgetItem(QString::number(((*iter).m_DoubleRoom.m_fixedPrice)*(1-(*iter).m_DoubleRoom.m_discount))));
         tableWidget->setItem(i,14,new QTableWidgetItem((*iter).m_DoubleRoom.m_description));
         tableWidget->setItem(i,15,new QTableWidgetItem(QString::number((*iter).m_TripleRoom.m_roomRestNum)));
         tableWidget->setItem(i,16,new QTableWidgetItem(QString::number((*iter).m_TripleRoom.m_fixedPrice)));
         tableWidget->setItem(i,17,new QTableWidgetItem(QString::number((*iter).m_TripleRoom.m_discount)));
         tableWidget->setItem(i,18,new QTableWidgetItem(QString::number(((*iter).m_TripleRoom.m_fixedPrice)*(1-(*iter).m_TripleRoom.m_discount))));
         tableWidget->setItem(i,19,new QTableWidgetItem((*iter).m_TripleRoom.m_description));
         tableWidget->setItem(i,20,new QTableWidgetItem(QString::number((*iter).m_KingSizeRoom.m_roomRestNum)));
         tableWidget->setItem(i,21,new QTableWidgetItem(QString::number((*iter).m_KingSizeRoom.m_fixedPrice)));
         tableWidget->setItem(i,22,new QTableWidgetItem(QString::number((*iter).m_KingSizeRoom.m_discount)));
         tableWidget->setItem(i,23,new QTableWidgetItem(QString::number(((*iter).m_KingSizeRoom.m_fixedPrice)*(1-(*iter).m_KingSizeRoom.m_discount))));
         tableWidget->setItem(i,24,new QTableWidgetItem((*iter).m_KingSizeRoom.m_description));
         tableWidget->setItem(i,25,new QTableWidgetItem(QString::number((*iter).m_SuiteRoom.m_roomRestNum)));
         tableWidget->setItem(i,26,new QTableWidgetItem(QString::number((*iter).m_SuiteRoom.m_fixedPrice)));
         tableWidget->setItem(i,27,new QTableWidgetItem(QString::number((*iter).m_SuiteRoom.m_discount)));
         tableWidget->setItem(i,28,new QTableWidgetItem(QString::number(((*iter).m_SuiteRoom.m_fixedPrice)*(1-(*iter).m_SuiteRoom.m_discount))));
         tableWidget->setItem(i,29,new QTableWidgetItem((*iter).m_SuiteRoom.m_description));
         i++;
     }
     tableWidget->show();
}

void MainWindowForPlatformManager::on_action_Q_triggered()//点击退出程序按钮
{
    this->close();
}

void MainWindowForPlatformManager::on_action_F_triggered()//点击退出账号按钮
{
    if(this->close() == QDialog::Accepted)
    {
        //打开登陆界面
        Login *l = new Login();
        l->exec();
    }
}

void MainWindowForPlatformManager::closeEvent(QCloseEvent *event)//关闭窗口事件触发
{
    int i;
    QMessageBox message(QMessageBox::Question,QObject::tr("退出"),QObject::tr("确认退出？"),QMessageBox::Yes|QMessageBox::No,this);
    message.setWindowIcon(QIcon(":/myimages/icon/question-circle.png"));
    i = message.exec();
    if(i == QMessageBox::No)
    {
        event->ignore(); // 忽略退出信号，程序继续进行
    }
    else if(i == QMessageBox::Yes)
    {
        //清空数据表
        hotelDatabaseEmpty();
        //将链表内数据写入数据库
        QLinkedList<Hotel>::iterator h_iter;
        for (h_iter=m_hotelList.begin();h_iter!=m_hotelList.end();h_iter++)
        {
            (*h_iter).Save();
        }
        QLinkedList<Hotel>::iterator hf_iter;
        for (hf_iter=m_hotelNotCheckedList.begin();hf_iter!=m_hotelNotCheckedList.end();hf_iter++)
        {
            (*hf_iter).Save();
        }
        event->accept(); // 接受退出信号，程序退出
    }
}

void MainWindowForPlatformManager::on_action_V_triggered()
{
    QPlainTextEdit *plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setWindowIcon(QIcon(":/myimages/icon2/mobiletesting移动测试.png"));
    //设定滑动条样式
    plainTextEdit->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    plainTextEdit->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
    "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
    "QScrollBar::handle:hover{background:gray;}"
    "QScrollBar::sub-line{background:transparent;}"
    "QScrollBar::add-line{background:transparent;}");
    plainTextEdit->setStyleSheet("font: 14pt '张海山锐谐体';");
    plainTextEdit->setReadOnly(true);//设置为只读
    plainTextEdit->resize(500,400);//设置窗口大小
    plainTextEdit->setWindowTitle("版本信息");//设置窗口标题
    plainTextEdit->setPlainText(QObject::tr("版本号： Ver 1.7\n\n"
                                            "开发者信息： 游晶 清华大学自动化系71班\n\n"
                                            "更新日志： \n\n"
                                            "2018.7.18\n* 完成登陆界面的构造\n* 采用用sqlite进行数据库读写\n\n"
                                            "2018.7.19\n* 完成各个类的大致设计\n\n"
                                            "2018.7.20\n* 优化了登陆窗口，注册窗口和主窗口之间的衔接\n* 根据类的设计优化了酒店注册表的信息内容\n* 完成类的数据成员的构造\n\n"
                                            "2018.7.21\n* 基本完成类的函数成员的构造\n* 完成room、hotel、order的链表函数构造\n\n"
                                            "2018.7.22\n* 完成所有数据的Save and lord接口的构造\n* 采用QLinkedList动态完成数据的读写与修改\n* 完成查看和修改账户信息的功能\n\n"
                                            "2018.7.23\n* 完成了搜索和排序相关功能的实现\n* 优化了界面焦点的显示\n* 修复了一个登陆界面闪退bug\n* 修复了顾客与酒店管理员可以相互登陆主窗口的bug\n* 完成了订单添加和显示功能\n\n"
                                            "2018.7.24\n* 完成订单管理功能\n* 修复了一个酒店余数bug\n* 添加了平台管理员的角色并实现其审核酒店的功能\n\n"
                                            "2018.7.25\n* 将函数形参尽可能地改为const类型\n* 修改了对话框标题\n* 优化了类数据成员的数据类型\n\n"
                                            "2018.7.26\n* 修复了一个无法添加订单的bug\n* 优化了输入界面的对齐\n* 优化了界面的焦点\n* 优化了链表排序的方法\n\n"
                                            "2018.7.27\n* 添加了三个主窗口图标\n\n"
                                            "2018.7.28\n* 添加了版本信息窗口\n* 添加了对输入信息的检查\n* 添加了登录前的图片界面\n\n"
                                            "2018.7.29\n* 添加了QMessageBox的图标\n* 添加了各个窗口的图标\n* 优化了登陆界面的提示信息\n* 优化了系统管理员的登陆方式\n* 优化了登陆界面的UX\n* 减少了源代码中使用数据库的比例\n\n"
                                            "2018.7.30\n* 优化了所有表格以及文本框的UX\n* 修复了一个警示框bug\n* 为订单类添加了开始结束时间和订单金额\n\n"
                                            "2018.7.31\n* 修复了酒店信息修改的一个bug\n* 对所有窗口进行了界面优化\n"));
    plainTextEdit->show();
}
