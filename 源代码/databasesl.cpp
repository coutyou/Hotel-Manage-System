#include "databasesl.h"
#include "people.h"

/*          ↓↓↓↓↓↓↓↓↓↓↓↓数据库连接函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

QSqlDatabase DatabaseConnect(const int connectType)
{
    QSqlDatabase Database;
    //先建立连接
    if (QSqlDatabase::contains("qt_sql_default_connection"))//若已建立连接
    {
        Database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else//若未建立连接 则建立连接
    {
        Database = QSqlDatabase::addDatabase("QSQLITE");//选择sqlite
        Database.setDatabaseName("Database.db");//设置数据库名
    }
    //尝试打开数据库
    if(!Database.open())//若打开失败
    {
        qDebug() << "Error: Failed to connect database." << Database.lastError();
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("数据库打开失败！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        exit(1);
    }
    else if(connectType == 1)//人类连接
    {
        //若打开成功 创建注册信息表格
        QSqlQuery query;
           query.exec("create table register (username vchar primary key, password vchar, phonenum vchar,"
                      " name vchar, isFemale int, id vchar, isCus int)");
        return Database;
    }
    else if(connectType == 2)//酒店连接
    {
        //若打开成功 创建酒店信息表格
        QSqlQuery query;
           query.exec("create table hotel (hotelname vchar primary key, city vchar, district vchar, hotelPhonenum vchar, ownerName vchar,"
                      " singleNum int, doubleNum int, tripleNum int, kingSizeNum int, suiteNum int,"
                      " singleRestNum int, doubleRestNum int, tripleRestNum int, kingSizeRestNum int, suiteRestNum int,"
                      " singleFixerPrize float, doubleFixerPrize float, tripleFixerPrize float, kingSizeFixerPrize float, suiteFixerPrize float,"
                      " singleDiscount float, doubleDiscount float, tripleDiscount float, kingSizeDiscount float, suiteDiscount float,"
                      " evaluation float,"
                      " singleDescription vchar, doubleDescription vchar, tripleDescription vchar, kingSizeDescription vchar, suiteDescription vchar, "
                      " evaluationTimes int, isChecked int)");
        return Database;
    }
    else//订单连接
    {
        //若打开成功 创建订单信息表格
        QSqlQuery query;
           query.exec("create table myorder (username vchar, hotelname vchar, roomType vchar,"
                      " paymentStatus int, checkInStatus int, evaluateStatus int, beginDate date, endDate date, amount float)");
           return Database;
    }
}

/*          ↑↑↑↑↑↑↑↑↑↑↑↑数据库连接函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */

