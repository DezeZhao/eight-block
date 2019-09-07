#include "MAIN_Operate.h"
#include"prompt.h"
#include "ui_MAIN_Operate.h"
#include<QString>
#include<QTimer>
using namespace  std;

OpWindow::OpWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OpWindow)
{
    ui->setupUi(this);
    this->setFixedSize(700,900);
    ui->pushButton->setStyleSheet("QPushButton{background-color:rgba(125,178,90);\
          color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
          "QPushButton:hover{background-color:rgb(85, 170, 127); color: black;}"  // 鼠标停放时的色彩
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
   ui->pushButton_2->setStyleSheet("QPushButton{background-color:rgba(125,178,90);\
          color: white;   border-radius: 10px;  border: 2px groove gray; border-style: outset;}" // 按键本色
          "QPushButton:hover{background-color:rgb(85, 170, 127); color: black;}"  // 鼠标停放时的色彩
          "QPushButton:pressed{background-color:rgb(85, 170, 255); border-style: inset; }");
    ui->lineEdit-> setClearButtonEnabled(true);
    ui->lineEdit_2->setClearButtonEnabled(true);
    ui->lineEdit->setPlaceholderText("9位数字，0代表空格，格式如：123456780");
    ui->lineEdit_2->setPlaceholderText("9位数字，0代表空格，格式如：123456780");

}

OpWindow::~OpWindow()
{
    delete ui;
}
void OpWindow::on_pushButton_2_clicked()
{

   str1 = ui->lineEdit->text();
    str1 = str1.remove(QRegExp("\\s"));
   str2 = ui->lineEdit_2->text();
    str2 = str2.remove(QRegExp("\\s"));
    if (str1 != nullptr&&str2!=nullptr)
    {
        QByteArray ba1 = str1.trimmed().toLatin1();
        QByteArray ba2 = str2.trimmed().toLatin1();
        for (int i = 0; i < 9; i++)
        {
            start_blk.blk[i / 3][i % 3] = ba1[i] - '0';
            if (ba1[i] == '0')
            {
                start_blk.x = i / 3;
                start_blk.y = i % 3;
            }
        }
        for (int i = 0; i < 9; i++)
            goal_blk.blk[i / 3][i % 3] = ba2[i] - '0';

         cnt1 = 0; cnt2 = 0;
        for (int i = 0; i < 9; i++)
            for (int j = 0; j <= i; j++)
                if (ba2[j]-'0' != 0 && ba2[i]-'0' != 0)
                    if (ba2[j]>ba2[i])
                        cnt1++;

        for (int i = 0; i < 9; i++)
            for (int j = 0; j <= i; j++)
                if (ba1[j] - '0' != 0 && ba1[i] - '0' != 0)
                    if (ba1[j] > ba1[i])
             cnt2++;
        MainWindow w;
        ui->l00->setNum(start_blk.blk[0][0]);
        ui->l01->setNum(start_blk.blk[0][1]);
        ui->l02->setNum(start_blk.blk[0][2]);
        ui->l10->setNum(start_blk.blk[1][0]);
        ui->l11->setNum(start_blk.blk[1][1]);
        ui->l12->setNum(start_blk.blk[1][2]);
        ui->l20->setNum(start_blk.blk[2][0]);
        ui->l21->setNum(start_blk.blk[2][1]);
        ui->l22->setNum(start_blk.blk[2][2]);
        w.SetColor0_8(start_blk.blk[0][0],ui->l00);
        w.SetColor0_8(start_blk.blk[0][1],ui->l01);
        w.SetColor0_8(start_blk.blk[0][2],ui->l02);
        w.SetColor0_8(start_blk.blk[1][0],ui->l10);
        w.SetColor0_8(start_blk.blk[1][1],ui->l11);
        w.SetColor0_8(start_blk.blk[1][2],ui->l12);
        w.SetColor0_8(start_blk.blk[2][0],ui->l20);
        w.SetColor0_8(start_blk.blk[2][1],ui->l21);
        w.SetColor0_8(start_blk.blk[2][2],ui->l22);


        ui->l00_2->setNum(goal_blk.blk[0][0]);
        ui->l01_2->setNum(goal_blk.blk[0][1]);
        ui->l02_2->setNum(goal_blk.blk[0][2]);
        ui->l10_2->setNum(goal_blk.blk[1][0]);
        ui->l11_2->setNum(goal_blk.blk[1][1]);
        ui->l12_2->setNum(goal_blk.blk[1][2]);
        ui->l20_2->setNum(goal_blk.blk[2][0]);
        ui->l21_2->setNum(goal_blk.blk[2][1]);
        ui->l22_2->setNum(goal_blk.blk[2][2]);
        w.SetColor0_8(goal_blk.blk[0][0],ui->l00_2);
        w.SetColor0_8(goal_blk.blk[0][1],ui->l01_2);
        w.SetColor0_8(goal_blk.blk[0][2],ui->l02_2);
        w.SetColor0_8(goal_blk.blk[1][0],ui->l10_2);
        w.SetColor0_8(goal_blk.blk[1][1],ui->l11_2);
        w.SetColor0_8(goal_blk.blk[1][2],ui->l12_2);
        w.SetColor0_8(goal_blk.blk[2][0],ui->l20_2);
        w.SetColor0_8(goal_blk.blk[2][1],ui->l21_2);
        w.SetColor0_8(goal_blk.blk[2][2],ui->l22_2);

        if (cnt2 % 2 != cnt1 % 2)
        {
            prompt p;
            p.show();
            QEventLoop eventloop;
            QTimer::singleShot(600000, &eventloop, SLOT(quit())); //wait 1s
            eventloop.exec();
        }
    }
    else
       ui->lineEdit->setFocus();
}
void OpWindow::on_pushButton_clicked()
{
  if(str1!=nullptr&&str2!=nullptr)
    {
       if (cnt2 % 2 == cnt1 % 2){
           MainWindow w;
           int step,node=0;
           w.show();
           w.Setgoalstatus(goal_blk);
           start_blk.step=0;
           w.A_STAR(start_blk,goal_blk,step,node);
           QEventLoop eventloop;
           QTimer::singleShot(1000, &eventloop, SLOT(quit())); //wait 1s
           eventloop.exec();
           ui->lineEdit_3->setText(QString::number(step, 10));
           ui->lineEdit_4->setText(QString::number(node, 10));
      }
       else {
           prompt p;
           p.show();
           QEventLoop eventloop;
           QTimer::singleShot(600000, &eventloop, SLOT(quit())); //wait 1s
           eventloop.exec();
       }
  }
  else if(str1==nullptr)
      ui->lineEdit->setFocus();
  else {
      ui->lineEdit_2->setFocus();
  }
}


