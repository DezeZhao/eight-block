#ifndef OPWINDOW_H
#define OPWINDOW_H

#include <QMainWindow>
#include "EightBlock.h"

namespace Ui {
class OpWindow;
}

class OpWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpWindow(QWidget *parent = nullptr);
    ~OpWindow();
    QString str1 ,str2;

    int cnt1 = 0, cnt2 = 0;
    MainWindow::Block start_blk;
    MainWindow::Block goal_blk ;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::OpWindow *ui;
};

#endif // OPWINDOW_H
