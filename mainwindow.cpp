#include "mainwindow.h"


void MainWindow::paintEvent(QPaintEvent *)
{
    //创建画家，指定绘图设备
    QPainter painter(this);
    //创建QPixmap对象
    QPixmap pix;
    //加载图片
    pix.load(":/img/bei_jing.jpg");
    //绘制背景图
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}



//初始化界面宽高属性
void MainWindow::init_width_height()
{
    //获取当前屏幕分辨率
    QScreen *screen=QGuiApplication::primaryScreen ();
    QRect mm=screen->availableGeometry() ;

#ifdef ANDROID
    this->my_app_data->width_ture = mm.width();
    this->my_app_data->height_ture = mm.height();
    this->my_app_data->width = (float)my_app_data->width_ture / 100.00f;
    this->my_app_data->height =  (float)my_app_data->height_ture / 100.00f;
    this->my_app_data->main_widget->setWhatsThis("zxc");
    this->my_app_data->main_widget->resize(my_app_data->width_ture,my_app_data->height_ture);
    return;
#endif

    this->my_app_data->width_ture = mm.height() / 2;
    this->my_app_data->width = (float)my_app_data->width_ture / 100.00f;
    this->my_app_data->height_ture =  mm.width()/2 - (int)(mm.width()/2*0.2);
    this->my_app_data->height =  (float)my_app_data->height_ture / 100.00f;
    this->my_app_data->main_widget->setWhatsThis("zxc");
    this->my_app_data->main_widget->resize(my_app_data->width_ture,my_app_data->height_ture);
}

//初始化栈容器
void MainWindow::init_stacked()
{
    //安卓端，信息栏底色填充
    this->andorid_temp = new QStackedWidget(this);
    this->andorid_temp->resize(my_app_data->width_ture,my_app_data->height*3.1);
    this->andorid_temp->move(0,0);
    this->andorid_temp->addWidget(new QTabWidget(this));



    //创建栈容器
    this->stacked = new QStackedWidget(this);
    this->stacked->move(0,my_app_data->height*3);
    this->stacked->resize(my_app_data->width_ture,my_app_data->height*89);
    //创建第一个页面
    zhouyi_tab_widget* my_stack_widget_one = new zhouyi_tab_widget(this);
    this->stacked->addWidget((QTabWidget*)my_stack_widget_one);

    //创建第二个页面
    laozi_widget * my_laozi = new laozi_widget(this);
    this->stacked->addWidget((QWidget*)my_laozi);
}

//初始化栈容器切换按钮
void MainWindow::init_push_button()
{
    this->zhouyi = new QPushButton(this);
    this->zhouyi->setText("周易速记");
    this->zhouyi->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    this->zhouyi->resize(this->my_app_data->width*(100/PB_NUM),this->my_app_data->height*8);
    this->zhouyi->move(this->my_app_data->width*(100/PB_NUM)*0,this->my_app_data->height*92);
    connect(this->zhouyi,&QPushButton::clicked,this,[=](){
        this->stacked->setCurrentIndex(0);
    });

    this->laozi = new QPushButton(this);
    this->laozi->setText("老子体会");
    this->laozi->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    this->laozi->resize(this->my_app_data->width*(100/PB_NUM),this->my_app_data->height*8);
    this->laozi->move(this->my_app_data->width*(100/PB_NUM)*1,this->my_app_data->height*92);
    connect(this->laozi,&QPushButton::clicked,this,[=](){
        emit ((laozi_widget*)this->stacked->widget(1))->sig_thr_text_edited();
        this->stacked->setCurrentIndex(1);
    });
}

//初始化透明度
void MainWindow::init_clarity()
{
    int a =5;
    QGraphicsOpacityEffect *effect[a];
    for (int i =0;i<a;i++)
    {
        effect[i]=  new QGraphicsOpacityEffect(this);
        effect[i]->setOpacity(0.8); // 设置透明度
    }
    this->laozi->setGraphicsEffect(effect[0]);
    this->zhouyi->setGraphicsEffect(effect[1]);
    this->stacked->setGraphicsEffect(effect[2]);
    this->andorid_temp->setGraphicsEffect(effect[3]);
}

MainWindow::MainWindow (QWidget *parent)
    : QMainWindow(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    my_app_data = app_data::get_app_data();
    my_app_data->main_widget =this;


    this->init_width_height();
    this->init_stacked();
    this->init_push_button();
    this->init_clarity();



}

MainWindow::~MainWindow()
{
}

