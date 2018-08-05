#ifndef CUSTOMERREGISTER_H
#define CUSTOMERREGISTER_H

#include <QDialog>

namespace Ui {
class customerRegister;
}

class customerRegister : public QDialog
{
    Q_OBJECT

public:
    explicit customerRegister(QWidget *parent = 0);
    ~customerRegister();

private:
    Ui::customerRegister *ui;
};

#endif // CUSTOMERREGISTER_H
