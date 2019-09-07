#include"MAIN_Operate.h"
#include <QApplication>
#include<QTimer>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OpWindow op;
    op.show();

    return a.exec() ;
}
