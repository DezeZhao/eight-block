#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<map>
#include<queue>
#include<iostream>
#include<QLabel>
#include<string>
#include<stack>
using namespace  std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    struct Block
    {
        int x, y, fx, gx,step;//x,y分别是block 中数的横纵坐标,fx是启发式函数,gx是起始状态到x状态的实际代价函数
        int blk[3][3];
        string pre;
        bool operator<(const Block &b) const { return fx > b.fx; }
    };
    map<int, Block> blk0; //存目标状态
    vector<Block> adjv[100];
    stack<Block>path;
    int hx(int blk8[][3]);//计算x状态到目标状态的估计距离
    string key(int blk8[][3]);
    void Traceback(Block b,int step);
    void Setgoalstatus (Block goal_blk);
    void SetColor0_8(int num,QLabel *l);
    void print(int blk[][3]);
    void A_STAR(Block b0,Block goal_blk,int &step,int&node);
    Ui::MainWindow *ui;
private slots:

private:

};

#endif // MAINWINDOW_H
