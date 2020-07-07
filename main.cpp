#include "mainsense.h"
#include <QApplication>
#include "dataconfig.h"
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainSense w;

    //测试如何读出dataConfig类里面的数据
//    dataConfig data;
//    //初始化当前游戏界面中的二维数组 gameArray
//    for(int i=0;i<4;i++){
//        for(int j=0;j<4;j++){
//         qDebug()<<data.mData[1][i][j];
//        }
//        qDebug()<<" ";
//    }
    w.show();

    return a.exec();
}
