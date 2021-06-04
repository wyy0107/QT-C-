#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "game.h"
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <math.h>
#include <QTimer>
#include <QPushButton>
#include <QtGui>
#include<QFrame>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);

    //设置棋盘大小
    setWindowTitle("六子棋");
    setFixedSize(1160,860);

    //背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/bj/bj1.jpg")));
    setPalette(pal);

    game=new Game;
    timer=new QTimer(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
    delete timer;
}

//绘制函数

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    //绘线
    for(int i=0;i<21;i++)
    {
        //第i条竖线
        painter.drawLine(30+40*i,30,30+40*i,830);
        //第i条横线
        painter.drawLine(30,30+40*i,830,30+40*i);
    }
    //绘鼠标光点
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    if(clickposrow>=0&&clickposrow<=21&&clickposcol>=0&&clickposcol<=21&&game->game_map[clickposrow][clickposcol]==0)
    {
        if(game->game_player)
            brush.setColor(Qt::black);
        else
            brush.setColor(Qt::white);
        painter.setBrush(brush);
        painter.drawEllipse(30+40*clickposrow-4,30+40*clickposcol-4,8,8);
    }
    //绘棋盘棋子
    for(int i=0;i<21;i++)
        for(int j=0;j<21;j++)
        {

            if(game->game_map[i][j]==1)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(30+40*i-18,30+40*j-18,36,36);
            }
            if(game->game_map[i][j]==2)
            {
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(30+40*i-18,30+40*j-18,36,36);
            }
        }
    update();

}

//鼠标监听函数
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    //确定落子的标记
    int x=event->x();
    int y=event->y();
    //边界不落子
    if(x>=20&&x<=840&&y>=20&&y<=840)
    {
        int row=(x-30)/40;
        int col=(y-30)/40;
        int lefttopposx=30+40*row;
        int lefttopposy=30+40*col;
        clickposcol=-1;
        clickposrow=-1;
        selectpos=false;
        int len=0;
        len=sqrt((x-lefttopposx)*(x-lefttopposx)+(y-lefttopposy)*(y-lefttopposy));
        if(len<20)
        {
            clickposcol=col;
            clickposrow=row;
            if(game->game_map[clickposrow][clickposcol]==0)
            {
                selectpos=true;
            }
        }
        len=sqrt((x-lefttopposx-40)*(x-lefttopposx-40)+(y-lefttopposy)*(y-lefttopposy));
        if(len<20)
        {
            clickposcol=col;
            clickposrow=row+1;
            if(game->game_map[clickposrow][clickposcol]==0)
            {
                selectpos=true;
            }
        }
       len=sqrt((x-lefttopposx)*(x-lefttopposx)+(y-lefttopposy-40)*(y-lefttopposy-40));
        if(len<20)
        {
            clickposcol=col+1;
            clickposrow=row;
            if(game->game_map[clickposrow][clickposcol]==0)
            {
                selectpos=true;
            }
        }
        len=sqrt((x-lefttopposx-40)*(x-lefttopposx-40)+(y-lefttopposy-40)*(y-lefttopposy-40));
        if(len<20)
        {
            clickposcol=col+1;
            clickposrow=row+1;
            if(game->game_map[clickposrow][clickposcol]==0)
            {
                selectpos=true;
            }
        }
        update();
    }
}
//落子函数
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(selectpos==false)
        return;
    else
        selectpos=false;

    if(game->gametype==PERSON)
        chessbyperson();

    if(game->gametype==AA)
        chessbyAI();
    if(game->gametype==AI)
    {
        chessbyperson();
        QTimer::singleShot(500,this,SLOT(chessbyAI()));
    }
}

void MainWindow::chessbyperson()
{
    if(clickposcol!=-1&&clickposrow!=-1&& game->game_map[clickposrow][clickposcol]==0)
    {
        //改变数组
        game->actionbyperson(clickposrow,clickposcol);
        //判断输赢
        winandend();

        update();
    }
}
void MainWindow::chessbyAI()
{
    game->actionbyAI(clickposrow,clickposcol);
    winandend();
    update();
}

void MainWindow::winandend()
{
    bool win=game->pdwin(clickposrow,clickposcol);
    bool jinshou=game->pdjinshou(clickposrow,clickposcol);
    bool heqi=game->pdheqi();
    if(win==true&&game->gamestatus==playing)
    {
        game->gamestatus=WIN;
        QString str;
        if(game->game_map[clickposrow][clickposcol]==1)
            str="黑棋胜利 ! ";
        else
            str="白棋胜利 ! ";
        QMessageBox::StandardButton btuValue=QMessageBox::information(this,"结果",str);
        //重置游戏
        if(btuValue==QMessageBox::Ok)
            gameupdate();
    }
    if(jinshou==true&&game->gamestatus==playing&&win==false)
    {
        game->gamestatus=WIN;
        QString str="黑棋禁手 白棋胜利 ! ";
        QMessageBox::StandardButton btuValue=QMessageBox::information(this,"结果",str);
        //重置游戏
        if(btuValue==QMessageBox::Ok)
            gameupdate();
    }
    if(win==false&&heqi==true)
    {
        game->gamestatus=HEQI;
        QString str=" 和棋  ! ";
        QMessageBox::StandardButton btuValue=QMessageBox::information(this,"结果",str);
        //重置游戏
        if(btuValue==QMessageBox::Ok)
            gameupdate();
    }
    if(!(win==false&&heqi==false&&jinshou==false))
        timer->stop();
}
//重置游戏
void MainWindow::gameupdate()
{
    game->startgame(gametype);
    game->gamestatus=playing;
}

void MainWindow::on_pushButton_clicked()
{
    timer->stop();
    game->Game::setppGame();
}


void MainWindow::on_pushButton_2_clicked()
{
    timer->stop();
    game->Game::setaiGame();
}


void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
    delete timer;

    game->Game::setaaGame();
    if(game->gametype==AA)
    {
    if(game->game_map[10][10]==0)
        game->updatemap(10,10);
    timer=new QTimer(this);
    timer->start();
    timer->setInterval(300);
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
    }
    else
        timer->stop();
    a=true;

}

void MainWindow::on_timer_timeout()
{
    chessbyAI();
}

void MainWindow::on_pushButton_5_clicked()
{
    if(a==true)
        timer->stop();
    if(a==false&&game->gametype==AA)
    {
        timer->start();
    }
    a=!a;
}


