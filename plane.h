#ifndef PLANE_H
#define PLANE_H
#include "square.h"
#include "structures.h"

class plane{
    public:
    /*
        plane_id
        pos: represented by id
        color
        path 路径
        dir 表示方向，0:正向，1:反向
        is_win表示当前飞机是否抵达终点
    */
    int plane_id;
    int pos;
    int color;
    int dir;
    int time_arrived;
    bool is_win;
    ask& chatGPT;

    //plane_list path;//我似乎直接架空了path.h
    //update,我直接架空了planelist

    int move_func(int dice_num,int time_now);

    int res_func(int tot_);
    

    //构造函数
    plane();

};

class temp_plane{
    public:
    int plane_id;
    int pos;
    int time_arrived;
    int color;

    temp_plane();
    temp_plane(int id_, int pos_, int time_,int col_);


};

#endif // PLANE_H