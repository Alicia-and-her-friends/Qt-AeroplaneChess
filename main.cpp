#include "mainwindow.h"
#include "plane.h"
#include "gen_.h"
#include "QPlane.h"
#include "start.h"
#include "Game.h"
#include "prop.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QIcon>
#include <QBitmap>
#include <cstring>
#include <iostream>

//#include <QMediaPlaylist>

using namespace std;

class Board{
public:
    int x;
    int y;
    int color; //绿色为1 黄色为2 蓝色为3 红色为4
    Board(int x_, int y_, int color_): x(x_), y(y_), color(color_) {}
    Board(){}
};

//the x-coordinates and y-coordinates of labelled grid points
Board board[300];
int x_coord[300]{
                 0, 255, 235, 235, 255, 215, 170, 127, 75, 65, 65, 65, 65, 65, 75, 127, 170,
                 215, 255, 235, 235, 255, 300, 343, 387, 430, 473, 520, 540, 540, 520, 560,
                 605, 648, 695, 710, 710, 710, 710, 710, 695, 648, 605, 560, 520, 540, 540,
                 520, 473, 430, 387, 343, 300, 0, 0, 0, 0, 0, 0, 0, 0, 387, 387, 387, 387, 387,
                 388, 0, 0, 0, 0, 127, 170, 213, 256, 299, 345, 0, 0, 0, 0, 387, 387, 387, 387,
                 387, 388, 0, 0, 0, 0, 648, 607, 562, 519, 476, 425, 0, 0, 0, 0, 222, 17, 547,
                 752, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 133, 133, 63, 63, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 65, 133, 65, 133, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 638, 638, 708, 708, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 710, 638, 710, 638, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int y_coord[300]{
                 0, 675, 630, 587, 540, 500, 520, 520, 500, 457, 414, 371, 328, 285, 240, 220, 220,
                 240, 200, 154, 111, 65, 50, 50, 50, 50, 50, 65, 111, 154, 200, 240,
                 220, 220, 240, 285, 328, 371, 414, 457, 500, 520, 520, 500, 540, 587, 630,
                 675, 693, 693, 693, 693, 693, 0, 0, 0, 0, 0, 0, 0, 0, 630, 587, 544, 501, 458,
                 410, 0, 0, 0, 0, 371, 371, 371, 371, 371, 371, 0, 0, 0, 0, 111, 154, 197, 240,
                 283, 330, 0, 0, 0, 0, 371, 371, 371, 371, 371, 371, 0, 0, 0, 0, 722, 207, 2,
                 532, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 690, 625, 690, 625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 115, 115, 50, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 115, 50, 115, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 625, 625, 690, 690, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

Plane * plane[20]{NULL};

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    Game game(nullptr);
    start menu(nullptr,&game);

    std::cerr<<"ok\n";

    MainWindow w(nullptr,&game);
    prop pp(nullptr,&game);
    gen_ gen__(nullptr,&menu,&game,&pp,&w);

    //pp.show();
    //set up the board
    for(int i=1; i<=52; i++){
        int tempcolor;
        if(i%4==0) tempcolor = 3;
        if(i%4==1) tempcolor = 4;
        if(i%4==2) tempcolor = 1;
        if(i%4==3) tempcolor = 2;
        board[i] = Board(x_coord[i], y_coord[i], tempcolor);
    }
    board[101] = Board(x_coord[101], y_coord[101], 1);
    board[102] = Board(x_coord[102], y_coord[102], 2);
    board[103] = Board(x_coord[103], y_coord[103], 3);
    board[104] = Board(x_coord[104], y_coord[104], 4);
    for(int i=61; i<=66; i++){
        board[i] = Board(x_coord[i], y_coord[i], 1);
    }
    for(int i=71; i<=76; i++){
        board[i] = Board(x_coord[i], y_coord[i], 2);
    }
    for(int i=81; i<=86; i++){
        board[i] = Board(x_coord[i], y_coord[i], 3);
    }
    for(int i=91; i<=96; i++){
        board[i] = Board(x_coord[i], y_coord[i], 4);
    }
    for(int i=201; i<=216; i++){
        board[i] = Board(x_coord[i], y_coord[i], 1);
    }
    for(int i=221; i<=236; i++){
        board[i] = Board(x_coord[i], y_coord[i], 2);
    }
    for(int i=241; i<=256; i++){
        board[i] = Board(x_coord[i], y_coord[i], 3);
    }
    for(int i=261; i<=276; i++){
        board[i] = Board(x_coord[i], y_coord[i], 4);
    }


    //place the planes
    for(int i=1; i<=4; i++){
        //int k=0;if(i%4==0)k=4;
        plane[i] = new Plane(&w, 1,i,&game);
        if(i==4) plane[i]->move(board[204].x, board[204].y);
        else
            plane[i]->move(board[i%4 + 200].x, board[i%4 + 200].y);
    }
    for(int i=5; i<=8; i++){
        plane[i] = new Plane(&w, 2,i,&game);
        if(i==8) plane[i]->move(board[224].x, board[224].y);
        else
            plane[i]->move(board[i%4 + 220].x, board[i%4 + 220].y);
    }
    for(int i=9; i<=12; i++){
        plane[i] = new Plane(&w, 3,i,&game);
        if(i==12) plane[i]->move(board[244].x, board[244].y);
        else
            plane[i]->move(board[i%4 + 240].x, board[i%4 + 240].y);
    }
    for(int i=13; i<=16; i++){
        plane[i] = new Plane(&w, 4,i,&game);
        if(i==16) plane[i]->move(board[264].x, board[264].y);
        else
            plane[i]->move(board[i%4 + 260].x, board[i%4 + 260].y);
    }

    menu.show();
    //w.show();
    return a.exec();
}
