#include "win.h"
#include "ui_win.h"
#include "path.h"
#include <iostream>
#include <cstring>
#include <QPixmap>
#include <QBitmap>


win::win(QWidget *parent,int col_) :
    QWidget(parent),
    ui(new Ui::win)
{
    ui->setupUi(this);
    std::string path_=Upath::file_path_;
    std::string cc="";
    if(col_==1){
        cc=path_+"/win_green.png";
    }
    else if(col_==2){
        cc=path_+"/win_yellow.png";

    }
    else if(col_==3){
        cc=path_+"/win_blue.png";

    }
    else{
        cc=path_+"/win_red.png";

    }
    QPixmap pixmap(cc.c_str());

    //QPixmap pixmap("/Users/vincentarak/QTs/Sources/Pay.JPG");
    ui->img->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->img->setPixmap(pixmap);
    ui->img->setScaledContents(true);

}

win::~win()
{
    delete ui;
}
