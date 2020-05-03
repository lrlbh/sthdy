#ifndef APP_DATA_H
#define APP_DATA_H

#include"mainwindow.h"


class app_data
{
public:


    int height_ture = 0;
    int width_ture = 0;
    float height = 0;
    float width =0;

    //复制，粘贴对象
    QClipboard *Copy_Paste;

    //主窗口对象
    QWidget* main_widget;

    //保存周易信息
    QMap<int,QList<QString>> zhouyi_txt;

    static app_data* get_app_data();

private:
        app_data();
        app_data(const app_data& app_data);
        static app_data* my_app_data;

};

#endif // APP_DATA_H
