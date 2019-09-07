#include "EightBlock.h"
#include "ui_EightBlock.h"
#include"MAIN_Operate.h"
#include<QTimer>
#include<vector>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(750,750);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int  MainWindow::hx(int blk8[][3])//计算x状态到目标状态的估计距离
{
    int h = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            h += abs(blk0[blk8[i][j]].x - i) + abs(blk0[blk8[i][j]].y - j);
    return int(h);
}

string MainWindow:: key(int blk8[][3])
{
    string key_value = " ";
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            key_value += to_string(blk8[i][j]);
    return key_value;
}

void MainWindow::Setgoalstatus (Block goal_blk)
{
   for(int i=0;i<9;i++)
   {
       blk0[goal_blk.blk[i/3][i%3]].x=i/3;
       blk0[goal_blk.blk[i/3][i%3]].y=i%3;
   }
}
void MainWindow::Traceback(Block b,int step)
{
    path.push(b);
    if (step == -1)
        return;
    vector<Block>::iterator iter;
    for (iter = adjv[step].begin(); iter < adjv[step].end();iter++)
    {
        Block u = *iter;
        if (b.pre == key(u.blk))
            Traceback(u, step - 1);
    }
}

void MainWindow::SetColor0_8(int num,QLabel *l)
{
    switch (num) {
    case 1:
        l->setStyleSheet("background-color: rgb(170, 0, 0);");break;
    case 2:
       l->setStyleSheet("background-color: rgb(0,170, 0);");break;
    case 3:
       l->setStyleSheet("background-color: rgb(170, 85, 255);");break;
    case 4:
       l->setStyleSheet("background-color: rgb(85, 0, 127);"); break;
    case 5:
       l->setStyleSheet("background-color: rgb(0,85, 255);");  break;
    case 6:
        l->setStyleSheet("background-color: rgb(255, 85, 0);");  break;
    case 7:
        l->setStyleSheet("background-color: rgb(255, 255, 0);");  break;
    case 8:
        l->setStyleSheet("background-color: rgb(170, 85, 127);");  break;
    case 0:
        l->setStyleSheet("background-color: rgb(255, 255, 255);");  break;
    }

}

void MainWindow::print(int blk[][3])
{
    ui->label->setNum(blk[0][0]);SetColor0_8(blk[0][0],ui->label);
    ui->label_2->setNum(blk[0][1]);SetColor0_8(blk[0][1], ui->label_2);
    ui->label_3->setNum(blk[0][2]);SetColor0_8(blk[0][2], ui->label_3);
    ui->label_4->setNum(blk[1][0]);SetColor0_8(blk[1][0], ui->label_4);
    ui->label_5->setNum(blk[1][1]);SetColor0_8(blk[1][1], ui->label_5);
    ui->label_6->setNum(blk[1][2]);SetColor0_8(blk[1][2], ui->label_6);
    ui->label_7->setNum(blk[2][0]);SetColor0_8(blk[2][0], ui->label_7);
    ui->label_8->setNum(blk[2][1]);SetColor0_8(blk[2][1], ui->label_8);
    ui->label_9->setNum(blk[2][2]);SetColor0_8(blk[2][2], ui->label_9);
    QEventLoop eventloop;
    QTimer::singleShot(700, &eventloop, SLOT(quit())); //wait 1s
    eventloop.exec();
}

void MainWindow::A_STAR(Block b0,Block goal_blk,int &step1,int &node)
{
    int direction[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} }; //左右上下移动
    priority_queue<Block> pq;
    map<string, int> MAP;
    b0.gx = 0;
    b0.fx = hx(b0.blk) + b0.gx;
    pq.push(b0);
    while (!pq.empty())
    {
        Block now = pq.top();
        adjv[now.step].push_back(now);
        MAP[key(now.blk)] = now.fx;
        pq.pop();
        node++;
        if (hx(now.blk) == 0)
        {
            int  step= now.step;
            step1=now.step;
            goal_blk.pre = adjv[now.step][0].pre;
            Traceback(goal_blk,step-1);
            while (!path.empty())
             {
               Block b = path.top();
               print(b.blk);
               path.pop();
             }
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int posx = now.x + direction[i][0];
            int posy = now.y + direction[i][1];
            if (posx < 0 || posx > 2 || posy > 2 || posy < 0)
                continue;
            Block b = now;
            b.blk[now.x][now.y] = b.blk[posx][posy];

            b.blk[posx][posy] = 0; //将now.blk的0和其中相邻的一个数进行交换
            b.x = posx;
            b.y = posy; //b中0的横纵坐标
            b.gx++;     //实际代价加一
            b.fx = hx(b.blk) + b.gx;

            b.step = now.step + 1;
            b.pre = key(now.blk);
            if (MAP[key(b.blk)] == 0)
            {
                pq.push(b);

            }
        }
    }
}


