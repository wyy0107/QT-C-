#include "game.h"
#include "mainwindow.h"
#include <time.h>
#include <stdlib.h>

Game::Game()
{

}
void Game::setppGame()
{
    gametype=PERSON;
    gamestatus=playing;
    startgame(gametype);
}
void Game::setaaGame()
{
    gametype=AA;
    gamestatus=playing;
    startgame(gametype);

}

void Game::setaiGame()
{
    gametype=AI;
    gamestatus=playing;
    startgame(gametype);
}

void Game::startgame(Gametype type)
{
    clearmap();//清空game_map数组
    game_player=true;//player设为黑子
    if(type==AI||type==AA)
    {
        clearscore();//清空game_score数组
    }

}

void Game::clearmap()
{
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
            game_map[i][j]=0;
}

void Game::clearscore()
{
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
            game_score[i][j]=0;
}
//落子
void Game::actionbyperson(int a, int b)
{
    updatemap(a,b);
}

void Game::updatemap(int a, int b)
{
    if(game_player==1 )
        game_map[a][b]=1;
    else
        game_map[a][b]=2;
    //换手
    game_player=!game_player;

}

//判断是否赢棋
//分别向八个方向辨别6（5）步
bool Game::pdwin(int a, int b)
{
    int k=0;
    //水平方向
    //向右
    if(a==-1&&b==-1)
        return false;
    for(int i=0;i<6;i++)
    {
        if(a+i<21)//是否还在棋盘内
        {
            if(game_map[a][b]==game_map[a+i][b])//与落下的子相同
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    //向左
    for(int i=1;i<6;i++)
    {
        if(a-i>0)
        {
            if(game_map[a][b]==game_map[a-i][b])
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    //竖直方向
    k=0;
    //向下
    for(int i=0;i<6;i++)
    {
        if(b+i<21)
        {
            if(game_map[a][b]==game_map[a][b+i])
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    //向上
    for(int i=1;i<6;i++)
    {
        if(b-i>0)
        {
            if(game_map[a][b]==game_map[a][b-i])
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    //'/'斜
    k=0;
    //右上
    for(int i=0;i<6;i++)
    {
        if(a+i<21&&b-i>0)
        {
            if(game_map[a+i][b-i]==game_map[a][b])
                k++;
            else
                break;
        }
        else
            break;
    }
    //左下
    for(int i=1;i<6;i++)
    {
        if(a-i>0&&b+i<21)
        {
            if(game_map[a-i][b+i]==game_map[a][b])
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    //'\'斜
    k=0;
    //右下
    for(int i=0;i<6;i++)
    {
        if(a+i<21&&b+i<21)
        {
            if(game_map[a+i][b+i]==game_map[a][b])
                k++;
            else
                break;
        }
        else
            break;
    }
    //左上
    for(int i=1;i<6;i++)
    {
        if(a-i>0&&b-i>0)
        {
            if(game_map[a-i][b-i]==game_map[a][b])
                k++;
            else
                break;
        }
        else
            break;
    }
    if(k>=6)
        return true;
    return false;
}
//判断是否和棋
bool Game::pdheqi()
{

    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
            if(game_map[i][j]==0)
                return false;

    return true;
}
//四四禁手和五五禁手
bool Game::pdjinshou(int a, int b)
{
    int num=0;//活四/活五的数量
    int k=0;//每一个方向连续的黑子数
    int q=0;//尾端是否是活棋
    //水平方向
    //向右
    for(int i=0;i<6;i++)
    {
        if(a+i<=21)
        {
            if(game_map[a+i][b]==1)
                k++;
            if(game_map[a+i][b]==2)
            {
                q++;
                break;
            }
            if(game_map[a+i][b]==0)
                break;
        }
        else break;
    }

    //向左
    for(int i=1;i<6;i++)
    {
        if(a-i>0)
        {
            if(game_map[a-i][b]==1)
                k++;
            if(game_map[a-i][b]==2)
            {
                q++;
                break;
            }
            if(game_map[a-i][b]==0)
                break;
        }
        else break;
    }
    if(k>=4&&q<2)
        num+=1;
    if(num>=2)
        return true;

    //竖直方向
    //向下
    k=0;q=0;
    for(int i=0;i<6;i++)
    {
        if(b+i<21)
        {
            if(game_map[a][b+i]==1)
                k++;
            if(game_map[a][b+i]==2)
            {
                q++;
                break;
            }
            if(game_map[a][b+i]==0)
            {
                break;
            }
        }
        else break;
    }

    //向上
    for(int i=1;i<6;i++)
    {
        if(b-i>0)
        {
            if(game_map[a][b-i]==1)
                k++;
            if(game_map[a][b-i]==2)
            {
                q++;
                break;
            }
            if(game_map[a][b-i]==0)
                break;
        }
        else break;
    }

    if(k>=4&&q<2)
        num++;

    if(num>=2)
        return true;

    //'\'斜
    k=0;q=0;
    //向右下
    for(int i=0;i<6;i++)
    {
        if(b+i<21&&a+i<21)
        {
            if(game_map[a+i][b+i]==1)
                k++;
            if(game_map[a+i][b+i]==2)
            {
                q++;
                break;
            }
            if(game_map[a+i][b+i]==0)
                break;
        }
        else break;
    }

    //向左上
    for(int i=1;i<6;i++)
    {
        if(a-i>0&&b-i>0)
        {
            if(game_map[a-i][b-i]==1)
                k++;
            if(game_map[a-i][b-i]==2)
            {
                q++;
                break;
            }
            if(game_map[a-i][b-i]==0)
                break;
        }
        else break;
    }
    if(k>=4&&q<2)
        num++;
    if(num>=2)
        return true;

    //'/'斜
    k=0;q=0;
    //向坐下
    for(int i=0;i<6;i++)
    {
        if(a-i>0&&b+i<21)
        {
            if(game_map[a-i][b+i]==1)
                k++;
            if(game_map[a-i][b+i]==2)
            {
                q++;
                break;
            }
            if(game_map[a-i][b+i]==0)
                break;
        }
        else break;
    }

    //向右上
    for(int i=1;i<6;i++)
    {
        if(a+i<21&&b-i>0)
        {
            if(game_map[a+i][b-i]==1)
                k++;
            if(game_map[a+i][b-i]==2)
            {
                q++;
                break;
            }
            if(game_map[a+i][b-i]==0)
                break;
        }
        else break;
    }
    if(k>=4&&q<2)
        num++;
    if(num>=2)
        return true;

    return false;
}

//ai落子
void Game::actionbyAI(int &a,int &b)
{
    getscore();
    int max=0;
    int i=0;
    int maxpos[2][21*21];
    for(int row=0;row<21;row++)
        for(int col=0;col<21;col++)
        {
            if(game_map[row][col]==0)
                if(game_score[row][col]>max)
                {
                    max=game_score[row][col];
                }
        }

    for(int row=0;row<21;row++)
        for(int col=0;col<21;col++)
        {
            if(game_score[row][col]==max&&game_map[row][col]==0)
            {
                maxpos[0][i]=row;
                maxpos[1][i]=col;
                i++;
            }
        }
    int n=rand()%i;
    a=maxpos[0][n];
    b=maxpos[1][n];
    updatemap(a,b);
}
void Game::getscore()
{
    clearscore();
    int player1=0;
    int player2=0;
    int empty=0;
    for(int row=0;row<21;row++)
        for(int col=0;col<21;col++)
        {
            if(game_map[row][col]==0)
            {
                for(int x=-1;x<=1;x++)
                    for(int y=-1;y<=1;y++)
                    {
                        player1=0;
                        player2=0;
                        empty=0;
                        if(!(x==0&&y==0))
                        {
                            for(int i=0;i<6;i++)
                            {
                                if(row+i*y>=0&&row+i*y<=21&&col+i*x>=0&&col+i*x<=21)
                                {
                                    if(game_map[row+i*y][col+i*x]==1)
                                        player1++;
                                    if(game_map[row+i*y][col+i*x]==0)
                                    {
                                        empty++;
                                        break;
                                    }
                                    if(game_map[row+i*y][col+i*x]==2)
                                        break;
                                }
                                else
                                    break;
                            }
                            for(int i=1;i<6;i++)
                            {
                                if(row-i*y>=0&&row-i*y<=21&&col-i*x>=0&&col-i*x<=21)
                                {
                                    if(game_map[row-i*y][col-i*x]==1)
                                        player1++;
                                    if(game_map[row-i*y][col-i*x]==0)
                                    {
                                        empty++;
                                        break;
                                    }
                                    if(game_map[row-i*y][col-i*x]==2)
                                        break;
                                }
                                else
                                    break;
                            }
                            if(player1==1)
                                game_score[row][col]+=10;
                            if(player1==2)
                            {
                                if(empty==1)
                                    game_score[row][col]+=30;
                                if(empty==2)
                                    game_score[row][col]+=40;
                            }
                            if(player1==3)
                            {
                                if(empty==1)
                                    game_score[row][col]+=60;
                                if(empty==2)
                                    game_score[row][col]+=110;
                            }
                            if(player1==4)
                            {
                                if(empty==1)
                                    game_score[row][col]+=300;
                                if(empty==2)
                                    game_score[row][col]+=500;
                            }
                            if(player1==5)
                                game_score[row][col]+=1200;
                            empty=0;
                            for(int i=0;i<6;i++)
                            {
                                if(row+i*y>=0&&row+i*y<=21&&col+i*x>=0&&col+i*x<=21)
                                {
                                    if(game_map[row+i*y][col+i*x]==2)
                                        player2++;
                                    if(game_map[row+i*y][col+i*x]==0)
                                    {
                                        empty++;
                                        break;
                                    }
                                    if(game_map[row+i*y][col+i*x]==1)
                                        break;
                                }
                                else
                                    break;
                            }

                            for(int i=1;i<6;i++)
                            {
                                if(row-i*y>=0&&row-i*y<=21&&col-i*x>=0&&col-i*x<=21)
                                {
                                    if(game_map[row-i*y][col-i*x]==2)
                                        player2++;
                                    if(game_map[row-i*y][col-i*x]==0)
                                    {
                                        empty++;
                                        break;
                                    }
                                    if(game_map[row-i*y][col-i*x]==1)
                                        break;
                                }
                                else
                                    break;
                            }
                            if(player2==1)
                                game_score[row][col]+=10;
                            else if(player2==2)
                            {
                                if(empty==1)
                                    game_score[row][col]+=30;
                                if(empty==2)
                                    game_score[row][col]+=40;
                            }
                            else if(player2==3)
                            {
                                if(empty==1)
                                    game_score[row][col]+=60;
                                if(empty==2)
                                    game_score[row][col]+=110;
                            }
                            else if(player2==4)
                            {
                                if(empty==1)
                                    game_score[row][col]+=300;
                                if(empty==2)
                                    game_score[row][col]+=500;
                            }
                            else if(player2==5)
                                game_score[row][col]+=1500;
                        }
                    }
            }
            else
                game_score[row][col]=0;
        }
}
