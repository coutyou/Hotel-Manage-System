#include "order.h"
#include "databasesl.h"


Order::Order(QDate beginDate,QDate endDate,float amount,QString username,QString hotelname,QString roomType,int paymentStatus,int checkInStatus,int evaluateStatus)
{
    m_username = username;
    m_hotelname = hotelname;
    m_roomType = roomType;
    m_paymentStatus = paymentStatus;
    m_checkInStatus = checkInStatus;
    m_evaluateStatus = evaluateStatus;
    m_beginDate = beginDate;
    m_endDate = endDate;
    m_amount = amount;
}

Order::Order()
{

}

void Order::Save()
{
    //调用外部接口的保存函数
    orderDatabaseSave(m_beginDate,m_endDate,m_amount,m_username,m_hotelname,m_roomType,m_paymentStatus,
                      m_checkInStatus,m_evaluateStatus);
}
