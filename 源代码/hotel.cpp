#include "hotel.h"
#include "databasesl.h"
#include "databasesl.h"
#include <QString>

Hotel::Hotel()//无参数的构造函数
{
}

//构造函数
Hotel::Hotel(QString hotelname,QString city,QString district,QString hotelPhonenum,QString ownerName,
             int singleNum,int doubleNum,int tripleNum,int kingSizeNum,int suiteNum,
             int singleRestNum,int doubleRestNum,int tripleRestNum,int kingSizeRestNum,int suiteRestNum,
             float singleFixedPrice,float doubleFixedPrice,float tripleFixedPrice,float kingSizeFixedPrize,float suiteFixedPrize,
             float singleDiscount,float doubleDiscount,float tripleDiscount,float kingSizeDiscount,float suiteDiscount,
             float evaluation,
             QString singleDescription,QString doubleDescription,QString tripleDescription,QString kingSizeDescription,QString suiteDescription,
             int evaluationTimes,int isChecked)
{
    m_isChecked = isChecked;
    m_hotelname = hotelname;
    m_city = city;
    m_district = district;
    m_hotelPhonenum = hotelPhonenum;
    m_ownerName = ownerName;
    m_evaluation = evaluation;
    m_evaluationTimes = evaluationTimes;
    m_SingleRoom = Room("SingleRoom",hotelname,singleDescription,singleFixedPrice,singleDiscount,singleNum,singleRestNum);
    m_DoubleRoom = Room("DoubleRoom",hotelname,doubleDescription,doubleFixedPrice,doubleDiscount,doubleNum,doubleRestNum);
    m_TripleRoom = Room("TripleRoom",hotelname,tripleDescription,tripleFixedPrice,tripleDiscount,tripleNum,tripleRestNum);
    m_KingSizeRoom = Room("KingSizeRoom",hotelname,kingSizeDescription,kingSizeFixedPrize,kingSizeDiscount,kingSizeNum,kingSizeRestNum);
    m_SuiteRoom = Room("SuiteRoom",hotelname,suiteDescription,suiteFixedPrize,suiteDiscount,suiteNum,suiteRestNum);
}



void Hotel::Save()
{
    //调用外部接口的保存函数
    hotelDatabaseSave(m_hotelname,m_city,m_district,m_hotelPhonenum,m_ownerName,
                      m_SingleRoom.m_roomNum,m_DoubleRoom.m_roomNum,m_TripleRoom.m_roomNum,m_KingSizeRoom.m_roomNum,m_SuiteRoom.m_roomNum,
                      m_SingleRoom.m_roomRestNum,m_DoubleRoom.m_roomRestNum,m_TripleRoom.m_roomRestNum,m_KingSizeRoom.m_roomRestNum,m_SuiteRoom.m_roomRestNum,
                      m_SingleRoom.m_fixedPrice,m_DoubleRoom.m_fixedPrice,m_TripleRoom.m_fixedPrice,m_KingSizeRoom.m_fixedPrice,m_SuiteRoom.m_fixedPrice,
                      m_SingleRoom.m_discount,m_DoubleRoom.m_discount,m_TripleRoom.m_discount,m_KingSizeRoom.m_discount,m_SuiteRoom.m_discount,
                      m_evaluation,
                      m_SingleRoom.m_description,m_DoubleRoom.m_description,m_TripleRoom.m_description,m_KingSizeRoom.m_description,m_SuiteRoom.m_description,
                      m_evaluationTimes,m_isChecked);
}

void Hotel::ChangeInfo(const Hotel newHotel,QLinkedList<Hotel> &list)
{
    QLinkedList<Hotel>::iterator iter;//创建迭代器
    for (iter=list.begin();iter!=list.end();iter++)
    {
       if((*iter).m_hotelname == newHotel.m_hotelname)
       {
           list.erase(iter);//删除对应的节点
           break;
       }
    }
    list<<newHotel;//添加新的节点
}
