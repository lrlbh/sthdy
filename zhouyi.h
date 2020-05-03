#ifndef STACK_WIDGET_ONE_H
#define STACK_WIDGET_ONE_H

#define TAB_WIDGET_NUM 3

#include "mainwindow.h"
#include"app_data.h"
class app_data;

class zhouyi_tab_widget : QTabWidget
{
public:
    zhouyi_tab_widget(QWidget *parent = 0);


    app_data* my_app_data;
    QPushButton* suji;  //获取一挂的按钮

private:
//    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    QVector<int> get_one_gua();
    int get_one_yao();

    //重写鼠标按下和释放事件，实现左右滑动
    int x=0;
    int y=0;



};


class zhouyi_widget : QWidget
{

public:
    zhouyi_widget(QWidget *parent = 0);
    app_data* my_app_data;
    QLabel* gua_name; //展示挂的  名称
    QLabel* gua_img;  //展示挂的  形状
    QLabel* gua_info; //展示挂的  信息

};



class zhouyi_labl : QLabel
{
public:
 //    zhouyi_labl();
    explicit zhouyi_labl(QWidget *parent = 0);
    app_data * my_app_data;

private:

    //重写事件分发处理鼠标按下事件，自定义成双击事件
    bool event(QEvent *e);

    int num = 0;

    //void mouseDoubleClickEvent(QMouseEvent *event); //双击事件
   // void mouseReleaseEvent(QMouseEvent *event); //释放事件，Android平台双击事件不好用这个暂时使用一下
};
#endif // STACK_WIDGET_ONE_H
