#include "registerchoose.h"
#include "ui_registerchoose.h"

registerChoose::registerChoose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerChoose)
{
    ui->setupUi(this);
}

registerChoose::~registerChoose()
{
    delete ui;
}
