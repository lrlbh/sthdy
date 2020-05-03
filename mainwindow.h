#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include<qmap.h>
#include<QApplication>
#include<QStackedWidget>
#include <qwidget.h>
#include<QGuiApplication>
#include<QRect>
#include<QScreen>
#include<qlabel.h>
#include<qdebug.h>
#include<qstring.h>
#include<QClipboard>
#include<qpushbutton.h>
#include"zhouyi.h"
#include"app_data.h"
#include<QThread>
#include <QPropertyAnimation>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include<qqueue.h>
#include <QTimer>
#include<QMouseEvent>
#include<QGraphicsOpacityEffect>
#include<QTabWidget>
#include"laozi.h"
#include<QInputDialog>
#include<QTextCodec>
#include<QLineEdit>
#include<qmap.h>
#include<qlist.h>
#include<qstring.h>
#include<qvector.h>
#include<QTime>
#include<QBitmap>
#include<QThread>
#include<QLineEdit>
#include<qobject.h>
#include<qprocess.h>
#include<string.h>
#include<QTextCodec>

#define PB_NUM 2
class app_data;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    app_data* my_app_data;

    QStackedWidget* stacked;    //栈容器
    QPushButton * zhouyi;   //按钮周易
    QPushButton * laozi;    //按钮老子
    QStackedWidget* andorid_temp;   //安卓端状态栏底色填充

private:
    void init_width_height();   //初始化不同平台下的页面宽高属性
    void init_stacked();    //初始化栈容器
    void init_push_button();    //初始化主页面切换栈容器的按钮
    void paintEvent(QPaintEvent *); //重写绘图事件
    void init_clarity();   //初始化透明度

};
#endif // MAINWINDOW_H