/*          ↓↓↓↓↓↓↓↓↓↓↓↓人类相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

bool IsNumber(QString qstrSrc)
{
    QByteArray ba = qstrSrc.toLatin1();
    const char *s = ba.data();
    bool bret = true;
    while(*s)
    {
        if(*s>='0' && *s<='9')
        {

        }
        else
        {
            bret = false;
            break;
        }
        s++;
    }
    return bret;
}

bool IsChinese(QString qstrSrc)
{
    int nCount = qstrSrc.count();
    bool bret = true;
    for(int i=0; i<nCount; ++i)
    {
        QChar cha = qstrSrc.at(i);
        ushort uni = cha.unicode();
        if((uni >= 0x4E00 && uni <= 0x9FA5))
        {

        }
        else
        {
            bret = false;
            break;
        }
    }
    return bret;
}

bool IsId(QString qstrSrc)
{
    int nCount = qstrSrc.count();
    bool bret = true;
    if (qstrSrc[nCount-1] == 'X'||(qstrSrc[nCount-1]>='0' && qstrSrc[nCount-1]<='9'))
    {

    }
    else
    {
        return false;
    }
    for(int i=0; i<nCount-1; ++i)
    {
        QChar c = qstrSrc.at(i);
        if((c >= '0' && c <= '9'))
        {

        }
        else
        {
            bret = false;
            break;
        }
    }
    return bret;
}

void registerDatabaseSave(const QString username,const QString password,const QString phonenum,
                          const QString name,const int isFemale,const QString id,const int isCus)
{
        QSqlDatabase db = DatabaseConnect(1);//获得注册信息数据库
        //SQL语句的创建
        QSqlQuery sql_query;
        QString insert_sql = "insert into register values (?, ?, ?, ?, ?, ?, ?)";
        sql_query.prepare(insert_sql);
        sql_query.addBindValue(username);
        sql_query.addBindValue(password);
        sql_query.addBindValue(phonenum);
        sql_query.addBindValue(name);
        sql_query.addBindValue(isFemale);
        sql_query.addBindValue(id);
        sql_query.addBindValue(isCus);
        if(!sql_query.exec())//若SQL语句执行失败
        {
            qDebug() << sql_query.lastError();
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("注册失败！"),QMessageBox::Ok);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
            db.close();//关闭数据库
        }
        else//若SQL语句执行成功
        {
            qDebug() << "human save successfully!";
            QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("注册成功！"),QMessageBox::Ok);
            message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
            message.exec();
            db.close();//关闭数据库
        }
}


bool registerDatabaseCheck(const QString username,const QString password,const bool isCusLoging)
{
    QSqlDatabase db = DatabaseConnect(1);//获得注册信息数据库
    QSqlQuery sql_query;
    sql_query.prepare("SELECT * FROM register WHERE username = (?) ");//取出用户名对应的数据
    sql_query.bindValue(0,username);
    if(username.isEmpty())//若未输入用户名
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("未输入用户名！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        db.close();
        return false;
    }
    else if (password.isEmpty())//若未输入密码
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("未输入密码！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        db.close();
        return false;
    }
    else if(!sql_query.exec())//若SQL语句执行失败 弹出警告
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("数据库打开失败！"),QMessageBox::Ok);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
        qDebug()<<sql_query.lastError();
        db.close();
        return false;
    }
    else//若SQL语句执行成功
    {
       sql_query.next();
       QString gotPsw = sql_query.value(1).toString();
       int gotIs = sql_query.value(6).toInt();
       if(gotPsw==password&&gotIs==1&&isCusLoging)//若顾客登陆成功
       {
           db.close();
           return true;
       }
       else if(gotPsw==password&&gotIs==0&&(!isCusLoging))//若酒店顾客成功
       {
           db.close();
           return true;
       }
       else//否则弹出警告
       {
           QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("用户名或密码或登陆方式错误！"),QMessageBox::Ok);
           message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
           message.exec();
           db.close();
           return false;
       }
    }
}

QLinkedList<Customer> customerLinkedListCreate()
{
    QLinkedList<Customer> customerLinkedList;
    QSqlDatabase db = DatabaseConnect(1);
    QSqlQuery sql_query;
    QString select_all_sql = "select * from register";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query.next())
        {
            //插入节点
            if(sql_query.value(6).toInt() == 1)
            {
                customerLinkedList<<Customer(sql_query.value(0).toString(),sql_query.value(1).toString(),sql_query.value(2).toString(),
                                             sql_query.value(3).toString(),sql_query.value(5).toString(),sql_query.value(4).toInt());
            }
        }
        db.close();
        qDebug()<<customerLinkedList.size();
        return customerLinkedList;
    }
}

QLinkedList<HotelManager> hotelManagerLinkedListCreate()
{
    QLinkedList<HotelManager> hotelManagerLinkedList;
    QSqlDatabase db = DatabaseConnect(1);
    QSqlQuery sql_query0;
    QString select_all_sql = "select * from register";
    sql_query0.prepare(select_all_sql);
    if(!sql_query0.exec())
    {
        qDebug()<<sql_query0.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query0.next())
        {
            //插入节点
            if(sql_query0.value(6).toInt() == 0)
            {
                QString qstr = "";
                QSqlQuery sql_query;
                sql_query.prepare("SELECT * FROM hotel WHERE ownerName = (?) ");//取出用户名对应的数据
                sql_query.addBindValue(sql_query0.value(0).toString());
                if(!sql_query.exec())//若SQL语句执行失败 弹出警告
                {
                    QMessageBox::warning(NULL,QObject::tr("警告！"),QObject::tr("数据库打开失败！"), QMessageBox::Ok);
                    qDebug()<<sql_query.lastError();
                    exit(1);
                }
                else//若SQL语句执行成功 返回酒店名
                {
                    sql_query.next();
                    qstr = sql_query.value(0).toString();
                }
                hotelManagerLinkedList<<HotelManager(qstr,sql_query0.value(0).toString(),sql_query0.value(1).toString(),sql_query0.value(2).toString(),
                                             sql_query0.value(3).toString(),sql_query0.value(5).toString(),sql_query0.value(4).toInt());
            }
        }
        db.close();
        qDebug()<<hotelManagerLinkedList.size()<<(*hotelManagerLinkedList.begin()).GetHotelName();
        return hotelManagerLinkedList;
    }
}

void humanDatabaseEmpty()
{
    QSqlDatabase db = DatabaseConnect(1);
    QSqlQuery sql_query;
    QString clear_sql = "delete from register";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        db.close();
    }
    else
    {
        qDebug() << "table cleared";
        db.close();
    }
}

/*          ↑↑↑↑↑↑↑↑↑↑↑↑人类相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */

