#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

/****************************README************************************/
/***********************程序启动时展示图片********************************/
/****************************END***************************************/


#include <QDialog>

namespace Ui {
class ShowImage;
}

class ShowImage : public QDialog
{
    Q_OBJECT

public:
    explicit ShowImage(QWidget *parent = 0);
    ~ShowImage();

private slots:
    void CloseAndOpen();

private:
    Ui::ShowImage *ui;
};

#endif // SHOWIMAGE_H
