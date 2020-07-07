#include "mycoin.h"

//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
//实现构造函数
MyCoin::MyCoin(QString CoinImg){
    QPixmap pix;
    bool ret = pix.load(CoinImg);
    if(!ret){
        //加载失败
        QString str = QString("you can not load the %1").arg(CoinImg);
        QMessageBox::warning(this,"error",str);
        return;
    }
    //依次设置 按钮大小 按钮边框 图片 图片大小
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    this->min = 1;
    this->max = 8;
    //初始化 按钮是否执行动画标志
    this->isAnimation = false;    //默认全是没有在执行动画

    //初始化 是否胜利的标志
    this->isWin = false;
    //监听定时器事件1
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;  //从正面 翻到反面
        QString str = QString(":/resource/Coin000%1.png").arg(this->min++);
        pix.load(str);

        //依次设置 按钮大小 按钮边框 图片 图片大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到了最后一张图，就停止定时器
        if(this->min > this->max){
            this->min = 1;  //重置最小值
            timer1->stop();
            this->isAnimation = false;  //定时器停止 表明动画结束了 动画执行标志 同步为false
        }
    });

    //监听定时器事件2
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;  //从反面翻转到正面
        QString str = QString(":/resource/Coin000%1.png").arg(this->max--);
        pix.load(str);

        //依次设置 按钮大小 按钮边框 图片 图片大小
        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));

        //如果显示到了最后一张图，就停止定时器
        if(this->max < this->min){
            this->max = 8;  //重置最大值
            timer2->stop();
            this->isAnimation = false; //定时器停止 表明动画结束了 动画执行标志 同步为false
        }
    });
}


//改变标志 执行翻转效果
void MyCoin::changeFlag(){
    if(this->flag){//如果当前是正面
    //开启正面 翻 反面 的定时器
        timer1->start(30);
        this->flag = false;  //同步标志
        this->isAnimation = true; //同步 执行动画的标志

    }else{  //当前是反面
        //开启反面 翻 正面的定时器
        timer2->start(30);
        this->flag = true;  //同步标志
        this->isAnimation = true; //同步 执行动画的标志
    }
}

//鼠标按下事件重写  //程序的优化
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation | this->isWin){
        //如果正在做动画 或者已经胜利了 对这次鼠标按下事件 忽略
        return;
    }else{
        //交给父类去处理
        QPushButton::mousePressEvent(e);
    }
}
