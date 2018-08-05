#ifndef CUSREGISTER_H
#define CUSREGISTER_H

/****************************README*************************************/
/***************************顾客注册界面***********************************/
/*******************作为顾客无法重复注册为酒店管理员**************************/
/****************************END****************************************/

#include <QDialog>

namespace Ui {
class cusRegister;
}

class cusRegister : public QDialog
{
    Q_OBJECT

public:
    explicit cusRegister(QWidget *parent = 0);
    ~cusRegister();

private slots:
    void on_returnButton_clicked();//点击返回按钮

    void on_checkButton_clicked();//点击确认注册按钮

private:
    Ui::cusRegister *ui;
};

#endif // CUSREGISTER_H
