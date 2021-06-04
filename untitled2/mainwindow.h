#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool a=true;

private:
    Ui::MainWindow *ui;
    //关联到game类
    Game *game;//游戏指针
    Gametype gametype;//存储游戏类型

    //绘制函数
    void paintEvent(QPaintEvent *event);

    //初始化函数

    //鼠标监听函数
    void mouseMoveEvent(QMouseEvent *event);
    int clickposrow,clickposcol;//存储将点击的位置
    bool selectpos=false;//判断是否移动到合适位置，以选中某个交叉点
    //落子函数
    void mouseReleaseEvent(QMouseEvent *event);
    void chessbyperson();

    //判断输赢，并调出结束界面
    void winandend();
    //重置游戏
    void gameupdate();
    void huiqi();
    QTimer *timer;
private slots:
    void chessbyAI();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_timer_timeout();
    void on_pushButton_5_clicked();
};
#endif // MAINWINDOW_H
