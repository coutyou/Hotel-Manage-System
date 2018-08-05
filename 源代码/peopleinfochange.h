#ifndef PEOPLEINFOCHANGE_H
#define PEOPLEINFOCHANGE_H

/****************************README*************************************/
/************************人类信息更改窗口**********************************/
/*****************************END***************************************/

#include <QDialog>
#include "people.h"

namespace Ui {
class PeopleInfoChange;
}

class PeopleInfoChange : public QDialog
{
    Q_OBJECT

public:
    explicit PeopleInfoChange(QLinkedList<Customer> &customerList,QLinkedList<HotelManager> &hotelManagerList,bool isCus, QString logingUsername,QWidget *parent = 0);
    ~PeopleInfoChange();
    QString m_logingUsername;//用于查找
    QLinkedList<Customer> &m_customerList;
    QLinkedList<HotelManager> &m_hotelManagerList;
    bool m_isCus;//判断是否为顾客更改信息 从而调用不同的信息更改函数

private slots:
    void on_checkButton_clicked();

private:
    Ui::PeopleInfoChange *ui;
};

#endif // PEOPLEINFOCHANGE_H
