#include "gen_.h"
#include <QObject>
gen_::gen_(QObject* p, start* menu_, Game* game_,prop* p__,MainWindow* mw_):
    QObject(p),menu(menu_),game(game_),pp(p__),flag(false),mw(mw_),win_state(nullptr)
{
    connect(menu_,SIGNAL(clk()),this,SLOT(show_()));
    connect(game,SIGNAL(signal_win_state_now(int)),this,SLOT(win_(int)));
}
void gen_::show_(){
    if(flag){
        return;
    }
    flag=true;
    pp->show();
    mw->show();
}
void gen_::win_(int x){
    if(x==-1){
        return;
    }
    win_state=new win(nullptr,x);
    win_state->show();
}
