#include "QPlane.h"
#include "Game.h"
//#include "path.h"
//#include "ui_mainwindow.h"
#include <QPixmap>
#include <QBitmap>
#include <QMainWindow>
#include <cstring>
#include <iostream>
//std::string path_="/Users/vincentarak/QTs/Sources";
std::string path_=Upath::file_path_;
//std::string path_="/Users/xiaohanzhou/Desktop/QtProgram";


Plane::Plane(QMainWindow *parent, int Pcolor): QPushButton(parent)
{
    if(Pcolor == 1){
        std::string temp_file=path_+"/greenPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/greenPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 2){
        std::string temp_file=path_+"/yellowPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/yellowPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 3){
        std::string temp_file=path_+"/bluePlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/bluePlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 4){
        std::string temp_file=path_+"/redPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/redPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
}


Plane::Plane(QMainWindow* parent, int Pcolor,int id_, Game* game_): QPushButton(parent),
    color(Pcolor),
    id(id_),
    game_now(game_)
{
    pos=200+(Pcolor-1)*20+(id_%4);
    if(id_%4==0)pos+=4;
    if(Pcolor == 1){
        std::string temp_file=path_+"/greenPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/greenPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 2){
        std::string temp_file=path_+"/yellowPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/yellowPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 3){
        std::string temp_file=path_+"/bluePlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/bluePlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(Pcolor == 4){
        std::string temp_file=path_+"/redPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/redPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    QObject::connect(this,SIGNAL(clicked(bool)),this,SLOT(slotbuttonclicked(bool)));
    QObject::connect(game_now,SIGNAL(spread()),this,SLOT(update()));
    QObject::connect(game_now,SIGNAL(signal_pos(int,int)),this,SLOT(singal_move(int,int)));
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
void Plane::slotbuttonclicked(bool checked){
    //if(checked==false)return;
    /*
        void change_mul(int id_, int x);
        void rev(int id_);
        void change_color(int player_color, int target_color);
        void swap_loca(int id_1, int id_2);
    */
    if(game_now->signal_state.avail_plane(id)==false){
        return ;
    }
    if(game_now->signal_state.type>=4){
        if(game_now->signal_state.type==4){
            game_now->change_mul(id,0);
        }
        else if(game_now->signal_state.type==5){
            game_now->rev(id);
        }
        else if(game_now->signal_state.type==6){
            game_now->change_mul(id,2);
        }
        else if(game_now->signal_state.type==7){
            if(game_now->signal_state.tot_swap==1){
                game_now->swap_loca(game_now->signal_state.id_for_swap[1],id);

            }
            else{
                game_now->signal_state.tot_swap+=1;
                game_now->signal_state.id_for_swap[1]=id;
                return ;
            }
        }
        else if(game_now->signal_state.type==8){
            game_now->change_color(game_now->signal_state.color_fixed,game_now->getcolor(id));
        }
        game_now->signal_state.reset();
        return;
    }
    //以上是信号处理部分
    int new_pos=game_now->signal_plane_move(id);
    pos=new_pos;
    this->move(x_coord[new_pos],y_coord[new_pos]);
    //this->move(33,44);
}
void Plane::update(){
    int new_pos=game_now->signal_plane_move(id);
    color=game_now->getcolor(id);

    if(color == 1){
        std::string temp_file=path_+"/greenPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/greenPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(color == 2){
        std::string temp_file=path_+"/yellowPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/yellowPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(color == 3){
        std::string temp_file=path_+"/bluePlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/bluePlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    if(color == 4){
        std::string temp_file=path_+"/redPlane_small.png";
        const char* c=temp_file.c_str();
        QPixmap pixmap(c);
        resize(pixmap.size());
        setMask(QBitmap(pixmap.mask()));
        std::string temp_file2="QPushButton{border-image: url("+path_+"/redPlane_small.png);}";
        const char* d=temp_file2.c_str();
        setStyleSheet(d);
    }
    pos=new_pos;
    this->move(x_coord[new_pos],y_coord[new_pos]);
}

void Plane::singal_move(int pos_,int id_){
    if(id_!=id){return;}
    int new_pos=pos_;
    pos=new_pos;
    this->move(x_coord[new_pos],y_coord[new_pos]);
}

