#include "showimage.h"
#include "ui_showimage.h"
#include "login.h"
#include <QPropertyAnimation>

ShowImage::ShowImage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowImage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉边框
    QPropertyAnimation *change = new QPropertyAnimation(this,"windowOpacity");//设置一个透明度渐变
    change->setDuration(2000);//设置渐变时间两秒
    change->setStartValue(0);
    change->setEndValue(1);//设置透明度的起始值
    change->start();
}

ShowImage::~ShowImage()
{
    delete ui;
}

void ShowImage::CloseAndOpen()
{
    //关闭该窗口打开新窗口
    this->close();
    Login *lg = new Login;
    lg->exec();
}
