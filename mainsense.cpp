#include "mainsense.h"
#include "ui_mainsense.h"
#include <QPainter>
#include <QPaintEvent>

MainSense::MainSense(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainSense)
{
    ui->setupUi(this);
    //点击  开始--退出 就会退出程序
    connect(ui->actionQuit,&QAction::triggered,this,[=](){
       this->close();
    });

    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    this->setWindowTitle(QStringLiteral("翻金币游戏"));
    //设置标题图片
    this->setWindowIcon(QIcon(":/resource/Coin0001.png"));
    //添加背景图片，可以通过往QLabel中添加图片，也可以利用绘图事件

    //封装好开始按钮之后 就可以创建 开始按钮
    MyPushButton* startBtn = new MyPushButton(":/resource/MenuSceneStartButton.png");
    startBtn->setParent(this);  //设置父亲
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);     //设置这个按钮的位置

    //创建出 选择关卡的场景
    chooseScense = new ChooseLevelSence;
    //只要有关卡场景，我们就开始监听是否按下返回按钮
    connect(chooseScense,&ChooseLevelSence::chooseSenceBack,this,[=](){
       //一旦接收到返回按钮按下 就 隐藏关卡场景  并且显示主界面场景
        chooseScense->hide();
        this->show();
    });

    //开始按钮的槽函数实现
    connect(startBtn,&MyPushButton::clicked,this,[=](){
//        qDebug()<<"press start button!";
        //点击开始按钮，执行弹跳效果
        startBtn->Zoom1();  //向下
        startBtn->Zoom2();  //向上

        //为了避免动画闪的太快，对动画显示完之后进行延时  延时进入到第二个场景
        QTimer::singleShot(500,this,&MainSense::slots1);
    });

}


//绘图事件
void MainSense::paintEvent(QPaintEvent*){
      QPainter painter(this);
      QPixmap pix;
      //画背景图片
      pix.load(":/resource/PlayLevelSceneBg.png");
      painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据当前的宽和高 对图片进行拉升

      //画标题图片
      pix.load(":/resource/Title.png");
      pix = pix.scaled(pix.width()*0.5,pix.height()*0.5); //对这个pix图进行缩小
      painter.drawPixmap(10,30,pix);
  }

//槽函数的实现
void MainSense::slots1(){
    //隐藏当前主界面
    this->hide();
    //显示下一个选择关卡界面
    chooseScense->show();
}

MainSense::~MainSense()
{
    delete ui;
}
