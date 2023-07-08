#include "Game.h"
#include "plane.h"
#include <iostream>
#include <random>

#define dice_round 0
#define plane_round 1

#define Green 1
#define Yellow 2
#define Blue 3
#define Red 4

#define tomb 299

PlaneState::PlaneState(){
    for(int i=1;i<5;i++){
        home[i]=4;
        notHome[i]=0;
        died[i]=false;
    }

}
void PlaneState::fly(int color){home[color]--;notHome[color]++;}
void PlaneState::eaten(int color){home[color]++;notHome[color]--;}
bool PlaneState::check_change(int color){
    return !(notHome[color]>0);
}
void PlaneState::arrived(int color){
    notHome[color]--;
}
void PlaneState::tran(int col0, int col1){
    home[col1]+=home[col0];
    home[col0]=0;
    notHome[col1]+=notHome[col0];
    notHome[col0]=0;
}
void PlaneState::die(int color){
    died[color]=true;
}
bool PlaneState::check_died(int color){
    return died[color];
}

void Game::run(){
    emit spread();
}

void Game::RMBplayer(){
    emit buy();
}

void Game::emit_pos_(int pos_,int id_){
    emit signal_pos(pos_,id_);
}

void Game::emit_color_now(){
    emit signal_color_now(color_now);
}
void Game::emit_win_state_now(int x){
    emit signal_win_state_now(x);
}
void Game::emit_change_kd(int col, int dk, int dd){
    emit change_kd(col,dk,dd);
}
int Game::signal_dice(){
    if(round!=dice_round){return legal_dice_num_now;}
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,6);
    int random_number=dis(gen);

    legal_dice_num_now=random_number;
    round^=1;
    std::cerr<<color_now<<std::endl;
    std::cerr<<legal_dice_num_now<<std::endl;
    return legal_dice_num_now;
}


void Game::ini_for_judge(){
    for(int i=1;i<=100;i++){
        tot_for_count[i]=0;
    }
    for(int i=1;i<=16;i++){
        if(planes[i].is_win==true){continue;}
        int pos_plane=planes[i].pos;
        ++tot_for_count[pos_plane];
        count_[pos_plane][tot_for_count[pos_plane]]=temp_plane(planes[i].plane_id,planes[i].pos,planes[i].time_arrived,planes[i].color);
    }
}

void Game::eaten_judge(){
    for(int i=1;i<=100;i++){
        if(tot_for_count[i]<=1){continue;}
        int time_la=-1,color_last=0;
        for(int j=1;j<=tot_for_count[i];j++){
            if(count_[i][j].time_arrived>time_la){
                time_la=count_[i][j].time_arrived;
                color_last=count_[i][j].color;
            }
        }
        //接下来需要把异色的时间更早的全部吃掉
        for(int j=1;j<=tot_for_count[i];j++){
            if(count_[i][j].color!=color_last){
                emit_change_kd(count_[i][j].color,0,1);
                player_die_num[count_[i][j].color]++;
                emit_change_kd(color_last,1,0);
                player_kill_num[color_last]++;
                res_tot[count_[i][j].color]++;
                int plane_id_now=count_[i][j].plane_id;
                statenow.eaten(count_[i][j].color);
                planes[plane_id_now].res_func(res_tot[count_[i][j].color]);

            }
        }

    }
}


void Game::arrived_judge(){
    for(int i=1;i<=16;i++){
        if(planes[i].is_win==true){continue;}
        if(chatGPT.isGoalState(planes[i].color,planes[i].pos)){
            arrived_plane_num[planes[i].color]++;
            //需要设计一个函数，把这个飞机扔到其他地方。
            planes[i].pos=tomb;
            planes[i].is_win=true;
            statenow.notHome[planes[i].color]--;

        }
    }
    run();
}

int Game::victory_judge(){
    for(int i=1;i<=4;i++){
        if(arrived_plane_num[i]>=4){
            std::cerr<<"DAMN BRO\n";
            emit_win_state_now(i);
            return i;
        }
    }
    emit_win_state_now(-1);
    return -1;
}

