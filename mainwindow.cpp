#include "mainwindow.h"

app_data* my_app_data;

QWidget * my_this;

QStackedWidget* stacked;

//初始化界面宽高属性
void init_width_height()
{
    //获取当前屏幕分辨率
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;

#ifdef ANDROID
    my_app_data->width_ture = mm.width();
    my_app_data->height_ture = mm.height();
    my_app_data->width = (float)my_app_data->width_ture / 100.00f;
    my_app_data->height =  (float)my_app_data->height_ture / 100.00f;
    my_this->setWhatsThis("zxc");
    my_this->resize(my_app_data->width_ture,my_app_data->height_ture);
    return;
#endif

    my_app_data->width_ture = mm.height() / 2;
    my_app_data->width = (float)my_app_data->width_ture / 100.00f;
    my_app_data->height_ture =  mm.width()/2 - (int)(mm.width()/2*0.2);
    my_app_data->height =  (float)my_app_data->height_ture / 100.00f;
    my_this->setWhatsThis("zxc");
    my_this->resize(my_app_data->width_ture,my_app_data->height_ture);

    //    qDebug()<<my_app_data->height_ture;
    //    qDebug()<<my_app_data->width_ture;
    //    qDebug()<<my_app_data->height;
    //    qDebug()<<my_app_data->width;
}

//初始化栈容器
void init_stacked()
{

    //创建栈容器
    stacked = new QStackedWidget(my_this);
    stacked->move(0,0);
    stacked->resize(my_app_data->width_ture,my_app_data->height*92);

    stack_widget_one* my_stack_widget_one = new stack_widget_one();

    stacked->addWidget((QTabWidget*)my_stack_widget_one);

    //添加栈容器第一个页面
    //init_stacked_one();

//    //添加栈容器第二个页面
//    my_ui->laozi_widget = new laozi_widget(my_this);
//    my_ui->stacked->addWidget(my_ui->laozi_widget);


//    //添加栈容器第三个页面
//    my_ui->user_account = new user_account_widget(my_this);
//    my_ui->stacked->addWidget(my_ui->user_account);

//    //添加栈容器第四个页面
//    my_ui->my_widget = new my_widget(my_this);
//    my_ui->stacked->addWidget(my_ui->my_widget);


}


MainWindow::MainWindow (QWidget *parent)
    : QMainWindow(parent)
{
    my_app_data = app_data::get_app_data();
    my_this = this;

    init_width_height();



    init_stacked();

}

MainWindow::~MainWindow()
{
}

