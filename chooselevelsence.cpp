#include "chooselevelsence.h"


ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle(QStringLiteral("选择关卡"));
    //设置标题图片
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));


    //用代码创建菜单栏
    QMenuBar* Bar = new QMenuBar();
    this->setMenuBar(Bar);
    //创建开始菜单
    QMenu* startMenu = new QMenu(QStringLiteral("开始"));
    Bar->addMenu(startMenu);
    //创建 开始菜单 下面的菜单项 退出菜单项
    QAction* quitAction = startMenu->addAction(QStringLiteral("退出"));
    //点击退出按钮 实现退出游戏
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });

    //返回按钮创建  利用之前封装好的MyPushButton类实现
    MyPushButton* backBtn = new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    //这里创建的时候，需要填入2个参数，一个是未选中时候的图片，一个是选中后的图片
    backBtn->setParent(this); //设置父亲
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());  //设置位置
    connect(backBtn,&MyPushButton::clicked,this,&ChooseLevelSence::DelaySlots);

    //游戏场景指针 一开始置为空
    playScense = NULL;


    //选择关卡按钮  20个按钮
    for(int i=0;i<20;i++){
        MyPushButton * menuBtn = new MyPushButton(":/resource/LevelIcon.png");  //定义一个关卡按钮
        menuBtn->setParent(this);
        menuBtn->move(25+(i%4)*70,130+(i/4)*70);  //一个循环 就可以写出一个矩阵
        //每个按钮 都会有一个信号与槽函数的实现
        connect(menuBtn,&MyPushButton::clicked,this,[=](){
//            QString str = QString("you choosed %1 level game").arg(i+1);
//            qDebug()<<str;
            //先隐藏自身
            this->hide();
            //进入到具体的游戏场景中
            playScense = new PlayScense(i+1);       //告诉代码 我现在生成的是 第几关的游戏场景
            playScense->show(); //显示出来这个新建的游戏场景

            //监听playScense是否发送返回信号 一旦发送返回信号，就执行 返回槽函数
            connect(playScense,&PlayScense::chooseSenceBack,this,&ChooseLevelSence::ReceiveBackSlots1);
        });

        QLabel* label = new QLabel(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());    //设置标签的大小
        label->setText(QString::number(i+1));       //设置label的文本

        //为了让label的文本能够显示在menuBtn上面，我们可以把它们的位置重叠
        label->move(25+(i%4)*70,130+(i/4)*70);
        label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置文本处于水平和垂直都居中

        //当按钮上面覆盖了一个label控件后，点击按钮，鼠标事件并不会发生，被label拦截了，我们需要设置鼠标的穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);      //对当前label设置鼠标事件的穿透  51
    }



}

//重写绘图事件
void ChooseLevelSence::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    //画背景图片
    pix.load(":/resource/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据当前的宽和高 对图片进行拉升

    //画标题图片
    pix.load(":/resource/Title.png");
    //这里没有对标题进行缩小
//    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5); //对这个pix图进行缩小
    painter.drawPixmap(10,30,pix);
}

//收到下一个界面发送的返回信号的槽函数
 void ChooseLevelSence::ReceiveBackSlots1(){   //lambda表达式写的槽函数 如果里面再嵌套一个lambda写的槽函数，对于this指针的成员变量都会出错
    //一旦接收到返回按钮按下 就 隐藏当前的游戏场景界面
    playScense->close();
    delete playScense;
    playScense = NULL;
    this->show();       //显示出选择关卡界面
 }


void ChooseLevelSence::DelaySlots(){    //延时发送返回信号的槽函数
    QTimer::singleShot(500,this,[=](){
       emit this->chooseSenceBack();
    });
}

