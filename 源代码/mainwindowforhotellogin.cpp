#include "mainwindowforhotellogin.h"
#include "ui_mainwindowforhotellogin.h"
#include "login.h"
#include <QPlainTextEdit>
#include "peopleinfochange.h"
#include "hotelinfochange.h"
#include "updateorder.h"
#include <QTableWidget>
#include <QScrollBar>


MainWindowForHotelLogin::MainWindowForHotelLogin(QLinkedList<Customer> customerList,QLinkedList<HotelManager> hotelManagerList,QLinkedList<Hotel> hotelNotCheckedList,QLinkedList<Hotel> hotelList,QLinkedList<Order> orderList,
                                                 QWidget *parent,QString logingUsername,QString logingHotelname):
    QMainWindow(parent),m_logingUsername(logingUsername),m_hotelList(hotelList),m_orderList(orderList),m_logingHotelname(logingHotelname),
    m_hotelNotCheckedList(hotelNotCheckedList),m_hotelManagerList(hotelManagerList),m_customerList(customerList),
    ui(new Ui::MainWindowForHotelLogin)
{
    ui->setupUi(this);
}

void MainWindowForHotelLogin::closeEvent(QCloseEvent *event)
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
        //清空数据库
        hotelDatabaseEmpty();
        orderDatabaseEmpty();
        humanDatabaseEmpty();
        //写入数据
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
        QLinkedList<Order>::iterator o_iter;
        for (o_iter=m_orderList.begin();o_iter!=m_orderList.end();o_iter++)
        {
            (*o_iter).Save();
        }
        QLinkedList<Customer>::iterator c_iter;
        for (c_iter=m_customerList.begin();c_iter!=m_customerList.end();c_iter++)
        {
            (*c_iter).Save();
        }
        QLinkedList<HotelManager>::iterator hm_iter;
        for (hm_iter=m_hotelManagerList.begin();hm_iter!=m_hotelManagerList.end();hm_iter++)
        {
            (*hm_iter).Save();
        }
        event->accept(); // 接受退出信号，程序退出
    }
}

MainWindowForHotelLogin::MainWindowForHotelLogin(QWidget *parent):QMainWindow(parent),
    ui(new Ui::MainWindowForHotelLogin)
{
    ui->setupUi(this);
}

MainWindowForHotelLogin::~MainWindowForHotelLogin()
{
    delete ui;
}

void MainWindowForHotelLogin::on_action_P_triggered()//点击查看个人信息按钮
{
    QLinkedList<HotelManager>::iterator iter;
    for (iter=m_hotelManagerList.begin();iter!=m_hotelManagerList.end();iter++)
    {
       if((*iter).GetUsername() == m_logingUsername)
       {
           (*iter).ShowInfo();
           break;
       }
    }
}

void MainWindowForHotelLogin::on_action_C_triggered()//点击修改个人信息按钮
{
    PeopleInfoChange *p = new PeopleInfoChange(m_customerList,m_hotelManagerList,false,m_logingUsername);//酒店管理员修改个人信息
    p->exec();
}

void MainWindowForHotelLogin::on_action_F_triggered()//点击退出账号按钮
{
    if(this->close() == QDialog::Accepted)
    {
        //打开登陆界面
        Login *l = new Login();
        l->exec();
    }
}

void MainWindowForHotelLogin::on_action_Q_triggered()//点击退出程序按钮
{
    this->close();
}

