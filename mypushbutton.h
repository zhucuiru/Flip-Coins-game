#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <QIcon>
#include <QMessageBox>
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyPushButton(QWidget *parent = 0);
    MyPushButton(QString normalImg ,QString pressImg = "");  //为了让我们自定义设计的按钮有按下之后有弹起的效果
    //其实就是按下前后，使用的是2个图片

    QString normalImagPath; //未按下时显示的图片路径
    QString pressImgPath;   //按下后显示的图片路径

    //向下跳跃
    void Zoom1();
    //向上跳跃
    void Zoom2();

    //鼠标按下事件
    void mousePressEvent(QMouseEvent *e);
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);

signals:


public slots:
};

#endif // MYPUSHBUTTON_H
