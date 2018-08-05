#include "roomsearch.h"
#include "ui_roomsearch.h"
#include <QMessageBox>
#include <QTableWidget>
#include <QScrollBar>

bool priceHighToLow(const Room room1,const Room room2)//为排序写的比较函数
{
    return (1-room1.m_discount)*room1.m_fixedPrice > (1-room2.m_discount)*room2.m_fixedPrice;
}

bool priceLowToHigh(const Room room1,const Room room2)//为排序写的比较函数
{
    return (1-room1.m_discount)*room1.m_fixedPrice < (1-room2.m_discount)*room2.m_fixedPrice;
}

bool discountHighToLow(const Room room1,const Room room2)//为排序写的比较函数
{
    return room1.m_discount > room2.m_discount;
}

bool discountLowToHigh(const Room room1,const Room room2)//为排序写的比较函数
{
    return room1.m_discount < room2.m_discount;
}

bool roomRestNumHighToLow(const Room room1,const Room room2)//为排序写的比较函数
{
    return room1.m_roomRestNum > room2.m_roomRestNum;
}

bool roomRestNumLowToHigh(const Room room1,const Room room2)//为排序写的比较函数
{
    return room1.m_roomRestNum < room2.m_roomRestNum;
}

RoomSearch::RoomSearch(QLinkedList<Room> &roomList,QWidget *parent) :
    QDialog(parent),m_roomList(roomList),
    ui(new Ui::RoomSearch)
{
    ui->setupUi(this);
}

RoomSearch::~RoomSearch()
{
    delete ui;
}

void RoomSearch::on_searchButton_clicked()
{
    QList<Room> resultList;
    QLinkedList<Room>::iterator iter;
    switch (ui->roomTypeBox->currentIndex())//识别房型
    {
    case 0:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            resultList<<(*iter);
        }
        break;
    case 1:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            if((*iter).GetRoomType() == "SingleRoom")
            {
                resultList<<(*iter);
            }
        }
        break;
    case 2:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            if((*iter).GetRoomType() == "DoubleRoom")
            {
                resultList<<(*iter);
            }

        }
        break;
    case 3:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            if((*iter).GetRoomType() == "TripleRoom")
            {
                resultList<<(*iter);
            }
        }
        break;
    case 4:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            if((*iter).GetRoomType() == "KingSizeRoom")
            {
                resultList<<(*iter);
            }
        }
        break;
    case 5:
        for (iter=m_roomList.begin();iter!=m_roomList.end();iter++)
        {
            if((*iter).GetRoomType() == "SuiteRoom")
            {
                resultList<<(*iter);
            }
        }
        break;
    default:
        break;
    }
    switch (ui->listMethodBox->currentIndex())//识别排序方法
    {
    case 0:
        std::sort(resultList.begin(),resultList.end(),priceHighToLow);
        break;
    case 1:
        std::sort(resultList.begin(),resultList.end(),priceLowToHigh);
        break;
    case 2:
        std::sort(resultList.begin(),resultList.end(),discountHighToLow);
        break;
    case 3:
        std::sort(resultList.begin(),resultList.end(),discountLowToHigh);
        break;
    case 4:
        std::sort(resultList.begin(),resultList.end(),roomRestNumHighToLow);
        break;
    case 5:
        std::sort(resultList.begin(),resultList.end(),roomRestNumLowToHigh);
        break;
    default:
        break;
    }
    if(resultList.size() == 0)//若结果集为空
    {
        QMessageBox message(QMessageBox::Warning,QObject::tr("警告！"),QObject::tr("无符合条件客房！"),QMessageBox::Ok,this);
        message.setWindowIcon(QIcon(":/myimages/icon/warning-circle.png"));
        message.exec();
    }
    else
    {
        //在表格中输出数据
        QTableWidget *tableWidget = new QTableWidget(resultList.size(),8);//设置行列数
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
        header<<"酒店名"<<"客房类型"<<"客房描述"<<"客房定价"<<"客房折扣"<<"客房价格"<<"客房总数"<<"客房余数";
        tableWidget->setHorizontalHeaderLabels(header);
        QList<Room>::iterator iter1;
        int i = 0;
        for (iter1=resultList.begin();iter1!=resultList.end();iter1++)
        {
             tableWidget->setItem(i,0,new QTableWidgetItem((*iter1).GetHotelname()));
             tableWidget->setItem(i,1,new QTableWidgetItem((*iter1).GetRoomType()));
             tableWidget->setItem(i,2,new QTableWidgetItem((*iter1).m_description));
             tableWidget->setItem(i,3,new QTableWidgetItem(QString::number((*iter1).m_fixedPrice)));
             tableWidget->setItem(i,4,new QTableWidgetItem(QString::number((*iter1).m_discount)));
             tableWidget->setItem(i,5,new QTableWidgetItem(QString::number((1-(*iter1).m_discount)*(*iter1).m_fixedPrice)));
             tableWidget->setItem(i,6,new QTableWidgetItem(QString::number((*iter1).m_roomNum)));
             tableWidget->setItem(i,7,new QTableWidgetItem(QString::number((*iter1).m_roomRestNum)));
             i++;
        }
        tableWidget->show();
    }
}
