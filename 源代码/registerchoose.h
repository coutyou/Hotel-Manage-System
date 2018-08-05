#ifndef REGISTERCHOOSE_H
#define REGISTERCHOOSE_H

#include <QDialog>

namespace Ui {
class registerChoose;
}

class registerChoose : public QDialog
{
    Q_OBJECT

public:
    explicit registerChoose(QWidget *parent = 0);
    ~registerChoose();

private:
    Ui::registerChoose *ui;
};

#endif // REGISTERCHOOSE_H
