#include "playscense.h"
#include <QtAlgorithms>
#include <QMap>
#include <QVector>
//PlayScense::PlayScense(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScense::PlayScense(int index){  //有参构造函数
    //    QString str = QString("you choosed %1 level game").arg(index);
    //    qDebug()<<str;

    //保存本关 关卡号
    this->levelIndex = index;

    //设置固定大小
    this->setFixedSize(320,588);
    //设置标题
    QString str =QString(QStringLiteral("level:%1 ")).arg(this->levelIndex);
    this->setWindowTitle(str);
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
    //点击退出菜单 实现退出游戏
    connect(quitAction,&QAction::triggered,this,[=](){
        this->close();
    });

    //添加返回按钮
    MyPushButton* backBtn = new MyPushButton(":/resource/BackButton.png",":/resource/BackButtonSelected.png");
    //这里创建的时候，需要填入2个参数，一个是未选中时候的图片，一个是选中后的图片
    backBtn->setParent(this); //设置父亲
    backBtn->move(this->width() - backBtn->width(),this->height()-backBtn->height());  //设置位置
    connect(backBtn,&MyPushButton::clicked,this,[=](){
        emit this->chooseSenceBack();       //发送返回信号
    });

    //在左下角显示具体的关卡号
    QLabel* label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("");
    font.setPointSize(20);  //定义一种字体类型
    label->setFont(font);   //让这个label控件 使用这种字体
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,120,50));  //设置位置

    //默认未胜利
    this->isWin = false;

    dataConfig data;  //定义初始所有的关卡信息
    //初始化当前游戏界面中的二维数组 gameArray
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            this->gameArray[i][j] = data.mData[this->levelIndex][i][j];
        }
    }

    //创建胜利的图片
    QLabel* winLabel = new QLabel;
    QPixmap pix;
    pix.load(":/resource/LevelCompletedDialogBg.png");
    winLabel->setGeometry(QRect(0,0,pix.width(),pix.height()));
    winLabel->setParent(this);
    winLabel->setPixmap(pix);
    winLabel->move((this->width()-pix.width())*0.5,-pix.height());  //最开始的时候，把图片放在当前界面看不到的位置
    //创建每一个金币的背景图片  二层循环
    for(int i = 0;i<4;i++){
        for(int j=0;j<4;j++){
            //QLabel显示图片
            QLabel* bg = new QLabel(this);    //在标签上 画图
            QPixmap pix;
            pix.load(":/resource/BoardNode.png");
            bg->setGeometry(0,0,pix.width(),pix.height());//设置标签的大小 和标签上面要画的图片大小一致
            bg->setPixmap(pix);  //在label上面画图
            bg->move(57+i*50,200+j*50); //设置位置

            //创建金币矩阵
            //根据gameArray这个数组 判断当前应该放金币 还是银币
            QString str;
            if(this->gameArray[i][j] == 1){
                str = ":/resource/Coin0001.png";
            }else{
                str = ":/resource/Coin0008.png";
            }
            MyCoin* coin = new MyCoin(str);

            //在创建币对象的时候 就初始化它的坐标信息
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j]; //记录当前币的正反标志
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);  //在对应的位置放上对应的金币类型
            //在相应位置 创建完金币值之后，就要把它放到金币二维数组中
            coinBtn[i][j] = coin;

            //监听这个币是否被按下
            connect(coin,&MyCoin::clicked,this,[=](){
                coin->changeFlag();  //修改当前标志
                this->gameArray[i][j] = this->gameArray[i][j]==0 ? 1 : 0;  //同步一下二维数组中的值

                //在改变完自己的状态之后 改变它周围的金币的状态  延时翻动周围的印币
                QTimer::singleShot(300,this,[=](){
                    //翻当前印币右侧的位置
                    if(coin->posX +1 <=3){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();        //检测 并且翻转右侧的印币
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY]==0 ? 1 : 0;  //同步一下状态 二维数组中的值
                    }
                    //检测左侧印币
                    if(coin->posX-1 >=0){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();        //检测 并且翻转左侧的印币
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY]==0 ? 1 : 0;  //同步一下状态 二维数组中的值
                    }
                    //检测上侧印币
                    if(coin->posY-1 >=0){
                        coinBtn[coin->posX][coin->posY-1 ]->changeFlag();        //检测 并且翻转上侧的印币
                        this->gameArray[coin->posX][coin->posY-1 ] = this->gameArray[coin->posX][coin->posY-1]==0 ? 1 : 0;  //同步一下状态 二维数组中的值
                    }

                    //检测下侧 印币
                    if(coin->posY+1 <=3){
                        coinBtn[coin->posX][coin->posY+1 ]->changeFlag();        //检测 并且翻转下侧的印币
                        this->gameArray[coin->posX][coin->posY+1 ] = this->gameArray[coin->posX][coin->posY+1]==0 ? 1 : 0;  //同步一下状态 二维数组中的值
                    }

                    //在执行完一次彻底的翻转之后，我们要检查一下 是否全部都是金币 如果是，那么游戏就胜利了，否则还没有
                    this->isWin = true;
                    for(int i = 0;i<4;i++){
                        for(int j=0;j<4;j++){
                            if(coinBtn[i][j]->flag == false){ //一旦有一个硬币 不是金币 那就没有胜利，置为假
                                this->isWin = false;
                                break;  //退出考察的循环
                            }
                        }
                    }
                    if(this->isWin == true){
//                        qDebug()<<"游戏胜利！";    //如果结束判断之后，还是胜利的标志 那么就是胜利， 就可以显示胜利的图标还有音乐
                        //将所有硬币的胜利标志 都设置为true
                        for(int i = 0;i<4;i++){
                            for(int j=0;j<4;j++){
                                coinBtn[i][j]->isWin = true;
                                }
                            }

                        //将胜利的图片 利用动画 展示出来
                        QPropertyAnimation* animation = new QPropertyAnimation(winLabel,"geometry");   //winLabel是执行动画的主体
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                });

            });
        }
    }
}


//重写绘图事件 因为要添加背景图片
void PlayScense::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    //画背景图片
    pix.load(":/resource/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);  //根据当前的宽和高 对图片进行拉升

    //画标题图片
    pix.load(":/resource/Title.png");
    //这里没有对标题进行缩小
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5); //对这个pix图进行缩小
    painter.drawPixmap(10,30,pix);
}
