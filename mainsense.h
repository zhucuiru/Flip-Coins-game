#ifndef MAINSENSE_H
#define MAINSENSE_H

#include <QMainWindow>
#include <QTimer>
#include "mypushbutton.h"
#include "chooselevelsence.h"
namespace Ui {
class MainSense;
}

class MainSense : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainSense(QWidget *parent = 0);
    ~MainSense();
    //绘图事件
    void paintEvent(QPaintEvent*);

    //维护一个 指向下一个选择关卡场景的指针
    ChooseLevelSence* chooseScense;

    void slots1();

private:
    Ui::MainSense *ui;
};

#endif // MAINSENSE_H
