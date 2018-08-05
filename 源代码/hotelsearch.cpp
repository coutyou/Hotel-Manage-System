#include "hotelsearch.h"
#include "ui_hotelsearch.h"
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QTableWidget>
#include <QList>
#include <QScrollBar>

bool evaluationHighToLow(const Hotel hotel1,const Hotel hotel2)
{
    return hotel1.m_evaluation > hotel2.m_evaluation;
}

bool evaluationLowToHigh(const Hotel hotel1,const Hotel hotel2)
{
    return hotel1.m_evaluation < hotel2.m_evaluation;
}

HotelSearch::HotelSearch(QLinkedList<Hotel> &hotelList,QWidget *parent) :
    QDialog(parent),m_hotelList(hotelList),
    ui(new Ui::HotelSearch)
{
    ui->setupUi(this);
}


HotelSearch::~HotelSearch()
{
    delete ui;
}

void HotelSearch::on_hotelnameButton_clicked()
{
    //根据酒店名查找酒店链表中的数据 创建QPlainTextEdit输出数据
    QPlainTextEdit *plainTextEdit = new QPlainTextEdit();
    plainTextEdit->setWindowIcon(QIcon(":/myimages/icon/酒店.png"));
    plainTextEdit->setStyleSheet("font: 14pt '张海山锐谐体';");
    plainTextEdit->setReadOnly(true);
    plainTextEdit->resize(500,500);
    plainTextEdit->setWindowTitle("酒店信息");
    QLinkedList<Hotel>::iterator iter;
    Hotel h;
    int flag = 0;//判断能否找到
    for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
    {
       if((*iter).GetHotelname() == ui->hotelNameInput->text())
       {
           h = (*iter);
           flag = 1;//能找到
           break;
       }
    }
    if(flag == 0)//若找不到 发出警告
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("该酒店名不存在！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
    plainTextEdit->setPlainText(QObject::tr("酒店名: ")+h.GetHotelname()+
                                QObject::tr("\n所在城市: ")+h.m_city+
                                QObject::tr("\n所在地区: ")+h.m_district+
                                QObject::tr("\n酒店电话: ")+h.m_hotelPhonenum+
                                QObject::tr("\n酒店评分: ")+QString::number(h.m_evaluation)+
                                QObject::tr("\n\n单人间总数: ")+QString::number(h.m_SingleRoom.m_roomNum)+
                                QObject::tr("\n单人间余数: ")+QString::number(h.m_SingleRoom.m_roomRestNum)+
                                QObject::tr("\n单人间定价: ")+QString::number(h.m_SingleRoom.m_fixedPrice)+
                                QObject::tr("\n单人间折扣: ")+QString::number(h.m_SingleRoom.m_discount)+
                                QObject::tr("\n单人间描述: ")+h.m_SingleRoom.m_description+
                                QObject::tr("\n\n双人间总数: ")+QString::number(h.m_DoubleRoom.m_roomNum)+
                                QObject::tr("\n双人间余数: ")+QString::number(h.m_DoubleRoom.m_roomRestNum)+
                                QObject::tr("\n双人间定价: ")+QString::number(h.m_DoubleRoom.m_fixedPrice)+
                                QObject::tr("\n双人间折扣: ")+QString::number(h.m_DoubleRoom.m_discount)+
                                QObject::tr("\n双人间描述: ")+h.m_DoubleRoom.m_description+
                                QObject::tr("\n\n三人间总数: ")+QString::number(h.m_TripleRoom.m_roomNum)+
                                QObject::tr("\n三人间余数: ")+QString::number(h.m_TripleRoom.m_roomRestNum)+
                                QObject::tr("\n三人间定价: ")+QString::number(h.m_TripleRoom.m_fixedPrice)+
                                QObject::tr("\n三人间折扣: ")+QString::number(h.m_TripleRoom.m_discount)+
                                QObject::tr("\n三人间描述: ")+h.m_TripleRoom.m_description+
                                QObject::tr("\n\n大床间总数: ")+QString::number(h.m_KingSizeRoom.m_roomNum)+
                                QObject::tr("\n大床间余数: ")+QString::number(h.m_KingSizeRoom.m_roomRestNum)+
                                QObject::tr("\n大床间定价: ")+QString::number(h.m_KingSizeRoom.m_fixedPrice)+
                                QObject::tr("\n大床间折扣: ")+QString::number(h.m_KingSizeRoom.m_discount)+
                                QObject::tr("\n大床间描述: ")+h.m_KingSizeRoom.m_description+
                                QObject::tr("\n\n套间总数: ")+QString::number(h.m_SuiteRoom.m_roomNum)+
                                QObject::tr("\n套床间余数: ")+QString::number(h.m_SuiteRoom.m_roomRestNum)+
                                QObject::tr("\n套床间定价: ")+QString::number(h.m_SuiteRoom.m_fixedPrice)+
                                QObject::tr("\n套床间折扣: ")+QString::number(h.m_SuiteRoom.m_discount)+
                                QObject::tr("\n套床间描述: ")+h.m_SuiteRoom.m_description);
    plainTextEdit->show();
    }
}

