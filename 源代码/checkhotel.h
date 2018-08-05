#ifndef CHECKHOTEL_H
#define CHECKHOTEL_H

/****************************README*************************************/
/**********************添加审核成功酒店窗口********************************/
/****************************END****************************************/

#include <QDialog>
#include "hotel.h"
#include <QLinkedList>
#include <QMessageBox>

namespace Ui {
class CheckHotel;
}

class CheckHotel : public QDialog
{
    Q_OBJECT

public:
    explicit CheckHotel(QLinkedList<Hotel> &hotelNotCheckedList,QLinkedList<Hotel> &hotelList,QWidget *parent = 0);
    ~CheckHotel();
    QLinkedList<Hotel> &m_hotelNotCheckedList;
    QLinkedList<Hotel> &m_hotelList;

private slots:
    void on_checkButton_clicked();

private:
    Ui::CheckHotel *ui;
};

#endif // CHECKHOTEL_H
