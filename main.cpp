#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*
    问题积累1：
        相同用法的控件还是应该用数组，循环初始化
        可以减少代码量，后期修改位置容易
    问题积累2：
        尝试不要基于界面大小写控件，应该试试基于上级控件大小写控件
*/

