#ifndef STRUCTURES_H
#define STRUCTURES_H

#include "square.h"

class ask{
    /*
        知识库
        通过ask类，实现chatGPT功能。
        大多数的询问操作，均通过ask chatGPT内置函数与数据实现。
    */
public:
    square squares[300];
    square ask_for_info(int square_id);

    /*
        Next表
        Next[color][id_now][direction]
        用以返回一个棋子下一步的位置。
    */
    int Next[5][300][3];
    int next_pos(int color, int id_now, int dir);
    /*
        jump表
        用以返回同色跳跃的下一个各点的位置
    */
    int jump[5][300][3];
    int jump_pos(int color, int id_now, int dir);

    /*
        reset表，
        Reset[color][tot]表示reset后的位置坐标编号
        用以将一个棋子归于原位。
    */
    int Reset[5][20];
    int res_pos(int color, int tot);

    /*
        GoalState表
        GoalState[color]
        用以判断一个棋子是否处于终点。
    */
    int GoalState[5];
    bool isGoalState(int color, int pos_x);


    //构造函数
    ask();
};

//用于传输状态
class node{
public:
    int current_round;//0d,1p
    int type;//type如果归零，意味着万事皆可行
    /*
        0,1 骰子（0），飞机回合（1）
        2 预设骰子点数（按一次就行）
        3 改变骰子投掷次数（按一次就行）
        4 减速器（后继还需要按一个飞机）
        5 反向移动（后继还需要按一个飞机）
        6 加速器（后继还需要按一个飞机）
        7 交换位置（后续需要按两个飞机）
        8 颜色托管（后续还需要选一个颜色）//可以通过选飞机来实现
    */
    int step;

    int color_fixed;
    //0: NO
    //1, 2, 3, 4
    int id_for_swap[3];
    int tot_swap;

    //判断是否可行
    bool avail_prop(int x);
    bool avail_dice();
    bool avail_plane(int color);


    void changeState(int x);
    void change_current_round();
    void reset();
    node();
    node(int cr_,int tp_, int cf_);



};

#endif // STRUCTURES_H
