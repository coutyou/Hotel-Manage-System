#include "checkhotel.h"
#include "ui_checkhotel.h"

CheckHotel::CheckHotel(QLinkedList<Hotel> &hotelNotCheckedList,QLinkedList<Hotel> &hotelList,QWidget *parent) :
    QDialog(parent),m_hotelNotCheckedList(hotelNotCheckedList),m_hotelList(hotelList),
    ui(new Ui::CheckHotel)
{
    ui->setupUi(this);
}

CheckHotel::~CheckHotel()
{
    delete ui;
}

void CheckHotel::on_checkButton_clicked()
{
    int flag = 0;//判断是否有该酒店
    QLinkedList<Hotel>::iterator iter;
    Hotel h;
    for (iter=m_hotelNotCheckedList.begin();iter!=m_hotelNotCheckedList.end();iter++)
    {
        if((*iter).GetHotelname() == ui->hotelNameInput->text())
        {
            (*iter).m_isChecked = 1;
            h = (*iter);
            m_hotelNotCheckedList.erase(iter);
            m_hotelList<<h;
            flag = 1;
            break;
        }
    }
    if(flag == 0)//若没有该酒店
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无该酒店！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("审核成功！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
        message.exec();
        this->close();
    }
}
