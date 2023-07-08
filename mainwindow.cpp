#include "mainwindow.h"
//#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QPixmap>
#include <QBitmap>
#include <QTimer>
#include <QThread>
#include <QEventloop>
#include <ctime>
#include "Game.h"
#include "path.h"
#include <iostream>
#include <cstring>

MainWindow::MainWindow(QWidget *parent, Game* game_)
    : QMainWindow(parent)
    , game_now(game_)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    this->resize(810,794);
    std::string path_=Upath::file_path_;
    std::string cc=path_+"/WechatIMG119.png";
    QPixmap bkgnd(cc.c_str());
    //QPixmap bkgnd("/Users/vincentarak/QTs/Sources/WechatIMG119.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    /*
    std::string path_=Upath::file_path_;
    std::string temp_file=path_+"/Pay.JPG";
    const char* c=temp_file.c_str();
    QPixmap pixmap(c);

    //QPixmap pixmap("/Users/vincentarak/QTs/Sources/Pay.JPG");
    ui->Pay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->Pay->setPixmap(pixmap);
    ui->Pay->setScaledContents(true);
    */
    //颜色
    color_now = new QLabel(this);
    //color_now->setGeometry(150,430,40,40);
    color_now->setGeometry(150,430,0,0);
    cc=path_+"/green.png";
    QPixmap xx(cc.c_str());
    color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    color_now->setPixmap(xx);
    color_now->setScaledContents(true);
    color_now->raise();
    connect(game_now,SIGNAL(signal_color_now(int)),this,SLOT(slotChangeColorNow(int)));
    //winState
    win_state=new QLabel(this);
    win_state->setGeometry(270,450,40,40);
    //win_state->raise();
    win_state->setText("");
    connect(game_now,SIGNAL(signal_win_state_now(int)),this,SLOT(slotChangeWinState(int)));
    //骰子
    dice = new QPushButton(this);
    dice->setGeometry(10, 530, 45, 45);
    QPixmap pix;
    //std::string ccc=path_+"/green.png";
    std::string ccc=path_+"/dice_1_small.jpg";
    pix = QPixmap(ccc.c_str());
    dice->resize(pix.size());
    dice->setMask(QBitmap(pix.mask()));
    ccc="QPushButton{border-image: url("+path_+"/dice_1_small.jpg);}";
    setStyleSheet(ccc.c_str());
    //setStyleSheet("QPushButton{border-image: url(/Users/vincentarak/QTs/Sources/dice_1_small.jpg);}");
    dice->setCheckable(true);
    connect(dice, SIGNAL(clicked(bool)), this, SLOT(slotDiceClicked(bool)));
}


MainWindow::~MainWindow(){
//    delete ui;
}

void MainWindow::m_sleep(int time){
    QEventLoop eloop;
    QTimer::singleShot(time, &eloop, SLOT(quit()));
    eloop.exec();
}


void MainWindow::slotDiceClicked(bool checked){
    std::string path_=Upath::file_path_;
    QPixmap pixmap;
    std::string cc="";

    cc=path_+"/dice_1_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_1_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    cc=path_+"/dice_2_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_2_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    cc=path_+"/dice_3_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_3_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    cc=path_+"/dice_4_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_4_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    cc=path_+"/dice_5_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_5_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    cc=path_+"/dice_6_small.jpg";
    pixmap = QPixmap(cc.c_str());
    dice->resize(pixmap.size());
    dice->setMask(QBitmap(pixmap.mask()));
    cc="QPushButton{border-image: url("+path_+"/dice_6_small.jpg);}";
    setStyleSheet(cc.c_str());
    m_sleep(200);

    //int dicenum = arc4random() % 6;
    int dicenum = game_now->signal_dice();
    switch(dicenum){
    case 1:
        cc=path_+"/dice_1_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_1_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    case 2:
        cc=path_+"/dice_2_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_2_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    case 3:
        cc=path_+"/dice_3_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_3_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    case 4:
        cc=path_+"/dice_4_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_4_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    case 5:
        cc=path_+"/dice_5_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_5_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    case 6:
        cc=path_+"/dice_6_small.jpg";
        pixmap = QPixmap(cc.c_str());
        dice->resize(pixmap.size());
        dice->setMask(QBitmap(pixmap.mask()));
        cc="QPushButton{border-image: url("+path_+"/dice_6_small.jpg);}";
        setStyleSheet(cc.c_str());
        break;
    }
}

void MainWindow::slotChangeColorNow(int col_){
    std::string path_=Upath::file_path_;
    std::string cc="";
    if(col_==1){
        cc=path_+"/green.png";
        QPixmap xx(cc.c_str());
        color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        color_now->setPixmap(xx);
        color_now->setScaledContents(true);
        color_now->raise();
    }
    else if(col_==2){
        cc=path_+"/yellow.png";
        QPixmap xx(cc.c_str());
        color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        color_now->setPixmap(xx);
        color_now->setScaledContents(true);
        color_now->raise();
    }
    else if(col_==3){
        cc=path_+"/blue.png";
        QPixmap xx(cc.c_str());
        color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        color_now->setPixmap(xx);
        color_now->setScaledContents(true);
        color_now->raise();
    }
    else{
        cc=path_+"/red.png";
        QPixmap xx(cc.c_str());
        color_now->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        color_now->setPixmap(xx);
        color_now->setScaledContents(true);
        color_now->raise();
    }

}
void MainWindow::slotChangeWinState(int x){
    //std::cerr<<x<<" SHIT\n";
    //win_state=new QLabel(this);
    //win_state->setGeometry(270,450,40,40);
    //win_state->raise();
    //win_state->setText("Result: ");
    if(x==-1){
        //std::cerr<<"WHY\n";
        //this->win_state->setText("Result: 1");
        //win_state->raise();
    }
    else if(x==1){
        //this->win_state->setText("Result: GREEN WIN");
        //win_state->raise();
    }
    else if(x==2){
        //this->win_state->setText("Result: YELLOW WIN");
        //win_state->raise();
    }
    else if(x==3){
        //this->win_state->setText("Result: BLUE WIN");
        //win_state->raise();
    }
    else{
        //this->win_state->setText("Result: RED WIN");
        //win_state->raise();
    }
}

