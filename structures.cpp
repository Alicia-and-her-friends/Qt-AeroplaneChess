#include "structures.h"

#define ZoneI 1
#define ZoneII 2
#define ZoneIII 3

#define Green 1
#define Yellow 2
#define Blue 3
#define Red 4

/*
    采用打表方式暴力解决路径问题
    打表部分已解决
*/
ask::ask(){
    /*
        第一层覆盖：基础覆盖
    */
    for(int color=1;color<=4;color++){
        for(int id_now=1;id_now<=52;id_now++){
            //0:正向, 1:反向
            Next[color][id_now][0]=(id_now%52)+1;
            Next[color][id_now][1]=(id_now-1);
            if(Next[color][id_now][1]==0)Next[color][id_now][1]=52;
            squares[id_now].color=(id_now-1)%4;
            squares[id_now].type=ZoneII;
            if(squares[id_now].color==0)squares[id_now].color=4;

        }
    }
    for(int color=1;color<=4;color++){
        for(int i=1;i<=280;i++){
            jump[color][i][0]=i;
            jump[color][i][1]=i;
        }
    }
    /*
        第二层覆盖：跳跃覆盖
    */
    //+4覆盖
    for(int id_now=1;id_now<=52;id_now++){
        jump[squares[id_now].color][id_now][0]=(id_now+4)%52;
        jump[squares[id_now].color][id_now][1]=(id_now-4)%52;
        if(jump[squares[id_now].color][id_now][0]==0)jump[squares[id_now].color][id_now][0]=52;
    }
    //+12覆盖
    jump[Green][18][0]=30;jump[Green][30][1]=18;
    jump[Yellow][31][0]=43;jump[Yellow][43][1]=31;
    jump[Blue][44][0]=4;jump[Blue][4][1]=44;
    jump[Red][5][0]=17;jump[Red][17][1]=5;

    /*
        第三层覆盖：转折点覆盖
    */
    Next[Green][50][0]=61;
    Next[Yellow][11][0]=71;
    Next[Blue][24][0]=81;
    Next[Red][37][0]=91;

    /*
        建立起点与棋盘链接
    */
    for(int i=101;i<=104;i++)squares[i].type=ZoneI;
    Next[Green][101][0]=1;
    Next[Yellow][102][0]=14;
    Next[Blue][103][0]=27;
    Next[Red][104][0]=40;

    /*
        建立终点循环区的循环连接
    */
    for(int i=6;i<=9;i++){
        for(int j=1;j<=6;j++){
            for(int color=1;color<=4;color++){
                Next[color][i*10+j][0]=i*10+(j%6)+1;
                Next[color][i*10+j][1]=i*10+(j%6)-1;
                if(j%6==0){Next[color][i*10+j][1]=i*10+6;}
            }
        }
    }
    /*
        建立机场与起点连接
    */
    for(int col=1;col<=4;col++){
        for(int j=1;j<=16;j++){
            Next[col][200+(col-1)*20+j][0]=100+col;
            Next[col][200+(col-1)*20+j][1]=100+col;
        }
    }
    /*
        reset部分打表
    */
    for(int i=1;i<=4;i++){
        for(int j=1;j<=16;j++){
            Reset[i][j]=200+(i-1)*20+j;
        }
    }


    /*
        GoalState部分打表
    */
    GoalState[Green]=66;
    GoalState[Yellow]=76;
    GoalState[Blue]=86;
    GoalState[Red]=96;

    //打表部分down

}

square ask::ask_for_info(int square_id){
    return squares[square_id];
}

int ask::next_pos(int color, int id_now, int dir){
    return Next[color][id_now][dir];
}

int ask::res_pos(int color, int tot){
    return Reset[color][tot];
}

int ask::jump_pos(int color, int id_now, int dir){
    return jump[color][id_now][dir];
}
bool ask::isGoalState(int color, int pos_x){
    return pos_x==GoalState[color];
}

/*
class node{
public:
    int current_round;
    int type;//type如果归零，意味着万事皆可行
    /*
        0,1 骰子（0），飞机回合（1）
        2 预设骰子点数（按一次就行）
        3 改变骰子投掷次数（按一次就行）
        4 减速器（后继还需要按一个飞机）
        5 反向移动（后继还需要按一个飞机）
        6 加速器（后继还需要按一个飞机）
        7 交换位置（后续需要按两个飞机）
        8 颜色托管（后续还需要选一个颜色）
//可以再增加一个取消按钮
    int step;

    int color_fixed;
//0: NO
//1, 2, 3, 4

//判断是否可行
    bool avail(int x);
    void changeState(int x);

    void reset();
    node();
    node(int cr_,int tp_, int cf_);
};
*/
void node::change_current_round(){
    current_round^=1;
}
void node::changeState(int x){
    type=x;
    tot_swap=0;
}
bool node::avail_prop(int x){
    //this Func is for 道具
    if(type>1){
        return false;
    }
    return true;
}
bool node::avail_dice(){
    if(type<=1)return true;
    return false;
}
bool node::avail_plane(int color){
    if(tot_swap>=1&&type!=7){
        return false;
    }
    if(type==8&&color==color_fixed){
        return false;
    }
    return true;
}
void node::reset(){
    tot_swap=0;
    type=current_round;
}
node::node(){

}
node::node(int cr_,int tp_,int cf_):current_round(cr_),type(tp_),color_fixed(cf_){
    step=0;tot_swap=0;
}
