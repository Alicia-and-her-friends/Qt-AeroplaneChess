#ifndef SQUARE_H
#define SQUARE_H

class square{
public:
    /*
        id 格点的编号
        x,y 格点对应于Qt界面的坐标
        color 格点的颜色
        type 格点的类型
            I 飞机场
            II 正常环形轨道
            III 胜利者迂回区
    */
    int x,y;
    int id;
    int color;

    int type;

    //构造函数
    square();
};

#endif // SQUARE_H
