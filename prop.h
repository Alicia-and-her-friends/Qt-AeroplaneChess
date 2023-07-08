#ifndef PROP_H
#define PROP_H

#include <QMainWindow>
#include "Game.h"
#include "path.h"
#include <iostream>
#include <cstring>
#include "mousehover.h"
#include "qrimage.h"

namespace Ui {
class prop;
}

class prop : public QMainWindow
{
    Q_OBJECT

public:
    Game* game;
    explicit prop(QWidget *parent = nullptr);
    prop(QWidget *parent, Game* game_);
    ~prop();

    QRImage *qr; //用以显示道具用法


    bool onTime;//中间变量


    bool SDN;//道具：设置骰子点数
    int diceNum;
    void SetDiceNum();

    bool SDT;//道具：设置剩余骰子次数
    int diceTime;
    void SetDiceTime();

    bool SU;//道具：加速
    void SpeedUp();

    bool SD;//道具：减速
    void SlowDown();

    bool MB;//道具：更改棋子方向
    void MoveBackward();

    bool BS;//道具：颜色托管
    void Babysit();

    bool SL;//道具：交换位置
    void SwapLoca();

    //暂时不考虑
    void Wave();




private slots:
    void buy();

    void Slot_of_SetDiceNum();
    void Slot_of_SetDiceTime();
    void Slot_of_SpeedUp();
    void Slot_of_SlowDown();
    void Slot_of_MoveBackward();
    void Slot_of_Babysit();
    void Slot_of_SwapLoca();
    void IniOnTime();
    void X();

    void buyBS();
    void buyBW();
    void buyDN();
    void buySD();
    void buySU();
    void buySWAP();
    void buyDT();

    void change_KD(int col,int dk, int dd);

    void slotChangeColorNow_(int x);
signals:
    void signOnTime(bool);
    void Y();
    void signal_showQR(QString);//解释道具用法

public slots:
    void slot_BtnObj(QObject*, QString);//鼠标悬浮

private:
    Ui::prop *ui;
public:
    void SendingOnTime();

};

#endif // PROP_H
