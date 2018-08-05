#include "people.h"
#include "databasesl.h"
#include <QPlainTextEdit>
#include <QScrollBar>

People::People()
{

}

Customer::Customer(QString username,QString password,QString phonenum,QString name,QString id,int isFemale)
{
    m_username = username;
    m_password = password;
    m_phonenum = phonenum;
    m_name = name;
    m_id = id;
    m_isFemale = isFemale;
}

Customer::Customer()
{
}

void Customer::Save()
{
    QSqlDatabase db = DatabaseConnect(1);//获得注册信息数据库
    //SQL语句的创建
    QSqlQuery sql_query;
    QString insert_sql = "insert into register values (?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(m_username);
    sql_query.addBindValue(m_password);
    sql_query.addBindValue(m_phonenum);
    sql_query.addBindValue(m_name);
    sql_query.addBindValue(m_isFemale);
    sql_query.addBindValue(m_id);
    sql_query.addBindValue(1);
    if(!sql_query.exec())//若SQL语句执行失败
    {
        qDebug() << sql_query.lastError();
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("保存失败！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        db.close();//关闭数据库
    }
    else//若SQL语句执行成功
    {
        db.close();//关闭数据库
    }
}

void Customer::ShowInfo()
{
    //根据用户名查找数据库中的数据 创建QPlainTextEdit输出数据
    QPlainTextEdit *plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setStyleSheet("font: 14pt '张海山锐谐体';");
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
    plainTextEdit->setWindowIcon(QIcon(":/myimages/icon/icon-id card.png"));
    plainTextEdit->setReadOnly(true);//设置为只读
    plainTextEdit->resize(500,350);//设置窗口大小
    plainTextEdit->setWindowTitle("个人信息");//设置窗口标题
    if(m_isFemale == 0)
    {
         plainTextEdit->setPlainText(QObject::tr("用户名:  ")+m_username+
                                     QObject::tr("\n\n手机号:  ")+m_phonenum+
                                     QObject::tr("\n\n姓名:  ")+m_name+
                                     QObject::tr("\n\n性别:  男")+
                                     QObject::tr("\n\n身份证号:  ")+m_id);
     }
     else
     {
        plainTextEdit->setPlainText(QObject::tr("用户名:  ")+m_username+
                                    QObject::tr("\n\n手机号:  ")+m_phonenum+
                                    QObject::tr("\n\n姓名:  ")+m_name+
                                    QObject::tr("\n\n性别:  女")+
                                    QObject::tr("\n\n身份证号:  ")+m_id);

     }
     plainTextEdit->show();

}

void Customer::ChangeInfo(const Customer newCus,QLinkedList<Customer> &list)
{
    QLinkedList<Customer>::iterator iter;//创建迭代器
    for (iter=list.begin();iter!=list.end();iter++)
    {
       if((*iter).GetUsername() == newCus.GetUsername())
       {
           list.erase(iter);//删除对应的节点
           break;
       }
    }
    list<<newCus;//添加新的节点
}

HotelManager::HotelManager(QString hotelname,QString username,QString password,QString phonenum,QString name,QString id,int isFemale)
{
    m_hotelname = hotelname;
    m_username = username;
    m_password = password;
    m_phonenum = phonenum;
    m_name = name;
    m_id = id;
    m_isFemale = isFemale;
}

HotelManager::HotelManager()
{

}

void HotelManager::Save()
{
    QSqlDatabase db = DatabaseConnect(1);//获得注册信息数据库
    //SQL语句的创建
    QSqlQuery sql_query;
    QString insert_sql = "insert into register values (?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(m_username);
    sql_query.addBindValue(m_password);
    sql_query.addBindValue(m_phonenum);
    sql_query.addBindValue(m_name);
    sql_query.addBindValue(m_isFemale);
    sql_query.addBindValue(m_id);
    sql_query.addBindValue(0);
    if(!sql_query.exec())//若SQL语句执行失败
    {
        qDebug() << sql_query.lastError();
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("保存失败！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        db.close();//关闭数据库
    }
    else//若SQL语句执行成功
    {
        qDebug() << "Hotel Manager Save Successfully!";
        db.close();//关闭数据库
    }
}

void HotelManager::ShowInfo()
{
    //根据用户名查找数据库中的数据 创建QPlainTextEdit输出数据
    QPlainTextEdit *plainTextEdit = new QPlainTextEdit();
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
    plainTextEdit->setWindowIcon(QIcon(":/myimages/icon2/个人头像.png"));
    plainTextEdit->setStyleSheet("font: 14pt '张海山锐谐体';");
    plainTextEdit->setReadOnly(true);
    plainTextEdit->resize(500,350);
    plainTextEdit->setWindowTitle("个人信息");
    if(m_isFemale == 0)
    {
         plainTextEdit->setPlainText(QObject::tr("用户名:  ")+m_username+
                                     QObject::tr("\n\n手机号:  ")+m_phonenum+
                                     QObject::tr("\n\n姓名:  ")+m_name+
                                     QObject::tr("\n\n性别:  男")+
                                     QObject::tr("\n\n身份证号:  ")+m_id);
    }
    else
    {
        plainTextEdit->setPlainText(QObject::tr("用户名:  ")+m_username+
                                    QObject::tr("\n\n手机号:  ")+m_phonenum+
                                    QObject::tr("\n\n姓名:  ")+m_name+
                                    QObject::tr("\n\n性别: 女")+
                                    QObject::tr("\n\n身份证号:  ")+m_id);

    }
     plainTextEdit->show();
}

void HotelManager::ChangeInfo(const HotelManager newHM,QLinkedList<HotelManager> &list)
{
    QLinkedList<HotelManager>::iterator iter;//创建迭代器
    for (iter=list.begin();iter!=list.end();iter++)
    {
       if((*iter).GetUsername() == newHM.GetUsername())
       {
           list.erase(iter);//删除对应的节点
           break;
       }
    }
    list<<newHM;//添加新的节点
}



