#ifndef HOTELSEARCH_H
#define HOTELSEARCH_H

/****************************README*************************************/
/*************************酒店搜索窗口************************************/
/*****************************END***************************************/

#include <QDialog>
#include "hotel.h"
#include <QLinkedList>
#include <algorithm>

namespace Ui {
class HotelSearch;
}

class HotelSearch : public QDialog
{

    Q_OBJECT

public:
    explicit HotelSearch(QLinkedList<Hotel> &hotelList,QWidget *parent = 0);
    ~HotelSearch();
    QLinkedList<Hotel> &m_hotelList;

private slots:
    void on_hotelnameButton_clicked();//点击按酒店名搜索按钮

    void on_hotelAddressButton_clicked();//点击按酒店地址搜索按钮


private:
    Ui::HotelSearch *ui;
};

bool evaluationHighToLow(const Hotel hotel1,const Hotel hotel2);

bool evaluationLowToHigh(const Hotel hotel1,const Hotel hotel2);

#endif // HOTELSEARCH_H
