#include "room.h"

Room::Room(QString roomType,QString hotelname,QString description,float fixedPrice,float discount,int roomNum,int roomRestNum)
{
    m_roomType = roomType;
    m_hotelname = hotelname;
    m_description = description;
    m_fixedPrice = fixedPrice;
    m_discount = discount;
    m_roomNum = roomNum;
    m_roomRestNum = roomRestNum;
}

Room::Room()
{

}

