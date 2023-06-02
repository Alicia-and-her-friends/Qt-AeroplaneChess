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
    bool isGoalState(int color, int id_x){
        return id_x==GoalState[color];
    }


    //构造函数
    ask();
};

#endif // STRUCTURES_H