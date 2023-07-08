#ifndef GAME_H
#define GAME_H

#include "plane.h"
#include "structures.h"
#include <QObject>
/*
    一些奇怪的话
    不要害怕bug，只要不是致命的bug，就不能算作bug，而是“游戏特性”。
*/

class PlaneState{
public:
    /*
        home 在飞机场的棋子个数
        notHome 不在飞机场且没有抵达终点的棋子个数

        fly() 飞机起飞
        eaten() 飞机被吃
        arrived() 飞机抵达终点
        check_change() 判断是否可以更换回合
        tran() 维护颜色托管之后的游戏信息
        died[] 记录玩家是否投降
        die() 玩家投降
        check_died() 查询玩家是否投降
    */
    int home[6];
    int notHome[6];
    PlaneState();
    void fly(int color);
    void eaten(int color);
    void arrived(int color);
    //check_change的使用首先要确认它是对在家里的飞机使用的
    bool check_change(int color);
    void tran(int col0,int col1);

    bool died[6];
    void die(int color);
    bool check_died(int color);
};

class Game: public QObject{
    /*
        最基本的信号:
        1. 骰子
        2. 棋子
    */

    Q_OBJECT
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
    int player_kill_num[6];
    int player_die_num[6];

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
    int dice_time_remain;//new
    int game_time;
    int signal_dice();
    int signal_plane_move(int id_plane);
    int getcolor(int id_);

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
    /*
        update1:
        statenow 用以更细致地维护游戏信息
        change_color() 进行当前颜色的切换
    */
    PlaneState statenow;
    void change_color();



    int arrived_plane_num[5];

    int res_tot[5];

    void ini_for_judge();
    void eaten_judge();
    void arrived_judge();
    int victory_judge();
    int judge();



    /*
        补充功能模块
    */
    /*
        update2:
        加入一些新的特性
        change_mul() 将对应飞机加速或减速
        rev() 改变飞机移动方向
        change_color() 实现颜色托管功能
        swap_loca() 交换两个飞机的位置
    */
    void change_mul(int id_, int x);
    void rev(int id_);
    void change_color(int player_color, int target_color);
    void swap_loca(int id_1, int id_2);


    /*
        构造函数
    */
    Game(QObject* p);


    /*
        run() 用以发射spread()信号
        RMBplayer() 用以发射buy()信号
        onTime 中间变量
    */
    void run();//发射spread信号
    void RMBplayer();
    bool onTime;
private slots:
    /*
        ChangeOnTime() 中间信号
        EmitBuy() 连接prop的氪金按钮
    */
    void ChangeOnTime(bool);
    void EmitBuy();


signals:
    void spread();//对所有飞机广播新的游戏信息

    void buy();//氪金，对prop的剩余金币数量发出信号

    void Finish_changeOnTime();//中间信号
    void signal_color_now(int);//对prop中的显示当前玩家颜色组件发出信号
    void signal_win_state_now(int);//对gen_发出游戏是否决出胜负

    void signal_pos(int,int);//对飞机发出位置信号
    void change_kd(int,int,int);//对prop中的玩家KD表发出信号
public:
    node signal_state;//用以维护Qt部分之间的信号秩序
    void emit_color_now();//发射signal_color_now
    void emit_win_state_now(int x);//发射signal_win_state_now

    void emit_pos_(int pos_,int id_);//发射signal_pos
    void emit_change_kd(int col,int dk,int dd);//发射change_kd
};

#endif // GAME_H
