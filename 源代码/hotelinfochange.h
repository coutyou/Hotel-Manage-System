#ifndef HOTELINFOCHANGE_H
#define HOTELINFOCHANGE_H

/****************************README*************************************/
/************************酒店信息更改窗口**********************************/
/*****************************END***************************************/

#include "hotel.h"
#include <QDialog>
#include <QLinkedList>

namespace Ui {
class HotelInfoChange;
}

class HotelInfoChange : public QDialog
{
    Q_OBJECT

public:
    explicit HotelInfoChange(QString logingHotelname,QLinkedList<Hotel> &hotelList,QWidget *parent = 0);
    QString m_logingHotelname;
    QLinkedList<Hotel> &m_hotelList;//得到动态酒店链表的引用 从而实现数据的更改
    ~HotelInfoChange();

private slots:
    void on_checkButton_clicked();

private:
    Ui::HotelInfoChange *ui;
};

#endif // HOTELINFOCHANGE_H
