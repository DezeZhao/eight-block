#include "prompt.h"
#include "ui_prompt.h"

prompt::prompt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::prompt)
{
    ui->setupUi(this);
    this->setFixedSize(800,550);
}

prompt::~prompt()
{
    delete ui;
}

void prompt::on_pushButton_clicked()
{
    close();
}
