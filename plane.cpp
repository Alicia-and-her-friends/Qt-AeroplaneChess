#include "plane.h"
#include <iostream>
int plane::move_func(int dice_num,int time_now){
    time_arrived=time_now;//更新时间
    if(mul_num==0){dice_num/=2;}
    else dice_num*=mul_num;
    if(pos>200)dice_num=1;
    int id_now=pos,col=color,dir_=dir;
    for(int k=1;k<=dice_num;k++){
        std::cerr<<"id now "<<id_now<<"\n";
        id_now=chatGPT.next_pos(col,id_now,dir_);
        std::cerr<<"id next "<<id_now<<"\n";
    }
    id_now=chatGPT.jump_pos(col,id_now,dir_);
    pos=id_now;
    return id_now;
}

int plane::res_func(int tot_){
    pos=chatGPT.res_pos(color,tot_);
    return pos;
}

plane::plane():chatGPT(){}
plane::plane(int id_,int pos_,int col_):plane_id(id_),pos(pos_),color(col_),mul_num(1){chatGPT=ask();dir=0;}


temp_plane::temp_plane(){}
temp_plane::temp_plane(int id_, int pos_, int time_,int col_):plane_id(id_),pos(pos_),time_arrived(time_),color(col_){}
