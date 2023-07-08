#include "qrimage.h"
#include "ui_qrimage.h"
#include <QDebug>
#include <iostream>

QRImage::QRImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QRImage)
{
    ui->setupUi(this);
    //setWindowFlags(Qt::FramelessWindowHint);//无边框
}

QRImage::~QRImage()
{
    delete ui;
}

void QRImage::slots_showQR(QString mes)
{
    std::cerr<<"in\n";
    std::cerr<<mes.toStdString()<<"\n";
    if (mes == "quit")
        this->hide();
    else if (mes == "SetDiceNum"){
        //this->move(250, 140);
        //this->show();
        this->resize(250, 39);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以选择预设点数掷骰子，而不是随机点数。");
        //ui->label->raise();
    }
    else if (mes == "Wave"){
        //this->move(250, 220);
        this->resize(300, 78);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以释放冲击波，"
                           "将一定距离内的所有对手的棋子击退到其起点。");
    }
    else if (mes == "SpeedUp"){
        //this->move(250, 300);
        this->resize(160, 39);
        ui->label->setText("使用后，玩家移动距离增加两倍。");
    }
    else if (mes == "SlowDown"){
        //this->move(250, 380);
        this->resize(160, 39);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，玩家移动距离减半取整。");
    }
    else if (mes == "MoveBackward"){
        //this->move(250, 460);
        this->resize(140, 39);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，玩家可以反向移动。");
    }
    else if (mes == "Babysit"){
        //this->move(250, 540);
        this->resize(300, 78);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以将自己的棋子交给指定玩家控制。"
                           "（点击对应颜色棋子即可）");
    }

    else if (mes == "SwapLoca"){
        //this->move(250, 620);
        this->resize(300, 78);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以与指定棋子交换位置。"
                           "（点击需要交换的两个棋子即可）");
    }
    else if (mes == "Explosion"){
        //this->move(250, 700);
        this->resize(200, 39);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以选择一个对手一起返回自己的起点。");
    }
    else if (mes == "SetDiceTime"){
        //this->move(250, 780);
        this->resize(190, 39);
        ui->label->setWordWrap(true);
        ui->label->setText("使用后，可以增加或减少掷骰子的次数。");
    }
}

