#ifndef STACK_WIDGET_ONE_H
#define STACK_WIDGET_ONE_H

#include "mainwindow.h"
#include <QPushButton>


class stack_widget_one : QTabWidget
{
public:
    stack_widget_one();
    app_data* my_app_data;
    QTabWidget* tab_wid;
    QPushButton* suji;

};

#endif // STACK_WIDGET_ONE_H
