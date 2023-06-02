#include "plane.h"

int plane::move_func(int dice_num,int time_now){
    time_arrived=time_now;//更新时间
    int id_now=pos,col=color,dir_=dir;
    for(int k=1;k<=dice_num;k++){
        id_now=chatGPT.next_pos(col,id_now,dir_);
    }
    pos=id_now;
    return id_now;
}

int plane::res_func(int tot_){
    pos=chatGPT.res_pos(color,tot_);
    return pos;
}



