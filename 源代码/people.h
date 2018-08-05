#ifndef PEOPLE_H
#define PEOPLE_H

/****************************README*************************************/
/**************************人类为基类*************************************/
/********************派生出顾客类和酒店管理员类******************************/
/****************************END****************************************/

#include <QString>
#include "databasesl.h"

class People
{
public:
    People();   
    QString m_password;
    QString m_phonenum;
    QString m_name;
    QString m_id;
    int m_isFemale;
    QString GetUsername() const {return m_username;}
    virtual void Save() = 0;
    virtual void ShowInfo() = 0;
protected:
    QString m_username;

};

class Customer :public People
{
public:
    Customer(QString username,QString password,QString phonenum,QString name,QString id,int isFemale);
    Customer();
    void Save();
    void ShowInfo();
    void ChangeInfo(const Customer newCus,QLinkedList<Customer> &list);
};

class HotelManager:public People
{
public:
    HotelManager(QString hotelname,QString username,QString password,QString phonenum,QString name,QString id,int isFemale);
    HotelManager();
    inline QString GetHotelName() const {return m_hotelname;}
    void Save();
    void ShowInfo();
    void ChangeInfo(const HotelManager newHM,QLinkedList<HotelManager> &list);
private:
    QString m_hotelname;
};
#endif // PEOPLE_H
