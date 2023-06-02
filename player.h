#ifndef PLAYER_H
#define PLAYER_H

class player{
    public:
    /*
        以id的形式保存当前所有的飞机。
    */
    int color;
    int tot_plane;
    int plane_id[17];
    int score;
    
    //构造函数
    player();
};

#endif // PLAYER_H