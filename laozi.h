#ifndef LAOZI_H
#define LAOZI_H
#include"mainwindow.h"

class app_data;
class QLineEdit;
class laozi_lab;
//老子界面类
class laozi_widget:public QWidget
{
    Q_OBJECT
public:
    laozi_widget(QWidget* p = 0);
    QLineEdit * max;
    QLineEdit *min;  //获取道德经章数区间
    QLineEdit * equal;   //需要获取某几张道德经
    QLineEdit * not_equal;   //不需要获取某几张道德经
    QLabel * hint_max_min;   //道德经区间的提示文本
    QLabel * hint_equal;   //需要某几章道德经的提示文本
    QLabel * hint_not_equal;   //不需要某几章道德经的提示文本
    QPixmap wen;//按钮图片
    QPixmap gou;//按钮图片
    QPixmap cha;//按钮图片
    QLineEdit* appoint_num; //生成指点单章的单行编辑

    QFile *config_file;//配置文件

    int read_sum = 0; // 当前 显示的道德经
    laozi_lab * txt;    //道德经显示
    QMap<int, QQueue<QString>> laozi_data;    //保存老子数据
    QQueue<QString>  one_laozi_data;
    QPushButton * tihui;    //体会按钮
    app_data * my_app_data;

    ~laozi_widget();

public slots:
    static void thr_text_edited();  // 文本框 发生变化会调用这个槽函数，调用子线程

signals:
    void sig_thr_text_edited();
};

//老子 内容显示 重写 鼠标释放事件
class laozi_lab: public QLabel
{
public:
    laozi_lab(QWidget* p = 0);

private:
    void mouseReleaseEvent(QMouseEvent *);
    app_data * my_app_data;
};

//多线程，追踪文本框变化
class line_edit_thr :public QObject
{
    Q_OBJECT
public:
    line_edit_thr(QObject* p = 0);
public slots:
    void run_1();
    void delete_this();
private:
    app_data* my_app_data;
};

//文本框 输入提示 信息，重写按下和释放事件
class hint_lab:public QWidget
{
public:
    hint_lab(QWidget*p =0);

private:
    void mousePressEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // LAOZI_H
