#include "prop.h"
#include "ui_prop.h"
#include "structures.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <cstring>
#include <QBitmap>
#include <QMainWindow>
#include "path.h"

prop::prop(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prop)
{
    ui->setupUi(this);
}
/*
        std::string temp_file=path_+"/greenPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
*/
prop::prop(QWidget *parent, Game* game_) :
    QMainWindow(parent),
    game(game_),
    ui(new Ui::prop)
{

    ui->setupUi(this);
    this->resize(400,794);
    this->setStyleSheet("background-color: rgb(203, 185, 173);");
    ui->Baby_Tleft->display(5);
    //std::cerr<<ui->Baby_Tleft->value();
    std::string path_=Upath::file_path_;
    std::string temp_file=path_+"/Pay.JPG";
    const char* c=temp_file.c_str();
    QPixmap pixmap(c);

    /*下面这一段！！*/
    qr = new QRImage(this);
    qr->hide();
    qr->setStyleSheet("background-color: rgb(200, 204, 215);");
    connect(this, &prop::signal_showQR, qr, &QRImage::slots_showQR);
    mouseHover *mmHover = new mouseHover();
    connect(mmHover, &mouseHover::signal_sendBtnObj, this, &prop::slot_BtnObj);
    ui->Babysit->installEventFilter(mmHover);
    ui->SetDiceNum->installEventFilter(mmHover);
    ui->SetDiceTime->installEventFilter(mmHover);
    ui->SlowDown->installEventFilter(mmHover);
    ui->MoveBackward->installEventFilter(mmHover);
    ui->SwapLoca->installEventFilter(mmHover);
    ui->SpeedUp->installEventFilter(mmHover);
    ui->Explosion->installEventFilter(mmHover);
    ui->Wave->installEventFilter(mmHover);


    //QPixmap pixmap("/Users/vincentarak/QTs/Sources/Pay.JPG");
    ui->Pay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->Pay->setPixmap(pixmap);
    ui->Pay->setScaledContents(true);

    std::string cc="";
    cc=path_+"/green.png";
    QPixmap xx(cc.c_str());
    ui->color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->color_now->setPixmap(xx);
    ui->color_now->setScaledContents(true);
    ui->color_now->raise();

    connect(game,SIGNAL(buy()),this,SLOT(buy()));

    connect(ui->Babysit,SIGNAL(clicked(bool)),this,SLOT(Slot_of_Babysit()));
    connect(ui->SetDiceNum,SIGNAL(clicked(bool)),this,SLOT(Slot_of_SetDiceNum()));
    connect(ui->SetDiceTime,SIGNAL(clicked(bool)),this,SLOT(Slot_of_SetDiceTime()));
    connect(ui->SlowDown,SIGNAL(clicked(bool)),this,SLOT(Slot_of_SlowDown()));
    connect(ui->MoveBackward,SIGNAL(clicked(bool)),this,SLOT(Slot_of_MoveBackward()));
    connect(ui->SwapLoca,SIGNAL(clicked(bool)),this,SLOT(Slot_of_SwapLoca()));
    connect(ui->SpeedUp,SIGNAL(clicked(bool)),this,SLOT(Slot_of_SpeedUp()));
    /*
    void buyBS();
    void buyBW();
    void buyDN();
    void buySD();
    void buySU();
    void buySWAP();
    void buyDT();
    */
    connect(ui->buyBS,SIGNAL(clicked(bool)),this,SLOT(buyBS()));
    connect(ui->buyDN,SIGNAL(clicked(bool)),this,SLOT(buyDN()));
    connect(ui->buyDT,SIGNAL(clicked(bool)),this,SLOT(buyDT()));
    connect(ui->buySD,SIGNAL(clicked(bool)),this,SLOT(buySD()));
    connect(ui->buyBW,SIGNAL(clicked(bool)),this,SLOT(buyBW()));
    connect(ui->buySWAP,SIGNAL(clicked(bool)),this,SLOT(buySWAP()));
    connect(ui->buySU,SIGNAL(clicked(bool)),this,SLOT(buySU()));

    connect(this,SIGNAL(signOnTime(bool)),game,SLOT(ChangeOnTime(bool)));
    connect(game,SIGNAL(Finish_changeOnTime()),this,SLOT(IniOnTime()));
    connect(ui->cheatButton,SIGNAL(clicked(bool)),game,SLOT(EmitBuy()));

    connect(game,SIGNAL(change_kd(int,int,int)),this,SLOT(change_KD(int,int,int)));

    connect(this,SIGNAL(Y()),this,SLOT(X()));

    connect(game,SIGNAL(signal_color_now(int)),this,SLOT(slotChangeColorNow_(int)));
}
/*这个函数！！*/
void prop::slot_BtnObj(QObject *objm, QString objName)
{
    if(objName == "mouse out"){
        emit signal_showQR("quit");
    }
    else{
        if(objName == ui->Babysit->objectName()){
            qr->move(250, 500);
            qr->show();
            emit signal_showQR("Babysit");
        }
        if(objName == ui->SetDiceNum->objectName()){
            qr->move(250, 100);
            qr->show();
            emit signal_showQR("SetDiceNum");
        }
        if(objName == ui->SetDiceTime->objectName()){
            qr->move(250, 740);
            qr->show();
            emit signal_showQR("SetDiceTime");
        }
        if(objName == ui->SlowDown->objectName()){
            qr->move(250, 340);
            qr->show();
            emit signal_showQR("SlowDown");
        }
        if(objName == ui->SpeedUp->objectName()){
            qr->move(250, 260);
            qr->show();
            emit signal_showQR("SpeedUp");
        }
        if(objName == ui->SwapLoca->objectName()){
            qr->move(250, 580);
            qr->show();
            emit signal_showQR("SwapLoca");
        }
        if(objName == ui->Explosion->objectName()){
            qr->move(250, 660);
            qr->show();
            emit signal_showQR("Explosion");
        }
        if(objName == ui->Wave->objectName()){
            qr->move(250, 180);
            qr->show();
            emit signal_showQR("Wave");
        }
        if(objName == ui->MoveBackward->objectName()){
            qr->move(250, 420);
            qr->show();
            emit signal_showQR("MoveBackward");
        }
    }
}


