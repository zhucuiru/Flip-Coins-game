#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QPixmap>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = 0);

    //自定义构造函数 根据传进来的图片路径不同，确定当前按钮显示的图片是金币 还是银币
    MyCoin(QString);

    //当前游戏币的坐标信息
    int posX;
    int posY;
    bool flag;//金币或者是银币的标志

    void changeFlag();      //改变标志，执行翻转效果
    QTimer* timer1;  //正面翻转到反面的定时器
    QTimer* timer2;  //反面翻转到正面的定时器
    int min;  //最小图片
    int max;  //最大图片

    //创建是否执行动画标志
    bool isAnimation;

    //创建 当前是否胜利的标志
    bool isWin;

    //为什么要设置一个 是否执行动画的标志 因为当动画正在执行的时候，再次按下按键，会影响上一个动画的执行效果
    //一般我们都会选择在动画执行结束之后，再执行下一个动画 因此我们需要在按键按下的时候，判断一下当前是否在执行动画的过程中，如果正在执行动画，那么这个按钮按下的事件，就忽略掉

    //鼠标按下事件重写
    void mousePressEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYCOIN_H