void MainWindowForHotelLogin::on_action_A_triggered()//点击查看酒店信息按钮
{
    //根据酒店名查找酒店链表中的数据 创建QPlainTextEdit输出数据
    QPlainTextEdit *plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setWindowIcon(QIcon(":/myimages/icon/酒店.png"));
    plainTextEdit->setStyleSheet("font: 14pt '张海山锐谐体';");
    plainTextEdit->setReadOnly(true);
    plainTextEdit->resize(500,500);
    plainTextEdit->setWindowTitle("酒店信息");
    QLinkedList<Hotel>::iterator iter;
    Hotel h;
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == m_logingHotelname)
       {
           h = (*iter);
           break;
       }
    }
    for (iter=m_hotelNotCheckedList.begin();iter!=m_hotelNotCheckedList.end();iter++)
    {
       if((*iter).GetHotelname() == m_logingHotelname)
       {
           h = (*iter);
           break;
       }
    }
    if(h.m_isChecked == 1)
    {
        plainTextEdit->setPlainText(QObject::tr("酒店名: ")+h.GetHotelname()+
                                    QObject::tr("\n所在城市: ")+h.m_city+
                                    QObject::tr("\n所在地区: ")+h.m_district+
                                    QObject::tr("\n酒店电话: ")+h.m_hotelPhonenum+
                                    QObject::tr("\n酒店是否已经通过审核: 是")+
                                    QObject::tr("\n酒店评分: ")+QString::number(h.m_evaluation)+
                                    QObject::tr("\n\n单人间总数: ")+QString::number(h.m_SingleRoom.m_roomNum)+
                                    QObject::tr("\n单人间余数: ")+QString::number(h.m_SingleRoom.m_roomRestNum)+
                                    QObject::tr("\n单人间定价: ")+QString::number(h.m_SingleRoom.m_fixedPrice)+
                                    QObject::tr("\n单人间折扣: ")+QString::number(h.m_SingleRoom.m_discount)+
                                    QObject::tr("\n单人间描述: ")+h.m_SingleRoom.m_description+
                                    QObject::tr("\n\n双人间总数: ")+QString::number(h.m_DoubleRoom.m_roomNum)+
                                    QObject::tr("\n双人间余数: ")+QString::number(h.m_DoubleRoom.m_roomRestNum)+
                                    QObject::tr("\n双人间定价: ")+QString::number(h.m_DoubleRoom.m_fixedPrice)+
                                    QObject::tr("\n双人间折扣: ")+QString::number(h.m_DoubleRoom.m_discount)+
                                    QObject::tr("\n双人间描述: ")+h.m_DoubleRoom.m_description+
                                    QObject::tr("\n\n三人间总数: ")+QString::number(h.m_TripleRoom.m_roomNum)+
                                    QObject::tr("\n三人间余数: ")+QString::number(h.m_TripleRoom.m_roomRestNum)+
                                    QObject::tr("\n三人间定价: ")+QString::number(h.m_TripleRoom.m_fixedPrice)+
                                    QObject::tr("\n三人间折扣: ")+QString::number(h.m_TripleRoom.m_discount)+
                                    QObject::tr("\n三人间描述: ")+h.m_TripleRoom.m_description+
                                    QObject::tr("\n\n大床间总数: ")+QString::number(h.m_KingSizeRoom.m_roomNum)+
                                    QObject::tr("\n大床间余数: ")+QString::number(h.m_KingSizeRoom.m_roomRestNum)+
                                    QObject::tr("\n大床间定价: ")+QString::number(h.m_KingSizeRoom.m_fixedPrice)+
                                    QObject::tr("\n大床间折扣: ")+QString::number(h.m_KingSizeRoom.m_discount)+
                                    QObject::tr("\n大床间描述: ")+h.m_KingSizeRoom.m_description+
                                    QObject::tr("\n\n套间总数: ")+QString::number(h.m_SuiteRoom.m_roomNum)+
                                    QObject::tr("\n套床间余数: ")+QString::number(h.m_SuiteRoom.m_roomRestNum)+
                                    QObject::tr("\n套床间定价: ")+QString::number(h.m_SuiteRoom.m_fixedPrice)+
                                    QObject::tr("\n套床间折扣: ")+QString::number(h.m_SuiteRoom.m_discount)+
                                    QObject::tr("\n套床间描述: ")+h.m_SuiteRoom.m_description);
        plainTextEdit->show();
    }
    else
    {
        plainTextEdit->setPlainText(QObject::tr("酒店名: ")+h.GetHotelname()+
                                    QObject::tr("\n所在城市: ")+h.m_city+
                                    QObject::tr("\n所在地区: ")+h.m_district+
                                    QObject::tr("\n酒店电话: ")+h.m_hotelPhonenum+
                                    QObject::tr("\n酒店是否已经通过审核: 否")+
                                    QObject::tr("\n酒店评分: ")+QString::number(h.m_evaluation)+
                                    QObject::tr("\n\n单人间总数: ")+QString::number(h.m_SingleRoom.m_roomNum)+
                                    QObject::tr("\n单人间余数: ")+QString::number(h.m_SingleRoom.m_roomRestNum)+
                                    QObject::tr("\n单人间定价: ")+QString::number(h.m_SingleRoom.m_fixedPrice)+
                                    QObject::tr("\n单人间折扣: ")+QString::number(h.m_SingleRoom.m_discount)+
                                    QObject::tr("\n单人间描述: ")+h.m_SingleRoom.m_description+
                                    QObject::tr("\n\n双人间总数: ")+QString::number(h.m_DoubleRoom.m_roomNum)+
                                    QObject::tr("\n双人间余数: ")+QString::number(h.m_DoubleRoom.m_roomRestNum)+
                                    QObject::tr("\n双人间定价: ")+QString::number(h.m_DoubleRoom.m_fixedPrice)+
                                    QObject::tr("\n双人间折扣: ")+QString::number(h.m_DoubleRoom.m_discount)+
                                    QObject::tr("\n双人间描述: ")+h.m_DoubleRoom.m_description+
                                    QObject::tr("\n\n三人间总数: ")+QString::number(h.m_TripleRoom.m_roomNum)+
                                    QObject::tr("\n三人间余数: ")+QString::number(h.m_TripleRoom.m_roomRestNum)+
                                    QObject::tr("\n三人间定价: ")+QString::number(h.m_TripleRoom.m_fixedPrice)+
                                    QObject::tr("\n三人间折扣: ")+QString::number(h.m_TripleRoom.m_discount)+
                                    QObject::tr("\n三人间描述: ")+h.m_TripleRoom.m_description+
                                    QObject::tr("\n\n大床间总数: ")+QString::number(h.m_KingSizeRoom.m_roomNum)+
                                    QObject::tr("\n大床间余数: ")+QString::number(h.m_KingSizeRoom.m_roomRestNum)+
                                    QObject::tr("\n大床间定价: ")+QString::number(h.m_KingSizeRoom.m_fixedPrice)+
                                    QObject::tr("\n大床间折扣: ")+QString::number(h.m_KingSizeRoom.m_discount)+
                                    QObject::tr("\n大床间描述: ")+h.m_KingSizeRoom.m_description+
                                    QObject::tr("\n\n套间总数: ")+QString::number(h.m_SuiteRoom.m_roomNum)+
                                    QObject::tr("\n套床间余数: ")+QString::number(h.m_SuiteRoom.m_roomRestNum)+
                                    QObject::tr("\n套床间定价: ")+QString::number(h.m_SuiteRoom.m_fixedPrice)+
                                    QObject::tr("\n套床间折扣: ")+QString::number(h.m_SuiteRoom.m_discount)+
                                    QObject::tr("\n套床间描述: ")+h.m_SuiteRoom.m_description);
        plainTextEdit->show();
    }
}