void prop::SendingOnTime(){
    emit signOnTime(onTime);
}

void prop::buy(){
    int k=0;
    k=ui->money_left->value();
    ui->money_left->display(k+1);
    if(k>=0x208-1||k>51){emit Y();}
    /*
    k=ui->Baby_Tleft->value();
    ui->Baby_Tleft->display(k+1);

    k=ui->SetDN_Tleft->value();
    ui->SetDN_Tleft->display(k+1);

    k=ui->SetDT_Tleft->value();
    ui->SetDT_Tleft->display(k+1);

    k=ui->Slow_Tleft->value();
    ui->Slow_Tleft->display(k+1);

    k=ui->Swap_Tleft->value();
    ui->Swap_Tleft->display(k+1);

    k=ui->Speed_Tleft->value();
    ui->Speed_Tleft->display(k+1);
    k=ui->Back_Tleft->value();
    ui->Back_Tleft->display(k+1);
    */
}
void prop::IniOnTime(){
    onTime=false;
}
/*
        0,1 骰子（0），飞机回合（1）
        2 预设骰子点数（按一次就行）
        3 改变骰子投掷次数（按一次就行）
        4 减速器（后继还需要按一个飞机）
        5 反向移动（后继还需要按一个飞机）
        6 加速器（后继还需要按一个飞机）
        7 交换位置（后续需要按两个飞机）
        8 颜色托管（后续还需要选一个颜色）//可以通过选飞机来实现
*/


void prop::Slot_of_SetDiceNum(){//2
    if(ui->SetDN_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(2)==false){
        return;
    }
    //以上是劝退环节
    game->legal_dice_num_now=ui->SetDN_spinBox->value();

    game->round^=1;
    game->signal_state.change_current_round();
    int k=ui->SetDN_Tleft->value();
    ui->SetDN_Tleft->display(k-1);

}
void prop::Slot_of_SetDiceTime(){//3
    if(ui->SetDT_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(3)==false){
        return;
    }
    //以上是劝退环节
    game->dice_time_remain=ui->SetDT_spinBox->value();
    int k=ui->SetDT_Tleft->value();
    ui->SetDT_Tleft->display(k-1);

}
void prop::Slot_of_SlowDown(){//4
    if(ui->Slow_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(4)==false){
        return;
    }
    //以上是劝退环节
    node state0=game->signal_state;
    state0.changeState(4);
    game->signal_state=state0;
    int k=ui->Slow_Tleft->value();
    ui->Slow_Tleft->display(k-1);

}
void prop::Slot_of_MoveBackward(){//5
    if(ui->Back_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(5)==false){
        return;
    }
    //以上是劝退环节
    node state0=game->signal_state;
    state0.changeState(5);
    game->signal_state=state0;
    int k=ui->Back_Tleft->value();
    ui->Back_Tleft->display(k-1);
}

