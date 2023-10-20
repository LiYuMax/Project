#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent)
    : QWidget{parent}
{
    //设置图片
    image.load(":/greatWall.jpg");
}
//绘图
void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter myPainter(this);
    myPainter.drawPixmap(0,0,image);
}
