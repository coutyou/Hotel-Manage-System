#include "hotelinfochange.h"
#include "ui_hotelinfochange.h"
#include "hotel.h"
#include "databasesl.h"
#include <QMessageBox>

HotelInfoChange::HotelInfoChange(QString logingHotelname,QLinkedList<Hotel> &hotelList,QWidget *parent) :
    QDialog(parent),m_logingHotelname(logingHotelname),m_hotelList(hotelList),
    ui(new Ui::HotelInfoChange)
{
    ui->setupUi(this);
}

HotelInfoChange::~HotelInfoChange()
{
    delete ui;
}

void HotelInfoChange::on_checkButton_clicked()//点击确认修改按钮
{
    QLinkedList<Hotel>::iterator iter;//创建迭代器找到对应的节点
    Hotel h;
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == m_logingHotelname)
       {
           h = (*iter);
           break;
       }
    }
    if(ui->cityInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("城市名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->districtInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("地区名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->hotelPhonenumInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("酒店电话不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsChinese(ui->cityInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效的城市名！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsChinese(ui->districtInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效的地区名！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsNumber(ui->hotelPhonenumInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效酒店电话输入！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->singleSpinBox->value() == 0&&!((ui->singleFixedPriceInput->value() == 0)&&(ui->singleDiscountInput->value() == 0)&&(ui->singleDescribeInput->text().isEmpty())))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("单人间数据输入非法！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->doubleSpinBox->value() == 0&&!((ui->doubleFixedPriceInput->value() == 0)&&(ui->doubleDiscountInput->value() == 0)&&(ui->doubleDescribeInput->text().isEmpty())))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("双人间数据输入非法！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->tripleSpinBox->value() == 0&&!((ui->tripleFixedPriceInput->value() == 0)&&(ui->tripleDiscountInput->value() == 0)&&(ui->tripleDescribeInput->text().isEmpty())))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("三人间数据输入非法！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->kingSizeSpinBox->value() == 0&&!((ui->kingSizeFixedPriceInput->value() == 0)&&(ui->kingSizeDiscountInput->value() == 0)&&(ui->kingSizeDescribeInput->text().isEmpty())))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("大床间数据输入非法！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->suiteSpinBox->value() == 0&&!((ui->suiteFixedPriceInput->value() == 0)&&(ui->suiteDiscountInput->value() == 0)&&(ui->suiteDescribeInput->text().isEmpty())))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("套间数据输入非法！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if((ui->singleSpinBox->value()-(h.m_SingleRoom.m_roomNum-h.m_SingleRoom.m_roomRestNum)) < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("单人间数量过少！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if((ui->doubleSpinBox->value()-(h.m_DoubleRoom.m_roomNum-h.m_DoubleRoom.m_roomRestNum)) < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("双人间数量过少！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if((ui->tripleSpinBox->value()-(h.m_TripleRoom.m_roomNum-h.m_TripleRoom.m_roomRestNum)) < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("三人间数量过少！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if((ui->kingSizeSpinBox->value()-(h.m_KingSizeRoom.m_roomNum-h.m_KingSizeRoom.m_roomRestNum)) < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("大床间数量过少！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if((ui->suiteSpinBox->value()-(h.m_SuiteRoom.m_roomNum-h.m_SuiteRoom.m_roomRestNum)) < 0)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("套间数量过少！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        //利用对应节点的数据创造新的节点插入酒店链表中
        Hotel n(m_logingHotelname,ui->cityInput->text(),ui->districtInput->text(),ui->hotelPhonenum->text(),h.GetOwnerName(),
                ui->singleSpinBox->value(),ui->doubleSpinBox->value(),ui->tripleSpinBox->value(),ui->kingSizeSpinBox->value(),ui->suiteSpinBox->value(),
                (ui->singleSpinBox->value()-(h.m_SingleRoom.m_roomNum-h.m_SingleRoom.m_roomRestNum)),(ui->doubleSpinBox->value()-(h.m_DoubleRoom.m_roomNum-h.m_DoubleRoom.m_roomRestNum)),
                (ui->tripleSpinBox->value()-(h.m_TripleRoom.m_roomNum-h.m_TripleRoom.m_roomRestNum)),(ui->kingSizeSpinBox->value()-(h.m_KingSizeRoom.m_roomNum-h.m_KingSizeRoom.m_roomRestNum)),
                (ui->suiteSpinBox->value()-(h.m_SuiteRoom.m_roomNum-h.m_SuiteRoom.m_roomRestNum)),
                ui->singleFixedPriceInput->value(),ui->doubleFixedPriceInput->value(),ui->tripleFixedPriceInput->value(),ui->kingSizeFixedPriceInput->value(),ui->suiteFixedPriceInput->value(),
                ui->singleDiscountInput->value(),ui->doubleDiscountInput->value(),ui->tripleDiscountInput->value(),ui->kingSizeDiscountInput->value(),ui->suiteDiscountInput->value(),
                h.m_evaluation,
                ui->singleDescribeInput->text(),ui->doubleDescribeInput->text(),ui->tripleDescribeInput->text(),ui->suiteDescribeInput->text(),ui->suiteDescribeInput->text(),h.m_evaluationTimes,0);
        h.ChangeInfo(n,m_hotelList);
        QMessageBox message(QMessageBox::Information,QObject::tr("恭喜！"),QObject::tr("酒店信息修改成功！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/info-circle.png"));
        message.exec();
        this->close();
    }
}