/*          ↓↓↓↓↓↓↓↓↓↓↓↓酒店相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

void hotelDatabaseSave(const QString hotelname,const QString city,const QString district,const QString hotelPhonenum,const QString ownerName,
                       const int singleNum,const int doubleNum,const int tripleNum,const int kingSizeNum,const int suiteNum,
                       const int singleRestNum,const int doubleRestNum,const int tripleRestNum,const int kingSizeRestNum,const int suiteRestNum,
                       const float singleFixedPrice,const float doubleFixedPrice,const float tripleFixedPrice,const float kingSizeFixedPrize,const float suiteFixedPrize,
                       const float singleDiscount,const float doubleDiscount,const float tripleDiscount,const float kingSizeDiscount,const float suiteDiscount,
                       const float evaluation,
                       const QString singleDescription,const QString doubleDescription,const QString tripleDescription,const QString kingSizeDescription,const QString suiteDescription,
                       const int evaluationTimes,const int isChecked)
{
    QSqlDatabase db = DatabaseConnect(2);//获得注册信息数据库
    //SQL语句的创建
    QSqlQuery sql_query;
    QString insert_sql = "insert into hotel values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                         " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                         " ?, ?, ?, ?, ?, ?, ?, ?, ?, ?,"
                         " ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(hotelname);
    sql_query.addBindValue(city);
    sql_query.addBindValue(district);
    sql_query.addBindValue(hotelPhonenum);
    sql_query.addBindValue(ownerName);
    sql_query.addBindValue(singleNum);
    sql_query.addBindValue(doubleNum);
    sql_query.addBindValue(tripleNum);
    sql_query.addBindValue(kingSizeNum);
    sql_query.addBindValue(suiteNum);
    sql_query.addBindValue(singleRestNum);
    sql_query.addBindValue(doubleRestNum);
    sql_query.addBindValue(tripleRestNum);
    sql_query.addBindValue(kingSizeRestNum);
    sql_query.addBindValue(suiteRestNum);
    sql_query.addBindValue(singleFixedPrice);
    sql_query.addBindValue(doubleFixedPrice);
    sql_query.addBindValue(tripleFixedPrice);
    sql_query.addBindValue(kingSizeFixedPrize);
    sql_query.addBindValue(suiteFixedPrize);
    sql_query.addBindValue(singleDiscount);
    sql_query.addBindValue(doubleDiscount);
    sql_query.addBindValue(tripleDiscount);
    sql_query.addBindValue(kingSizeDiscount);
    sql_query.addBindValue(suiteDiscount);
    sql_query.addBindValue(evaluation);
    sql_query.addBindValue(singleDescription);
    sql_query.addBindValue(doubleDescription);
    sql_query.addBindValue(tripleDescription);
    sql_query.addBindValue(kingSizeDescription);
    sql_query.addBindValue(suiteDescription);
    sql_query.addBindValue(evaluationTimes);
    sql_query.addBindValue(isChecked);
    if(!sql_query.exec())//若SQL语句执行失败
    {
        qDebug() << sql_query.lastError();
        db.close();//关闭数据库
    }
    else//若SQL语句执行成功
    {
        qDebug() << "hotel save successfully!";
        db.close();//关闭数据库
    }
}

QLinkedList<Hotel> hotelLinkedListCreate()
{
    QLinkedList<Hotel>hotelLinkedList;
    QSqlDatabase db = DatabaseConnect(2);//获得注册信息数据库
    QSqlQuery sql_query;
    QString select_all_sql = "select * from hotel";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query.next())
        {
            //插入节点
            if(sql_query.value(32).toInt() == 1)//若已经过审核
            {
                hotelLinkedList<<Hotel(sql_query.value(0).toString(),sql_query.value(1).toString(),sql_query.value(2).toString(),sql_query.value(3).toString(),sql_query.value(4).toString(),
                                       sql_query.value(5).toInt(),sql_query.value(6).toInt(),sql_query.value(7).toInt(),sql_query.value(8).toInt(),sql_query.value(9).toInt(),
                                       sql_query.value(10).toInt(),sql_query.value(11).toInt(),sql_query.value(12).toInt(),sql_query.value(13).toInt(),sql_query.value(14).toInt(),
                                       sql_query.value(15).toFloat(),sql_query.value(16).toFloat(),sql_query.value(17).toFloat(),sql_query.value(18).toFloat(),sql_query.value(19).toFloat(),
                                       sql_query.value(20).toFloat(),sql_query.value(21).toFloat(),sql_query.value(22).toFloat(),sql_query.value(23).toFloat(),sql_query.value(24).toFloat(),
                                       sql_query.value(25).toFloat(),
                                       sql_query.value(26).toString(),sql_query.value(27).toString(),sql_query.value(28).toString(),sql_query.value(29).toString(),sql_query.value(30).toString(),
                                       sql_query.value(31).toInt(),1);
            }
        }
        db.close();
        return hotelLinkedList;
    }
}

QLinkedList<Hotel> hotelLinkedListForPlatformManagerCreate()
{
    QLinkedList<Hotel>hotelLinkedList;
    QSqlDatabase db = DatabaseConnect(2);//获得酒店信息数据库
    QSqlQuery sql_query;
    QString select_all_sql = "select * from hotel";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query.next())
        {
            //插入节点
            if(sql_query.value(32).toInt() == 0)//若未通过审核
            {
                hotelLinkedList<<Hotel(sql_query.value(0).toString(),sql_query.value(1).toString(),sql_query.value(2).toString(),sql_query.value(3).toString(),sql_query.value(4).toString(),
                                       sql_query.value(5).toInt(),sql_query.value(6).toInt(),sql_query.value(7).toInt(),sql_query.value(8).toInt(),sql_query.value(9).toInt(),
                                       sql_query.value(10).toInt(),sql_query.value(11).toInt(),sql_query.value(12).toInt(),sql_query.value(13).toInt(),sql_query.value(14).toInt(),
                                       sql_query.value(15).toFloat(),sql_query.value(16).toFloat(),sql_query.value(17).toFloat(),sql_query.value(18).toFloat(),sql_query.value(19).toFloat(),
                                       sql_query.value(20).toFloat(),sql_query.value(21).toFloat(),sql_query.value(22).toFloat(),sql_query.value(23).toFloat(),sql_query.value(24).toFloat(),
                                       sql_query.value(25).toFloat(),
                                       sql_query.value(26).toString(),sql_query.value(27).toString(),sql_query.value(28).toString(),sql_query.value(29).toString(),sql_query.value(30).toString(),
                                       sql_query.value(31).toInt(),0);
            }
        }
        db.close();
        return hotelLinkedList;
    }
}

QLinkedList<Room> roomLinkedListCreate()
{
    QLinkedList<Room>roomLinkedList;
    QSqlDatabase db = DatabaseConnect(2);//获得注册信息数据库
    QSqlQuery sql_query;
    QString select_all_sql = "select * from hotel";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query.next())
        {
            //若酒店过审且客房总数不为零则插入节点
            if(sql_query.value(32).toInt() == 1)
            {
                if(sql_query.value(5).toInt()!=0)
                {
                    roomLinkedList<<Room("SingleRoom",sql_query.value(0).toString(),sql_query.value(26).toString(),sql_query.value(15).toFloat(),sql_query.value(20).toFloat(),sql_query.value(5).toInt(),sql_query.value(10).toInt());
                }
                if(sql_query.value(6).toInt()!=0)
                {
                    roomLinkedList<<Room("DoubleRoom",sql_query.value(0).toString(),sql_query.value(27).toString(),sql_query.value(16).toFloat(),sql_query.value(21).toFloat(),sql_query.value(6).toInt(),sql_query.value(11).toInt());
                }
                if(sql_query.value(7).toInt()!=0)
                {
                    roomLinkedList<<Room("TripleRoom",sql_query.value(0).toString(),sql_query.value(28).toString(),sql_query.value(17).toFloat(),sql_query.value(22).toFloat(),sql_query.value(7).toInt(),sql_query.value(12).toInt());
                }
                if(sql_query.value(8).toInt()!=0)
                {
                    roomLinkedList<<Room("KingSizeRoom",sql_query.value(0).toString(),sql_query.value(29).toString(),sql_query.value(18).toFloat(),sql_query.value(23).toFloat(),sql_query.value(8).toInt(),sql_query.value(13).toInt());
                }
                if(sql_query.value(9).toInt()!=0)
                {
                    roomLinkedList<<Room("SuiteRoom",sql_query.value(0).toString(),sql_query.value(30).toString(),sql_query.value(19).toFloat(),sql_query.value(24).toFloat(),sql_query.value(9).toInt(),sql_query.value(14).toInt());
                }
            }
        }
        db.close();
        return roomLinkedList;
    }
}


void hotelDatabaseEmpty()
{
    QSqlDatabase db = DatabaseConnect(2);//获得注册信息数据库
    QSqlQuery sql_query;
    QString clear_sql = "delete from hotel";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        db.close();
    }
    else
    {
        qDebug() << "table cleared";
        db.close();
    }
}

QString getHotelName(const QString username)
{
    QSqlDatabase db = DatabaseConnect(2);//获得酒店信息数据库
    QSqlQuery sql_query;
    sql_query.prepare("SELECT * FROM hotel WHERE ownerName = (?) ");//取出用户名对应的数据
    sql_query.addBindValue(username);
    if(!sql_query.exec())//若SQL语句执行失败 弹出警告
    {
        QMessageBox::warning(NULL,QObject::tr("警告！"),QObject::tr("数据库打开失败！"), QMessageBox::Ok);
        qDebug()<<sql_query.lastError();
        db.close();
        exit(1);
    }
    else//若SQL语句执行成功 返回酒店名
    {
        sql_query.next();
        QString hn = sql_query.value(0).toString();
        db.close();
        return hn;
    }
}

/*          ↑↑↑↑↑↑↑↑↑↑↑↑酒店相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */

