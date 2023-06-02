#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "square.h"

class ask{
    /*
        ask函数用以保存所有的格子的id对应的格子类型信息。
        在初始化的时候，将所有信息传入。
    */
    public:
    square squares[300];


    square ask_for_info(int square_id);
    
    /*
        Next表
        Next[color][id_now][direction]
    */
    int Next[5][300][3];
    int next_pos(int color, int id_now, int dir);


    /*
        reset表，
        Reset[color][tot]表示reset后的位置坐标编号
    */ 
    int Reset[5][20];
    int res_pos(int color, int tot);

    //构造函数
    ask();
};

class plane_list{
    /*
        首先，需要在这个类内部初始化的时候，
        实现对于每一个编号的格子，它知道它们的位置以及类型信息。
        这个需要在构造函数中实现
        update: 这项功能转移到ask类里了。

        它是从属于每一个飞机的一个内部类，所以它理所当然地需要知道这个飞机的颜色。

        这个类要实现一个很牛逼的功能：
        我们把骰子的点数传进去，它可以决定我们将要走到哪里，并返回一个位置编号。



    */
    public:
    //ask& chatGPT;

    int color_of_plane;
    int pos_now;//以id的形式表达
    int direction;//方向

    //移动函数
    int move_func(int dice_num);


    /*
        高阶功能
        涉及颜色托管以及路径翻转
    */

    //构造函数
    plane_list();
};

#endif // STRUCTURES_H