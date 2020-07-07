#ifndef PLAYSCENSE_H
#define PLAYSCENSE_H

#include <QMainWindow>
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QLabel>
#include <mycoin.h>
#include <QPropertyAnimation>
#include "mycoin.h"
#include "dataconfig.h"
class PlayScense : public QMainWindow
{
    Q_OBJECT
public:
//    explicit PlayScense(QWidget *parent = 0);
     PlayScense(int index);  //构造函数


     //重写绘图事件 因为要添加背景图片
     void paintEvent(QPaintEvent *);

     //维护一个游戏二维数组  数组里面保存的信息是 当前位置是金币还是银币
     int gameArray[4][4];

     //金币按钮数组
     MyCoin* coinBtn[4][4];   //每个位置 存放此时的金币值
     //就是因为要翻动周围的印币，所以必须能够找到周围印币的具体信息 所以要把所有的印币 都存放到二维数组中 方便寻找

     //封装一个成员变量 表示当前游戏的关卡号
     int levelIndex;

     //游戏是否胜利的标准
     bool isWin;

signals:
    void chooseSenceBack();  //自定义信号
public slots:
};

#endif // PLAYSCENSE_H
