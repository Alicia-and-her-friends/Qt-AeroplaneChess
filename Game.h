#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "plane.h"
#include "square.h"
#include "structures.h"
/*
    不要害怕bug，只要不是致命的bug，就不能算作bug，而是“游戏特性”。
*/


class Game{
    /*
        他们会把信号传输过来
        
        最基本的信号:
        1. 骰子
        2. 棋子

    */
    public:
    /*
        基本功能模块
    */
    ask chatGPT;

    //player players[5];//经过我的思考，我意识到我们甚至不需要玩家。
    //square squares[200];


    /*
        飞机非常重要，我需要对飞机展开文章
    */
    plane  planes[20];

    temp_plane count_[300][20];
    int tot_for_count[300];    




    //round用以记录现在是该扔骰子了还是该行棋了: 0 骰子 1 行棋
    //color_now表示：若当前是行棋回合，该哪个颜色
    int round;
    int color_now;
    
    //void update_plane(int id_,int step);
    //void update_square_state();
    
    /*
        信号函数具有一个功能，可以判断当前点击是否有效。
        按钮对应于对游戏状态的更新。
    */
    //legel_dice_num_now用于维护当前合法的骰子点数，防止误触
    int legal_dice_num_now;
    //game_time可以用以为棋子何时抵达一个格子做标记，有助于判断同一个棋盘上有两个子时，谁应该被吃。
    int game_time;
    int signal_dice(int x);
    int signal_plane_move(int id_plane);


    /*
        需要一个大的判断函数模块，来判断当前比赛的状态。
        在每次信号交换后都要运行一次。
        可以写成judge
        ---------------
        整个judge的流程：
        判断是否有棋子应该被吃
        判断是否有棋子抵达终点
        判断是否有玩家胜利

    */

    int arrived_plane_num[5];
    
    //飞机飞走的时候，res_tot还需要减少
    int res_tot[5];

    void ini_for_judge();
    void eaten_judge();
    //void trans_judge();
    void arrived_judge();

    int victory_judge();

    //judge的返回类型为int的原因是：这样可以判断是否有玩家胜利；-1表示没有，即游戏继续进行；否则返回胜利玩家的id。
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