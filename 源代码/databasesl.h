#ifndef DATABASESL_H
#define DATABASESL_H

/****************************README****************************************/
/***************数据库有关函数，为外部提供接口，并且方便类内函数调用***************/
/********************数据库储存在文件Database.db中***************************/
/***数据库里register表储存人类注册信息，hotel表储存酒店信息，myorder表储存订单信息****/
/******************************END****************************************/

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QMessageBox>
#include <QLinkedList>
#include "order.h"
#include "hotel.h"
#include "room.h"
#include <QIcon>

//防止与people.h相互包含进行提前声明
class Customer;
class HotelManager;


/*          ↓↓↓↓↓↓↓↓↓↓↓↓数据库连接函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

//打开注册信息数据库
QSqlDatabase DatabaseConnect(const int connectType);//1 人类 ，2 酒店 ，3 订单

/*          ↑↑↑↑↑↑↑↑↑↑↑↑数据库连接函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */




/*          ↓↓↓↓↓↓↓↓↓↓↓↓人类相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

bool IsNumber(QString qstrSrc);//判断输入是否为纯数字

bool IsChinese(QString qstrSrc);//判断输入是否为纯中文

bool IsId(QString qstrSrc);//判断输入是否为身份证号码

//注册时人类信息保存
void registerDatabaseSave(const QString username,const QString password,const QString phonenum,
                          const QString name,const int isFemale,const QString id,const int isCus);

//登录时判断用户名密码是否正确
bool registerDatabaseCheck(const QString username,const QString password,const bool isCusLoging);

//创建顾客链表
QLinkedList<Customer> customerLinkedListCreate();

//创建酒店管理员链表
QLinkedList<HotelManager> hotelManagerLinkedListCreate();

void humanDatabaseEmpty();

/*          ↑↑↑↑↑↑↑↑↑↑↑↑人类相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */




/*          ↓↓↓↓↓↓↓↓↓↓↓↓酒店相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

//注册时酒店信息保存
void hotelDatabaseSave(const QString hotelname,const QString city,const QString district,const QString hotelPhonenum,const QString ownerName,
                       const int singleNum,const int doubleNum,const int tripleNum,const int kingSizeNum,const int suiteNum,
                       const int singleRestNum,const int doubleRestNum,const int tripleRestNum,const int kingSizeRestNum,const int suiteRestNum,
                       const float singleFixedPrice,const float doubleFixedPrice,const float tripleFixedPrice,const float kingSizeFixedPrize,const float suiteFixedPrize,
                       const float singleDiscount,const float doubleDiscount,const float tripleDiscount,const float kingSizeDiscount,const float suiteDiscount,
                       const float evaluation,
                       const QString singleDescription,const QString doubleDescription,const QString tripleDescription,const QString kingSizeDescription,const QString suiteDescription,
                       const int evaluationTimes,const int isChecked);

//从数据库创建已通过审核酒店链表
QLinkedList<Hotel> hotelLinkedListCreate();

//从数据库创建未审核酒店链表
QLinkedList<Hotel> hotelLinkedListForPlatformManagerCreate();

//从数据库创建房间链表
QLinkedList<Room> roomLinkedListCreate();

//清空酒店表
void hotelDatabaseEmpty();

//用于通过酒店管理员用户名得到酒店名
QString getHotelName(const QString username);

/*          ↑↑↑↑↑↑↑↑↑↑↑↑酒店相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */

/*          ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓订单相关函数↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓          */

//提交订单时信息保存
void orderDatabaseSave(const QDate beginDate,const QDate endDate,const float amount,const QString username,const QString hotelname,const QString roomType,
                       const int paymentStatus,const int checkInStatus,const int evaluateStatus);

//从数据库创建订单链表
QLinkedList<Order> orderLinkedListCreate();

//清空订单表
void orderDatabaseEmpty();

/*          ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑订单相关函数↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑          */


#endif // DATABASESL_H