void MainWindowForHotelLogin::on_action_D_triggered()//点击修改酒店信息按钮
{
    HotelInfoChange *h = new HotelInfoChange(m_logingHotelname,m_hotelList);
    h->exec();
}

void MainWindowForHotelLogin::on_action_E_triggered()//点击查看所有订单按钮
{
    //利用迭代器筛选出本酒店的所有订单 组成一个链表
    QLinkedList<Order> myOrderList;
    QLinkedList<Order>::iterator iter0;
    for (iter0=m_orderList.begin();iter0!=m_orderList.end();iter0++)
    {
        if((*iter0).GetHotelname() == m_logingHotelname)
        {
            myOrderList<<(*iter0);
        }
    }
    //用迭代器访问新建链表中的每个订单的数据 创建QTableWidget输出数据
    QTableWidget *tableWidget = new QTableWidget(myOrderList.size(),9);//设置行列数
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
    tableWidget->setWindowIcon(QIcon(":/myimages/icon/列表.png"));
    tableWidget->setWindowTitle("所有订单信息");//设置标题
    tableWidget->resize(500, 400);//设置窗口大小
     QStringList header;//设置表头
     header<<"用户名"<<"酒店名"<<"客房类型"<<"付款状态"<<"入住状态"<<"评价状态"<<"开始时间"<<"结束时间"<<"订单金额";
     tableWidget->setHorizontalHeaderLabels(header);
     tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
     QLinkedList<Order>::iterator iter;
     int i = 0;
     for (iter=myOrderList.begin();iter!=myOrderList.end();iter++)//判断每个订单状态 加入表格中
     {
         if((*iter).m_paymentStatus == 0)//未付款
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("未付款"));
             tableWidget->setItem(i,4,new QTableWidgetItem("未入住"));
             tableWidget->setItem(i,5,new QTableWidgetItem("未评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         else if ((*iter).m_paymentStatus == 1&&(*iter).m_checkInStatus == 0)//已付款，未入住
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("已付款"));
             tableWidget->setItem(i,4,new QTableWidgetItem("未入住"));
             tableWidget->setItem(i,5,new QTableWidgetItem("未评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         else if ((*iter).m_paymentStatus == -1)//已取消
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("已取消"));
             tableWidget->setItem(i,4,new QTableWidgetItem("未入住"));
             tableWidget->setItem(i,5,new QTableWidgetItem("未评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         else if ((*iter).m_checkInStatus == 1)//正在入住
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("已付款"));
             tableWidget->setItem(i,4,new QTableWidgetItem("正在入住"));
             tableWidget->setItem(i,5,new QTableWidgetItem("未评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         else if ((*iter).m_checkInStatus == 2&&(*iter).m_evaluateStatus == 0)//已退房，未评价
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("已付款"));
             tableWidget->setItem(i,4,new QTableWidgetItem("已退房"));
             tableWidget->setItem(i,5,new QTableWidgetItem("未评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         else if ((*iter).m_checkInStatus == 2&&(*iter).m_evaluateStatus == 1)//已退房，已评价
         {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter).GetUsername()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter).GetHotelname()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter).GetRoomType()));
             tableWidget->setItem(i,3,new QTableWidgetItem("已付款"));
             tableWidget->setItem(i,4,new QTableWidgetItem("已退房"));
             tableWidget->setItem(i,5,new QTableWidgetItem("已评价"));
             tableWidget->setItem(i,6,new QTableWidgetItem((*iter).GetBeginDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,7,new QTableWidgetItem((*iter).GetEndDate().toString("yyyy.MM.dd")));
             tableWidget->setItem(i,8,new QTableWidgetItem(QString::number((*iter).GetAmount())));
         }
         i++;
     }
     tableWidget->show();
}

void MainWindowForHotelLogin::on_action_U_triggered()//点击更新订单状态按钮
{
    UpdateOrder *uo = new UpdateOrder(m_logingUsername,m_logingHotelname,m_hotelList,m_orderList);
    uo->show();
}

void MainWindowForHotelLogin::on_action_V_triggered()
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
