#ifndef ROOM_H
#define ROOM_H

/****************************README************************************/
/****************************客房类*************************************/
/****************************END***************************************/

#include <QString>

class Room
{
public:
    Room(QString roomType,QString hotelname,QString description,float fixedPrice,float discount,int roomNum,int roomRestNum);
    Room();
    QString m_description;
    float m_fixedPrice;
    float m_discount;
    int m_roomNum;
    int m_roomRestNum;
    inline QString GetRoomType() const {return m_roomType;}
    inline QString GetHotelname() const {return m_hotelname;}
private:
    QString m_roomType;//SingleRoom DoubleRoom TripleRoom KingSizeRoom SuiteRoom
    QString m_hotelname;
};


#endif // ROOM_H
