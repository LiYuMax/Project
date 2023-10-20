#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event)override;
public:
    QPixmap image;
    QPixmap scaledPixmap ;
signals:
};

#endif // MYWIDGET_H
