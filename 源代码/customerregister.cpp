#include "customerregister.h"
#include "ui_customerregister.h"

customerRegister::customerRegister(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customerRegister)
{
    ui->setupUi(this);
}

customerRegister::~customerRegister()
{
    delete ui;
}
