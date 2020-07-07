#ifndef CHOOSELEVELSENCE_H
#define CHOOSELEVELSENCE_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include "mypushbutton.h"
#include "playscense.h"
class ChooseLevelSence : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelSence(QWidget *parent = 0);

    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //维护一个 游戏场景的指针
    PlayScense* playScense;

signals:
    //自定义的信号 一旦按键按下，就给主场景发送一个按下back按钮的信号
    void chooseSenceBack();// 自定义信号 只需要声明，不需要实现
public slots:       //因为我自己写的槽函数嵌套槽函数 用lambda表达式 出现问题 所以还是用槽函数实现
    void ReceiveBackSlots1();  //收到下一个界面发送的返回信号的槽函数
    void DelaySlots();      //延时发送返回信号的槽函数

    //
};

#endif // CHOOSELEVELSENCE_H
