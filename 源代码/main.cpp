#include "mainwindow.h"
#include "login.h"
#include "hotelRegister.h"
#include "cusRegister.h"
#include "showimage.h"
#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowImage s;
    s.move((a.desktop()->width() - s.width()) / 2, (a.desktop()->height() - s.height()) / 2);//将图片窗口移到屏幕中间
    s.show();
    QTimer::singleShot(4000, &s, SLOT(CloseAndOpen()));//设置一个四秒定时器，四秒后触发ShowImage类中的槽函数
    return a.exec();
}
