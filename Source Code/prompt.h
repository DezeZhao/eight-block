#ifndef PROMPT_H
#define PROMPT_H

#include <QMainWindow>

namespace Ui {
class prompt;
}

class prompt : public QMainWindow
{
    Q_OBJECT

public:
    explicit prompt(QWidget *parent = nullptr);
    ~prompt();

private slots:
    void on_pushButton_clicked();

private:
    Ui::prompt *ui;
};

#endif // PROMPT_H
