#ifndef ORDER_H
#define ORDER_H

/****************************README*************************************/
/***************************订单类***************************************/
/****************同一个顾客在一家酒店只能存在一个未完成的订单*******************/
/****************************END****************************************/

#include <QString>
#include <QDate>

class Order
{
public:
    Order(QDate beginDate,QDate endDate,float amount,QString username,QString hotelname,QString roomType,int paymentStatus,int checkInStatus,int evaluateStatus);
    Order();
    int m_paymentStatus;//0 未付款 ，1 已付款 ，-1 已取消（退款）
    int m_checkInStatus;//0 未入住 ，1 正在入住 ，2 已退房
    int m_evaluateStatus;//0 未评价 ， 1 已评价
    void Save();//类内部的保存函数 调用前先清空order表
    inline QString GetHotelname() const {return m_hotelname;}
    inline QString GetUsername() const {return m_username;}
    inline QString GetRoomType() const {return m_roomType;}
    inline QDate GetBeginDate() const {return m_beginDate;}
    inline QDate GetEndDate() const {return m_endDate;}
    inline float GetAmount() const {return m_amount;}
private:
    float m_amount;
    QDate m_beginDate;
    QDate m_endDate;
    QString m_username;
    QString m_hotelname;
    QString m_roomType;

};

#endif // ORDER_H
