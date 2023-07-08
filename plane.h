#ifndef PLANE_H
#define PLANE_H

#include "structures.h"

//#include "Game.h"

class plane{
public:
    /*
        plane_id 飞机的编号
        pos 飞机的坐标（以id形式表示）
        color 飞机的颜色
        dir 表示方向，0:正向，1:反向（所谓正向，指顺时针；所谓反向，指逆时针）
        is_win 表示当前飞机是否抵达终点
        time_arrived 用以表示飞机何时抵达当前格点（用以判断同一个格子有多架飞机时，谁吃谁）
        chatGPT 知识库，用以询问。
        ------
        move_func() 实现棋子的移动
        res_func() 将棋子重置回飞机场
    */
    int plane_id;
    int pos;
    int color;
    int dir;
    int time_arrived;
    bool is_win;
    ask chatGPT;
    /*
        update2:
        int mul 用以维护飞机是否加速或者减速
    */
    int mul_num;

    int move_func(int dice_num,int time_now);

    int res_func(int tot_);


    //构造函数
    plane();
    plane(int id_, int pos_, int col_);

};

class temp_plane{
    /*
        用以进行一些中间操作的飞机类型，我称之为模型机。
    */
public:
    int plane_id;
    int pos;
    int time_arrived;
    int color;

    temp_plane();
    temp_plane(int id_, int pos_, int time_,int col_);


};

#endif // PLANE_H
