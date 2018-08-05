#ifndef HOTEL_H
#define HOTEL_H

/****************************README*************************************/
/****************************酒店类**************************************/
/*****************************END***************************************/

#include <QString>
#include "room.h"

class Hotel
{
public:
    Hotel();
    Hotel(QString hotelname,QString city,QString district,QString hotelPhonenum,QString ownerName,
          int singleNum,int doubleNum,int tripleNum,int kingSizeNum,int suiteNum,
          int singleRestNum,int doubleRestNum,int tripleRestNum,int kingSizeRestNum,int suiteRestNum,
          float singleFixedPrice,float doubleFixedPrice,float tripleFixedPrice,float kingSizeFixedPrize,float suiteFixedPrize,
          float singleDiscount,float doubleDiscount,float tripleDiscount,float kingSizeDiscount,float suiteDiscount,
          float evaluation,
          QString singleDescription,QString doubleDescription,QString tripleDescription,QString kingSizeDescription,QString suiteDescription,
          int evaluationTimes,int isChecked);   
    QString m_city;
    QString m_district;
    QString m_hotelPhonenum;  
    float m_evaluation;
    int m_evaluationTimes;
    int m_isChecked;
    Room m_SingleRoom;
    Room m_DoubleRoom;
    Room m_TripleRoom;
    Room m_KingSizeRoom;
    Room m_SuiteRoom;
    void Save();//结束程序前保存至hotel表内 调用前清空hotel表
    void ChangeInfo(const Hotel newHotel,QLinkedList<Hotel> &list);//酒店管理员更改酒店信息（酒店名除外）
    inline QString GetHotelname() const {return m_hotelname;}
    inline QString GetOwnerName() const {return m_ownerName;}
private:
    QString m_hotelname;
    QString m_ownerName;

};

#endif // HOTEL_H
