#ifndef GAME_H
#define GAME_H
#include "plane.h"
#include "square.h"
#include "structures.h"
/*
    一些奇怪的话
    不要害怕bug，只要不是致命的bug，就不能算作bug，而是“游戏特性”。
*/

class Game{
    /*
        最基本的信号:
        1. 骰子
        2. 棋子
    */

    public:
    /*
        基本功能模块
    */
    /*
        chatGPT 知识库
        planes 储存游戏中所有的飞机信息
        count_[][] 用以进行一些中间操作
        tot_for_count[] 用以进行一些中间操作

        round 用以记录当前是骰子回合(0)还是行棋回合(1)
        color_now 若是行棋回合，表示当前回合的颜色


    */
    ask chatGPT;
    plane  planes[20];
    
    temp_plane count_[300][20];
    int tot_for_count[300];    

    int round;
    int color_now;
    
    /*
        信号函数具有一个功能，可以判断当前点击是否有效。
        按钮对应于对游戏状态的更新。
        legel_dice_num_now 用于维护当前合法的骰子点数，防止误触
        game_time 用以为棋子何时抵达一个格子时做标记，有助于判断同一个棋盘上有多个子时，谁应该被吃。
   
        signal_dice 骰子按钮信号，返回合法的骰子值
        signal_plane_move 飞机按钮信号，返回合法的飞机坐标
    */
    int legal_dice_num_now;
    int game_time;
    int signal_dice(int x);
    int signal_plane_move(int id_plane);

    /*
        需要一个大的判断函数模块，来判断当前比赛的状态。
        在每次信号交换后都要运行一次。
        可以写成judge
        ---------------
        整个judge的流程：
        ini_for_judge() 初始化
        eaten_judge() 判断是否有棋子应该被吃
        arrived_judge() 判断是否有棋子抵达终点
        victory_judge() 判断是否有玩家胜利，返回值若为-1，则游戏继续；否则返回获胜玩家id

        arrived_plane_num[] 每位玩家抵达终点的飞机数目
        res_tot[] 用以维护飞机场的有序性

    */

    int arrived_plane_num[5];
    
    int res_tot[5];

    void ini_for_judge();
    void eaten_judge();
    void arrived_judge();
    int victory_judge();
    int judge();

    //每次judge完，所有飞机统一发射信号，一起依次改变位置

    /*
        补充功能模块
    */



    /*
        构造函数
    */
    Game();
};

#endif // GAME_H