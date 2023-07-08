#include "start.h"
#include "ui_start.h"
#include "structures.h"
#include <iostream>
#include <QLabel>
#include <QPixmap>
#include <cstring>
#include <QBitmap>
#include <QMainWindow>
#include "path.h"

start::start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
}

start::start(QWidget *parent, Game *game_):
    QMainWindow(parent),
    game(game_),
    ui(new Ui::start){
    ui->setupUi(this);
    this->resize(800,600);

    std::string path_=Upath::file_path_;
    std::string cc=path_+"/pic.png";
    QPixmap bkgnd(cc.c_str());
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
    connect(ui->pushButton_7,SIGNAL(clicked(bool)),this,SLOT(slotclk()));
    connect(ui->pushButton_8,SIGNAL(clicked(bool)),this,SLOT(close()));
}

start::~start()
{
    delete ui;
}
void start::emit_clk(){
    emit clk();
}
void start::slotclk(){
    emit_clk();
}
