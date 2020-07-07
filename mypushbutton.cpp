#include "mypushbutton.h"
#include <QPropertyAnimation>
//构造函数
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    //保存  未按下时图片的显示路径 还有按下时的图片显示路径
    this->normalImagPath = normalImg;
    this->pressImgPath = pressImg;

    QPixmap pix;
    bool flag = pix.load(this->normalImagPath);     //把未按下时候的图片导入
    if(!flag){
        QString str = QString("%1 图片加载失败").arg(this->normalImagPath);
        qDebug()<<str;
        return;
    }

    //设定按钮大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则按钮的样式
    this->setStyleSheet("QPushButton{border:0px;}");  //这个字符串 打错一个字符 都没有效果
    //设置图片
    this->setIcon(pix);
    //设置图片大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}


//向下跳跃
void MyPushButton::Zoom1(){
    //定义一个动画
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(200);  //200ms
    //设置动态对象的起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

   //设置动画对象 结束位置  y坐标增加 就是往下跳跃
     animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

     //设置曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);  //就是向下跳的路线
     //调用执行动画的函数
     animation->start();
}

//向上跳跃
void MyPushButton::Zoom2(){
    //定义一个动画
    QPropertyAnimation* animation = new QPropertyAnimation(this,"geometry");

    //设定时间间隔
    animation->setDuration(200);  //200ms
    //设置动态对象的起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

   //设置动画对象 结束位置  y坐标增加 就是往下跳跃
     animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

     //设置曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);  //就是向下跳的路线
     //调用执行动画的函数
     animation->start();
}
//鼠标按下事件
void MyPushButton::mousePressEvent(QMouseEvent *e){
    //首先判断是否需要切换图片，也就是传进来的pressImg是否为空
    if(this->pressImgPath != ""){  //不为空才进行切换
        QPixmap pix;
       bool ret =  pix.load(this->pressImgPath);  //加载图片
       if(!ret){
           QMessageBox::warning(this,"error","can not load the picture!");
       }
       //加载图片之后，修改当前按钮的图片

       this->setFixedSize(pix.width(),pix.height());     //设定按钮大小
       this->setStyleSheet("QPushButton{border:0px;}");  //设置不规则按钮的样式
       this->setIcon(pix);   //设置按钮上面的图片
       this->setIconSize(QSize(pix.width(),pix.height()));   //设置图片大小
    }

    //其它的按钮事件 都交给父类来处理
    QPushButton::mousePressEvent(e);
}

//鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    //首先判断是否需要切换图片，也就是传进来的pressImg是否为空
    if(this->pressImgPath != ""){  //不为空才进行切换
        QPixmap pix;
       bool ret =  pix.load(this->normalImagPath);  //加载图片
       if(!ret){
           QMessageBox::warning(this,"error","can not load the picture!");
       }
       //加载图片之后，修改当前按钮的图片

       this->setFixedSize(pix.width(),pix.height());     //设定按钮大小
       this->setStyleSheet("QPushButton{border:0px;}");  //设置不规则按钮的样式
       this->setIcon(pix);   //设置按钮上面的图片
       this->setIconSize(QSize(pix.width(),pix.height()));   //设置图片大小
    }

    //其它的按钮事件 都交给父类来处理
    QPushButton::mouseReleaseEvent(e);
}
