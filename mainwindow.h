#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStackedWidget>
#include <qwidget.h>
#include<QGuiApplication>
#include<QRect>
#include<QScreen>
#include<app_data.h>
#include<qdebug.h>
#include<qstring.h>
#include"stack_widget_one.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