/*          ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓订单相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

void orderDatabaseSave(const QDate beginDate,const QDate endDate,const float amount,const QString username,const QString hotelname,const QString roomType,
                       const int paymentStatus,const int checkInStatus,const int evaluateStatus)
{
    QSqlDatabase db = DatabaseConnect(3);//获得注册信息数据库
    //SQL语句的创建
    QSqlQuery sql_query;
    QString insert_sql = "insert into myorder values (?, ?, ?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(username);
    sql_query.addBindValue(hotelname);
    sql_query.addBindValue(roomType);
    sql_query.addBindValue(paymentStatus);
    sql_query.addBindValue(checkInStatus);
    sql_query.addBindValue(evaluateStatus);
    sql_query.addBindValue(beginDate);
    sql_query.addBindValue(endDate);
    sql_query.addBindValue(amount);
    if(!sql_query.exec())//若SQL语句执行失败
    {
        qDebug() << sql_query.lastError();
        db.close();//关闭数据库
    }
    else//若SQL语句执行成功
    {
        qDebug() << "myorder save successfully!";
        db.close();//关闭数据库
    }
}

QLinkedList<Order> orderLinkedListCreate()
{
    QLinkedList<Order>orderLinkedList;
    QSqlDatabase db = DatabaseConnect(3);//获得注册信息数据库
    QSqlQuery sql_query;
    QString select_all_sql = "select * from myorder";
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        db.close();
        exit(1);
    }
    else
    {
        while(sql_query.next())
        {
            //插入节点
            orderLinkedList<<Order(sql_query.value(6).toDate(),sql_query.value(7).toDate(),sql_query.value(8).toFloat(),
                                   sql_query.value(0).toString(),sql_query.value(1).toString(),sql_query.value(2).toString(),
                                   sql_query.value(3).toInt(),sql_query.value(4).toInt(),sql_query.value(5).toInt());
        }
        db.close();
        return orderLinkedList;
    }

}

void orderDatabaseEmpty()
{
    QSqlDatabase db = DatabaseConnect(3);//获得注册信息数据库
    QSqlQuery sql_query;
    QString clear_sql = "delete from myorder";
    sql_query.prepare(clear_sql);
    if(!sql_query.exec())
    {
        qDebug() << sql_query.lastError();
        db.close();
    }
    else
    {
        qDebug() << "table cleared";
        db.close();
    }
}

/*          ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑订单相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */

