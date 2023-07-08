#ifndef GEN__H
#define GEN__H
#include <QObject>
#include "win.h"
#include "Game.h"
#include "start.h"
#include "prop.h"
#include "mainwindow.h"

class gen_: public QObject
{
    Q_OBJECT
public:
    start* menu;
    Game* game;
    prop* pp;
    MainWindow* mw;
    win* win_state;
    bool flag;
    gen_(QObject* p=nullptr, start* menu_=nullptr, Game* game_=nullptr,prop* p__=nullptr,MainWindow* mw_=nullptr);
private slots:
    void show_();//点击之后用以显示界面
    void win_(int);//传递胜负信息
};

#endif // GEN__H
