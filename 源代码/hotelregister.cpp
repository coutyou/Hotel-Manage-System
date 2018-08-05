#include "hotelRegister.h"
#include "ui_hotelregister.h"
#include "login.h"
#include "databasesl.h"

hotelRegister::hotelRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hotelRegister)
{
    ui->setupUi(this);
}

hotelRegister::~hotelRegister()
{
    delete ui;
}

void hotelRegister::on_returnButton_clicked()//点击返回按钮
{
    //关闭注册界面打开登陆界面
    this->close();
    Login *lg = new Login;
    lg->exec();
}

void hotelRegister::on_checkButton_clicked()
{
    if(ui->hotelNameInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("酒店名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->cityInput->text().isEmpty())
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
    else if(ui->usernameInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("用户名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->passwordInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("密码不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->phonenumInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->nameInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->idInput->text().isEmpty())
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号不能为空！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->phonenumInput->text().size() != 11)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("手机号长度错误！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(ui->idInput->text().size() != 18)
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("身份证号长度错误！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsNumber(ui->phonenumInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效手机号输入！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsChinese(ui->nameInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("真实姓名输入非纯中文！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else if(!IsId(ui->idInput->text()))
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无效身份证号输入！"),QMessageBox::Ok,this);
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
    else
    {
        //调用保存函数 关闭注册窗口 新建登陆窗口
        hotelDatabaseSave(ui->hotelNameInput->text(),ui->cityInput->text(),ui->districtInput->text(),ui->hotelPhonenumInput->text(),ui->usernameInput->text(),
                          ui->singleSpinBox->value(),ui->doubleSpinBox->value(),ui->tripleSpinBox->value(),ui->kingSizeSpinBox->value(),ui->suiteSpinBox->value(),
                          ui->singleSpinBox->value(),ui->doubleSpinBox->value(),ui->tripleSpinBox->value(),ui->kingSizeSpinBox->value(),ui->suiteSpinBox->value(),
                          ui->singleFixedPriceInput->value(),ui->doubleFixedPriceInput->value(),ui->tripleFixedPriceInput->value(),ui->kingSizeFixedPriceInput->value(),ui->suiteFixedPriceInput->value(),
                          ui->singleDiscountInput->value(),ui->doubleDiscountInput->value(),ui->tripleDiscountInput->value(),ui->kingSizeDiscountInput->value(),ui->suiteDiscountInput->value(),
                          3,ui->singleDescribeInput->text(),ui->doubleDescribeInput->text(),ui->tripleDescribeInput->text(),ui->kingSizeDescribeInput->text(),ui->suiteDescribeInput->text(),0,0);
        registerDatabaseSave(ui->usernameInput->text(),ui->passwordInput->text(),ui->phonenumInput->text(),
                             ui->nameInput->text(),ui->sexComboBox->currentIndex(),ui->idInput->text(),0);
        this->close();
        Login *lg = new Login;
        lg->exec();
    }
}
