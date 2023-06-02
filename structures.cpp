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
    /*
        第二层覆盖：跳跃覆盖
    */
    //+4覆盖
    for(int id_now=1;id_now<=52;id_now++){
        Next[squares[id_now].color][id_now][0]=(id_now+4)%52;
        Next[squares[id_now].color][id_now][0]=(id_now-4)%52;
        if(Next[squares[id_now].color][id_now][0]==0)Next[squares[id_now].color][id_now][0]=52;
    }
    //+12覆盖
    Next[Green][18][0]=30;Next[Green][30][1]=18;
    Next[Yellow][31][0]=43;Next[Yellow][43][1]=31;
    Next[Blue][44][0]=4;Next[Blue][4][1]=44;
    Next[Red][5][0]=17;Next[Red][17][1]=5;

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
        循环区比较特殊，我正在思考我要不要偷懒(嘿嘿，还是选择偷懒了)
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
