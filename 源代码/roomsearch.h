#ifndef ROOMSEARCH_H
#define ROOMSEARCH_H

/****************************README*************************************/
/*************************客房搜索窗口************************************/
/*****************************END***************************************/

#include "room.h"
#include <QDialog>
#include <QLinkedList>

namespace Ui {
class RoomSearch;
}

class RoomSearch : public QDialog
{
    Q_OBJECT

public:
    explicit RoomSearch(QLinkedList<Room> &roomList,QWidget *parent = 0);
    ~RoomSearch();
    QLinkedList<Room> &m_roomList;

private slots:
    void on_searchButton_clicked();

private:
    Ui::RoomSearch *ui;
};

bool priceHighToLow(const Room room1,const Room room2);

bool priceLowToHigh(const Room room1,const Room room2);

bool discountHighToLow(const Room room1,const Room room2);

bool discountLowToHigh(const Room room1,const Room room2);

bool roomRestNumHighToLow(const Room room1,const Room room2);

bool roomRestNumLowToHigh(const Room room1,const Room room2);


#endif // ROOMSEARCH_H