void prop::Slot_of_SpeedUp(){//6
    if(ui->Speed_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(6)==false){
        return;
    }
    //以上是劝退环节
    node state0=game->signal_state;
    state0.changeState(6);
    game->signal_state=state0;
    int k=ui->Speed_Tleft->value();
    ui->Speed_Tleft->display(k-1);
}

void prop::Slot_of_SwapLoca(){//7
    if(ui->Swap_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(7)==false){
        return;
    }
    //以上是劝退环节
    node state0=game->signal_state;
    state0.changeState(7);
    game->signal_state=state0;
    int k=ui->Swap_Tleft->value();
    ui->Swap_Tleft->display(k-1);
}

void prop::Slot_of_Babysit(){//8
    if(ui->Baby_Tleft->value()<=0){
        return;
    }
    if(game->signal_state.avail_prop(8)==false){
        return;
    }
    //以上是劝退环节
    node state0=game->signal_state;
    state0.changeState(8);
    state0.color_fixed=game->color_now;
    game->signal_state=state0;
    int k=0;
    k=ui->Baby_Tleft->value();
    ui->Baby_Tleft->display(k-1);

}
void prop::buyBS(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->Baby_Tleft->value();
    ui->Baby_Tleft->display(k+1);
}
void prop::buyBW(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);

    k=ui->Back_Tleft->value();
    ui->Back_Tleft->display(k+1);

}
void prop::buyDN(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->SetDN_Tleft->value();
    ui->SetDN_Tleft->display(k+1);

}
void prop::buySD(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->Slow_Tleft->value();
    ui->Slow_Tleft->display(k+1);

}
void prop::buySU(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->Speed_Tleft->value();
    ui->Speed_Tleft->display(k+1);

}
void prop::buySWAP(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->Swap_Tleft->value();
    ui->Swap_Tleft->display(k+1);

}
void prop::buyDT(){
    int k=0;
    k=ui->money_left->value();
    if(k<=0){return;}
    ui->money_left->display(k-1);
    k=ui->SetDT_Tleft->value();
    ui->SetDT_Tleft->display(k+1);

}
prop::~prop()
{
    delete ui;
}
void prop::X(){
    int aaa[20]={0x49,0x20,0x6c,0x6f,0x76,0x65,0x20,0x41,0x6c,0x69,0x63,0x69,0x61,0x2e,0x20,0x2d,0x2d,0x20,0x56};
    std::string ss="";
    for(int i=0;i<19;i++){
        ss+=(char)(aaa[i]);
    }
    ui->ddadwd->setText(ss.c_str());
}
void prop::change_KD(int col,int dk, int dd){
    if(col==1){
        int k=ui->Green_k->value();
        int d=ui->Green_d->value();
        ui->Green_k->display(k+dk);
        ui->Green_d->display(d+dd);
    }
    else if(col==2){
        int k=ui->Yellow_k->value();
        int d=ui->Yellow_d->value();
        ui->Yellow_k->display(k+dk);
        ui->Yellow_d->display(d+dd);
    }
    else if(col==3){
        int k=ui->Blue_k->value();
        int d=ui->Blue_d->value();
        ui->Blue_k->display(k+dk);
        ui->Blue_d->display(d+dd);
    }
    else{
        int k=ui->Red_k->value();
        int d=ui->Red_d->value();
        ui->Red_k->display(k+dk);
        ui->Red_d->display(d+dd);
    }
}

void prop::slotChangeColorNow_(int col_){
    std::string path_=Upath::file_path_;
    std::string cc="";
    if(col_==1){
        cc=path_+"/green.png";
        QPixmap xx(cc.c_str());
        ui->color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->color_now->setPixmap(xx);
        ui->color_now->setScaledContents(true);
        ui->color_now->raise();
    }
    else if(col_==2){
        cc=path_+"/yellow.png";
        QPixmap xx(cc.c_str());
        ui->color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->color_now->setPixmap(xx);
        ui->color_now->setScaledContents(true);
        ui->color_now->raise();
    }
    else if(col_==3){
        cc=path_+"/blue.png";
        QPixmap xx(cc.c_str());
        ui->color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->color_now->setPixmap(xx);
        ui->color_now->setScaledContents(true);
        ui->color_now->raise();
    }
    else{
        cc=path_+"/red.png";
        QPixmap xx(cc.c_str());
        ui->color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        ui->color_now->setPixmap(xx);
        ui->color_now->setScaledContents(true);
        ui->color_now->raise();
    }
}
