#include "Game.h"
#include <iostream>
#include <random>

#define dice_round 0
#define plane_round 1

#define Green 1
#define Yellow 2
#define Blue 3
#define Red 4


int Game::signal_dice(int x){
    if(round!=dice_round){return legal_dice_num_now;}
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1,6);
    int random_number=dis(gen);

    legal_dice_num_now=random_number;
    round^=1;
    return legal_dice_num_now;
}

int Game::signal_plane_move(int id_plane){
    if(round!=plane_round){return planes[id_plane].pos;}
    if(planes[id_plane].color!=color_now){return planes[id_plane].pos;}
    if(planes[id_plane].pos>=200){
        if(legal_dice_num_now!=6){return planes[id_plane].pos;}
        if(planes[id_plane].pos!=chatGPT.res_pos(planes[id_plane].color,res_tot[planes[id_plane].color])){
            return planes[id_plane].pos;
        }
    }
    if(planes[id_plane].pos>=200){
        res_tot[planes[id_plane].color]--;
    }
    planes[id_plane].move_func(legal_dice_num_now,game_time);
    game_time++;
    color_now=(color_now+1)%4;
    if(color_now==0)color_now=4;
    return planes[id_plane].pos;
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
               res_tot[count_[i][j].color]++;
               int plane_id_now=count_[i][j].plane_id;
               planes[plane_id_now].res_func(res_tot[count_[i][j].color]);

            }
        }

    }
}


void Game::arrived_judge(){
    for(int i=1;i<=16;i++){
        if(planes[i].is_win==true){continue;}
        if(chatGPT.isGoalState(planes[i].color,planes[i].plane_id)){
            arrived_plane_num[planes[i].color]++;
            //需要设计一个函数，把这个飞机扔到其他地方。

        }
    }
}

int Game::victory_judge(){
    for(int i=1;i<=4;i++){
        if(arrived_plane_num[i]>=4){return i;}
    }
    return -1;
}

int Game::judge(){
    //依次组合上面这些小judge
}

