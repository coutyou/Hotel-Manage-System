#ifndef LOGIN_H
#define LOGIN_H

/****************************README*************************************/
/***************************登陆界面*************************************/
/****************************END****************************************/

#include <QDialog>
#include <QMessageBox>

namespace  Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginButton_clicked();//点击登陆按钮

    void on_registerButton_clicked();//点击注册按钮

    void on_exitButton_clicked();//点击退出按钮



private:
    Ui::Login *ui;

};

#endif // LOGIN_H