void HotelSearch::on_hotelAddressButton_clicked()
{
    //根据酒店地址创建一个结果集链表 再利用QTableWidget输出结果
    QList<Hotel> resultList;
    QLinkedList<Hotel>::iterator iter;
    int flag = 0;//判断能否找到
    if(ui->cityInput->text().isEmpty()&&ui->districtInput->text().isEmpty())//若无输入地址
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("请至少输入酒店所在城市！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        if(ui->districtInput->text().isEmpty())//若只输入城市
        {
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
            {
               if((*iter).m_city == ui->cityInput->text())
               {
                   resultList<<(*iter);
                   flag = 1;//至少找到了一个酒店
               }
            }
            if(flag == 1)
            {
                if(ui->listMethodBox->currentIndex() == 0)//按评分由高到低排序
                {
                    std::sort(resultList.begin(),resultList.end(),evaluationHighToLow);
                }
                else//按评分由低到高排序
                {
                    std::sort(resultList.begin(),resultList.end(),evaluationLowToHigh);
                }
                //打印结果集链表
                QTableWidget *tableWidget = new QTableWidget(resultList.size(),30);//设置行列数
                tableWidget->setWindowIcon(QIcon(":/myimages/icon/icon-Search.png"));//设置icon
                tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置无法编辑
                //设置水平、垂直滑动条
                tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                "QScrollBar::handle:hover{background:gray;}"
                "QScrollBar::sub-line{background:transparent;}"
                "QScrollBar::add-line{background:transparent;}");
                tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                "QScrollBar::handle:hover{background:gray;}"
                "QScrollBar::sub-line{background:transparent;}"
                "QScrollBar::add-line{background:transparent;}");
                tableWidget->verticalHeader()->setVisible(false);//隐藏列表头
                tableWidget->horizontalHeader()->setStretchLastSection(true);//打开自动填充
                tableWidget->setFrameShape(QFrame::NoFrame);
                tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置表头居中
                QFont font;//设置表头加粗
                font.setBold(true);
                tableWidget->horizontalHeader()->setFont(font);
                tableWidget->verticalHeader()->setFont(font);
                tableWidget->setAlternatingRowColors(true);//打开交替颜色
                tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(102,102,153);color: white;};}");//设置表头颜色
                //设置表格颜色
                tableWidget->setStyleSheet("alternate-background-color:rgb(204,204,204);background-color:rgb(255,255,255);selection-color:Black;selection-background-color:rgb(239,240,220);");
                tableWidget->setWindowTitle("搜索结果");//设置标题
                tableWidget->resize(1000, 800);//设置窗口大小
                 QStringList header;//设置表头
                 header<<"酒店名"<<"城市"<<"地区"<<"酒店电话"<<"评分"
                       <<"单人间剩余房间数"<<"单人间定价"<<"单人间折扣"<<"单人间价格"<<"单人间介绍"
                       <<"双人间剩余房间数"<<"双人间定价"<<"双人间折扣"<<"双人间价格"<<"双人间介绍"
                       <<"三人间剩余房间数"<<"三人间定价"<<"三人间折扣"<<"三人间价格"<<"三人间介绍"
                       <<"大床间剩余房间数"<<"大床间定价"<<"大床间折扣"<<"大床间价格"<<"大床间介绍"
                       <<"套间剩余房间数"<<"套间定价"<<"套间折扣"<<"套间价格"<<"套间介绍";
                 tableWidget->setHorizontalHeaderLabels(header);
                 tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                 QList<Hotel>::iterator iter1;
                 int i = 0;
                 for (iter1=resultList.begin();iter1!=resultList.end();iter1++)
                 {
                     tableWidget->setItem(i,0,new QTableWidgetItem((*iter1).GetHotelname()));
                     tableWidget->setItem(i,1,new QTableWidgetItem((*iter1).m_city));
                     tableWidget->setItem(i,2,new QTableWidgetItem((*iter1).m_district));
                     tableWidget->setItem(i,3,new QTableWidgetItem((*iter1).m_hotelPhonenum));
                     tableWidget->setItem(i,4,new QTableWidgetItem(QString::number((*iter1).m_evaluation)));
                     tableWidget->setItem(i,5,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,7,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_discount)));
                     tableWidget->setItem(i,8,new QTableWidgetItem(QString::number(((*iter1).m_SingleRoom.m_fixedPrice)*(1-(*iter1).m_SingleRoom.m_discount))));
                     tableWidget->setItem(i,9,new QTableWidgetItem((*iter1).m_SingleRoom.m_description));
                     tableWidget->setItem(i,10,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,11,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,12,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_discount)));
                     tableWidget->setItem(i,13,new QTableWidgetItem(QString::number(((*iter1).m_DoubleRoom.m_fixedPrice)*(1-(*iter1).m_DoubleRoom.m_discount))));
                     tableWidget->setItem(i,14,new QTableWidgetItem((*iter1).m_DoubleRoom.m_description));
                     tableWidget->setItem(i,15,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,16,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,17,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_discount)));
                     tableWidget->setItem(i,18,new QTableWidgetItem(QString::number(((*iter1).m_TripleRoom.m_fixedPrice)*(1-(*iter1).m_TripleRoom.m_discount))));
                     tableWidget->setItem(i,19,new QTableWidgetItem((*iter1).m_TripleRoom.m_description));
                     tableWidget->setItem(i,20,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_roomRestNum)));
                     tableWidget->setItem(i,21,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_fixedPrice)));
                     tableWidget->setItem(i,22,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_discount)));
                     tableWidget->setItem(i,23,new QTableWidgetItem(QString::number(((*iter1).m_KingSizeRoom.m_fixedPrice)*(1-(*iter1).m_KingSizeRoom.m_discount))));
                     tableWidget->setItem(i,24,new QTableWidgetItem((*iter1).m_KingSizeRoom.m_description));
                     tableWidget->setItem(i,25,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_roomRestNum)));
                     tableWidget->setItem(i,26,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_fixedPrice)));
                     tableWidget->setItem(i,27,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_discount)));
                     tableWidget->setItem(i,28,new QTableWidgetItem(QString::number(((*iter1).m_SuiteRoom.m_fixedPrice)*(1-(*iter1).m_SuiteRoom.m_discount))));
                     tableWidget->setItem(i,29,new QTableWidgetItem((*iter1).m_SuiteRoom.m_description));
                     i++;
                 }
                 tableWidget->show();
            }
            else//一个酒店都没有
            {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("该城市无酒店！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
            }
        }
        else if (ui->cityInput->text().isEmpty())//若只输入地区 弹出警告
        {
            QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("请输入城市名！"),QMessageBox::Ok,this);
            message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
            message.exec();
        }
        else//城市与地区都非空
        {
            for (iter=m_hotelList.begin();iter!=m_hotelList.end();iter++)
            {
               if((*iter).m_city == ui->cityInput->text()&&(*iter).m_district == ui->districtInput->text())
               {
                   resultList<<(*iter);
                   flag = 1;//至少找到了一个酒店
               }
            }
            if(flag == 1)
            {
                if(ui->listMethodBox->currentIndex() == 0)//按评分由高到低排序
                {
                    std::sort(resultList.begin(),resultList.end(),evaluationHighToLow);
                }
                else//按评分由低到高排序
                {
                    std::sort(resultList.begin(),resultList.end(),evaluationLowToHigh);
                }
                //打印结果集链表
                QTableWidget *tableWidget = new QTableWidget(resultList.size(),30);//设置行列数
                tableWidget->setWindowIcon(QIcon(":/myimages/icon/icon-Search.png"));//设置icon
                tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置无法编辑
                //设置水平、垂直滑动条
                tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
                "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                "QScrollBar::handle:hover{background:gray;}"
                "QScrollBar::sub-line{background:transparent;}"
                "QScrollBar::add-line{background:transparent;}");
                tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
                "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
                "QScrollBar::handle:hover{background:gray;}"
                "QScrollBar::sub-line{background:transparent;}"
                "QScrollBar::add-line{background:transparent;}");
                tableWidget->verticalHeader()->setVisible(false);//隐藏列表头
                tableWidget->horizontalHeader()->setStretchLastSection(true);//打开自动填充
                tableWidget->setFrameShape(QFrame::NoFrame);
                tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置表头居中
                QFont font;//设置表头加粗
                font.setBold(true);
                tableWidget->horizontalHeader()->setFont(font);
                tableWidget->verticalHeader()->setFont(font);
                tableWidget->setAlternatingRowColors(true);//打开交替颜色
                tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:rgb(102,102,153);color: white;};}");//设置表头颜色
                //设置表格颜色
                tableWidget->setStyleSheet("alternate-background-color:rgb(204,204,204);background-color:rgb(255,255,255);selection-color:Black;selection-background-color:rgb(239,240,220);");
                tableWidget->setWindowTitle("搜索结果");//设置标题
                tableWidget->resize(1000, 800);//设置窗口大小
                 QStringList header;//设置表头
                 header<<"酒店名"<<"城市"<<"地区"<<"酒店电话"<<"评分"
                       <<"单人间剩余房间数"<<"单人间定价"<<"单人间折扣"<<"单人间价格"<<"单人间介绍"
                       <<"双人间剩余房间数"<<"双人间定价"<<"双人间折扣"<<"双人间价格"<<"双人间介绍"
                       <<"三人间剩余房间数"<<"三人间定价"<<"三人间折扣"<<"三人间价格"<<"三人间介绍"
                       <<"大床间剩余房间数"<<"大床间定价"<<"大床间折扣"<<"大床间价格"<<"大床间介绍"
                       <<"套间剩余房间数"<<"套间定价"<<"套间折扣"<<"套间价格"<<"套间介绍";
                 tableWidget->setHorizontalHeaderLabels(header);
                 tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
                 QList<Hotel>::iterator iter1;
                 int i = 0;
                 for (iter1=resultList.begin();iter1!=resultList.end();iter1++)
                 {
                     tableWidget->setItem(i,0,new QTableWidgetItem((*iter1).GetHotelname()));
                     tableWidget->setItem(i,1,new QTableWidgetItem((*iter1).m_city));
                     tableWidget->setItem(i,2,new QTableWidgetItem((*iter1).m_district));
                     tableWidget->setItem(i,3,new QTableWidgetItem((*iter1).m_hotelPhonenum));
                     tableWidget->setItem(i,4,new QTableWidgetItem(QString::number((*iter1).m_evaluation)));
                     tableWidget->setItem(i,5,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,7,new QTableWidgetItem(QString::number((*iter1).m_SingleRoom.m_discount)));
                     tableWidget->setItem(i,8,new QTableWidgetItem(QString::number(((*iter1).m_SingleRoom.m_fixedPrice)*(1-(*iter1).m_SingleRoom.m_discount))));
                     tableWidget->setItem(i,9,new QTableWidgetItem((*iter1).m_SingleRoom.m_description));
                     tableWidget->setItem(i,10,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,11,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,12,new QTableWidgetItem(QString::number((*iter1).m_DoubleRoom.m_discount)));
                     tableWidget->setItem(i,13,new QTableWidgetItem(QString::number(((*iter1).m_DoubleRoom.m_fixedPrice)*(1-(*iter1).m_DoubleRoom.m_discount))));
                     tableWidget->setItem(i,14,new QTableWidgetItem((*iter1).m_DoubleRoom.m_description));
                     tableWidget->setItem(i,15,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_roomRestNum)));
                     tableWidget->setItem(i,16,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_fixedPrice)));
                     tableWidget->setItem(i,17,new QTableWidgetItem(QString::number((*iter1).m_TripleRoom.m_discount)));
                     tableWidget->setItem(i,18,new QTableWidgetItem(QString::number(((*iter1).m_TripleRoom.m_fixedPrice)*(1-(*iter1).m_TripleRoom.m_discount))));
                     tableWidget->setItem(i,19,new QTableWidgetItem((*iter1).m_TripleRoom.m_description));
                     tableWidget->setItem(i,20,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_roomRestNum)));
                     tableWidget->setItem(i,21,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_fixedPrice)));
                     tableWidget->setItem(i,22,new QTableWidgetItem(QString::number((*iter1).m_KingSizeRoom.m_discount)));
                     tableWidget->setItem(i,23,new QTableWidgetItem(QString::number(((*iter1).m_KingSizeRoom.m_fixedPrice)*(1-(*iter1).m_KingSizeRoom.m_discount))));
                     tableWidget->setItem(i,24,new QTableWidgetItem((*iter1).m_KingSizeRoom.m_description));
                     tableWidget->setItem(i,25,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_roomRestNum)));
                     tableWidget->setItem(i,26,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_fixedPrice)));
                     tableWidget->setItem(i,27,new QTableWidgetItem(QString::number((*iter1).m_SuiteRoom.m_discount)));
                     tableWidget->setItem(i,28,new QTableWidgetItem(QString::number(((*iter1).m_SuiteRoom.m_fixedPrice)*(1-(*iter1).m_SuiteRoom.m_discount))));
                     tableWidget->setItem(i,29,new QTableWidgetItem((*iter1).m_SuiteRoom.m_description));
                     i++;
                 }
                 tableWidget->show();
        }
        else//一个酒店都没有
        {
                QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("该城市该地区无酒店！"),QMessageBox::Ok,this);
                message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
                message.exec();
        }

      }
    }
}