int Game::judge(){
    //依次组合上面这些小judge
    ini_for_judge();
    eaten_judge();
    run();//********************
    arrived_judge();
    victory_judge();

    return 0;
}

void Game::change_color(){
    for(;1;){
        color_now=(color_now+1)%4;
        if(color_now==0)color_now=4;

        if(statenow.check_died(color_now)==false)break;
    }
    emit_color_now();
}
int Game::signal_plane_move(int id_plane){
    std::cerr<<id_plane<<" in signal_plane_move\n";
    if(round!=plane_round){
        std::cerr<<"but not in plane round\n";
        return planes[id_plane].pos;
    }
    if(planes[id_plane].color!=color_now){
        std::cerr<<"but not the right color\n";
        return planes[id_plane].pos;
    }
    if(planes[id_plane].pos>=200){
        std::cerr<<"plane in airport\n";
        if(legal_dice_num_now!=6){
            std::cerr<<"dice num ="<<legal_dice_num_now<<"\n";
            if(statenow.check_change(planes[id_plane].color)){
                round^=1;
                game_time++;
                change_color();
                std::cerr<<"changed\n";
            }
            return planes[id_plane].pos;

        }
        if(planes[id_plane].pos!=chatGPT.res_pos(planes[id_plane].color,res_tot[planes[id_plane].color])){
            std::cerr<<"not the right one "<<"plane_now.pos= "<<planes[id_plane].pos<<"instead of "<<chatGPT.res_pos(planes[id_plane].color,res_tot[planes[id_plane].color])<<"\n";
            return planes[id_plane].pos;

        }

    }

    std::cerr<<"able to fly\n";
    if(planes[id_plane].pos>=200){
        res_tot[planes[id_plane].color]--;

    }
    statenow.fly(planes[id_plane].color);
    planes[id_plane].move_func(legal_dice_num_now,game_time);
    dice_time_remain--;
    std::cerr<<dice_time_remain<<std::endl;
    round^=1;
    game_time++;
    //新加了骰子次数
    if(dice_time_remain<=0){
        change_color();
        dice_time_remain=0;
    }
    judge();
    return planes[id_plane].pos;
}

Game::Game(QObject* s_):QObject(s_),signal_state(0,0,1){
    chatGPT=ask();
    color_now=1;
    legal_dice_num_now=1;
    round=0;
    dice_time_remain=0;
    statenow=PlaneState();
    for(int col=1;col<=4;col++){
        res_tot[col]=0;
        arrived_plane_num[col]=0;
        player_die_num[col]=0;
        player_kill_num[col]=0;
        for(int i=1;i<=4;i++){
            res_tot[col]++;
            int pos_=ask().res_pos(col,i);
            planes[(col-1)*4+i]=plane((col-1)*4+i,pos_,col);
        }
    }
}
int Game::getcolor(int id_){
    return planes[id_].color;
}
void Game::rev(int id_){
    planes[id_].dir^=1;
}
void Game::change_mul(int id_,int x){
    planes[id_].mul_num=x;
}
void Game::change_color(int player_color, int target_color){
    statenow.die(player_color);
    statenow.home[target_color]+=statenow.home[player_color];
    statenow.notHome[target_color]+=statenow.notHome[player_color];
    for(int i=1;i<=16;i++){
        if(planes[i].color==player_color){
            planes[i].color=target_color;
            if(planes[i].pos>=200){
                res_tot[player_color]--;
                res_tot[target_color]++;
                planes[i].pos=planes[i].res_func(res_tot[target_color]);
            }


        }
    }
    run();
    change_color();
}
void Game::swap_loca(int id_1, int id_2){
    int temp_pos=planes[id_1].pos;
    planes[id_1].pos=planes[id_2].pos;
    planes[id_2].pos=temp_pos;
    run();
}
void Game::EmitBuy(){
    emit buy();
}

void Game::ChangeOnTime(bool x){
    onTime=x;
}

