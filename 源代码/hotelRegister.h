#ifndef HOTELREGISTER_H
#define HOTELREGISTER_H

/****************************README*************************************/
/***************************酒店注册界面*****************************/
/*需要同时注册酒店管理员的相关信息，且作为管理员无法重复注册为顾客，一个管理员只能管理一个酒店*/
/****************************END****************************************/

#include <QDialog>

namespace Ui {
class hotelRegister;
}

class hotelRegister : public QDialog
{
    Q_OBJECT

public:
    explicit hotelRegister(QWidget *parent = 0);
    ~hotelRegister();

private:
    Ui::hotelRegister *ui;

private slots:
    void on_returnButton_clicked();//返回点击槽

    void on_checkButton_clicked();//确认注册点击槽
};

#endif // HOTELREGISTER_H
