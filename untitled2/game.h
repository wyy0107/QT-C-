#ifndef GAME_H
#define GAME_H

//游戏类型
enum Gametype{ PERSON,AI,AA };

//status
enum Gamestatus{ playing,WIN,HEQI };

class Game
{
public:

    Game();

    //储存棋盘、棋子，空：0，黑：1，白：2
    int game_map[21][21];

    //储存各个点的分值
    int game_score[21][21];

    //储存下棋方，黑：true,白:false
    bool game_player=true;

    Gamestatus gamestatus;
    Gametype gametype;

    void startgame(Gametype type);
    void clearmap();
    void clearscore();
    //落子
    void actionbyperson(int a,int b);
    void actionbyAI(int &a,int &b);
    void updatemap(int a,int b);
    //判断棋局
    bool pdwin(int a,int b);
    bool pdheqi();
    bool pdjinshou(int a,int b);
    //ai下棋计分函数
    void getscore();
    //设置游戏类型并开始游戏
    void setppGame();//双人模式
    void setaiGame();//人机模式
    void setaaGame();//AI对战

};

#endif // GAME_H
