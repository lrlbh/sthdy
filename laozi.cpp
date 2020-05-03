#include "laozi.h"
#include "mainwindow.h"
#include <QTextCodec>

laozi_widget::laozi_widget(QWidget* p):QWidget(p)
{



    my_app_data = app_data::get_app_data();
    //设置白色背景
    this->setAttribute(Qt::WA_StyledBackground,true);
    this->setStyleSheet("background-color: rgb(255,255, 255)");

    //初始化3个需要使用的图片
    this->wen = QPixmap(":/img/wen.png");
    this->gou = QPixmap(":/img/gou.png");
    this->cha = QPixmap(":/img/cha.png");

    //区间输入框
    this->min =new QLineEdit(this);
    this->min->resize(my_app_data->width*38,my_app_data->height*5);
    this->min->move(my_app_data->width*2,0);
    this->max =new QLineEdit(this);
    this->max->resize(my_app_data->width*38,my_app_data->height*5);
    this->max->move(my_app_data->width*42,0);
    //区间提示
    this->hint_max_min = new QLabel(this);
    this->hint_max_min->resize(my_app_data->width*14 ,my_app_data->height*3);
    this->hint_max_min->move(my_app_data->width*84,my_app_data->height);
    this->hint_max_min->setPixmap(wen);
    this->hint_max_min->setScaledContents(true);
    this->hint_max_min->setStyleSheet("QLabel{border:0px;}");


    //需要输入框
    this->equal = new QLineEdit(this);
    this->equal->resize(my_app_data->width * 78,my_app_data->height*5);
    this->equal->move(my_app_data->width*2,my_app_data->height*5);
    //需要输入提示
    this->hint_equal = new QLabel(this);
    this->hint_equal->resize(my_app_data->width*14 ,my_app_data->height*3);
    this->hint_equal->move(my_app_data->width*84,my_app_data->height*6);
    this->hint_equal->setPixmap(wen);
    this->hint_equal->setScaledContents(true);
    this->hint_equal->setStyleSheet("QLabel{border:0px;}");

    //不需要输入框
    this->not_equal = new QLineEdit(this);
    this->not_equal->resize(my_app_data->width* 78,my_app_data->height*5);
    this->not_equal->move(my_app_data->width*2,my_app_data->height*10);
    //不需要输入提示
    this->hint_not_equal = new QLabel(this);
    this->hint_not_equal->resize(my_app_data->width*14 ,my_app_data->height*3);
    this->hint_not_equal->move(my_app_data->width*84,my_app_data->height*11);
    this->hint_not_equal->setPixmap(wen);
    this->hint_not_equal->setScaledContents(true);
    this->hint_not_equal->setStyleSheet("QLabel{border:0px;}");



    //道德经显示文本
    this->txt = new laozi_lab(this);    //道德经显示
    this->txt->resize(my_app_data->width*96,my_app_data->height*60);
    this->txt->move(my_app_data->width*2,my_app_data->height*16);
    this->txt->setStyleSheet("border:1px solid black;");
    this->txt->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    this->txt->setWordWrap(true);
    this->txt->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->txt->show();

    // 只显示某一章
    this->appoint_num = new QLineEdit(this);
    this->appoint_num->resize(my_app_data->width* 14,my_app_data->height*5);
    this->appoint_num->move(my_app_data->width * 9,my_app_data->height*80);

    //体会按钮
    this->tihui = new QPushButton("体会",this);
    this->tihui->resize(my_app_data->width*32,my_app_data->height*9);
    this->tihui->move(my_app_data->width * 34,my_app_data->height*78);
    this->tihui->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    connect(this->tihui,&QPushButton::clicked,this,[&]()
    {
        if(this->appoint_num->text().toInt()>=1 && this->appoint_num->text().toInt()<=81)
        {
            this->one_laozi_data = this->laozi_data[this->appoint_num->text().toInt() - 1];
            this->txt->setText( this->one_laozi_data.front());
            this->one_laozi_data.pop_front();
            return ;
        }

        QSet<int> temp_map;
        if((*this->hint_max_min->pixmap()) == this->gou)
        {

            for (int i = this->min->text().toInt();i <= this->max->text().toInt();i++)
            {
                temp_map.insert(i);

            }
        }


        QList<QString> temp_list_int;

        if((*this->hint_equal->pixmap()) == this->gou)
        {
            temp_list_int = this->equal->text().split("-");
            for (int i = 0;i<temp_list_int.length();i++)
            {
                temp_map.insert(temp_list_int[i].toInt());

            }
        }


        if((*this->hint_not_equal->pixmap()) == this->gou)
        {
            temp_list_int.clear();
            temp_list_int = this->not_equal->text().split("-");
            for (int i = 0;i<temp_list_int.length();i++)
            {
                temp_map.remove(temp_list_int[i].toInt());

            }
        }


next:
        this->read_sum =qrand()%81+1;
        if(!temp_map.empty())
        {
            if(temp_map.find(this->read_sum) == temp_map.end())
            {
                goto next;
            }

        }



        this->one_laozi_data = this->laozi_data[this->read_sum -1];
        this->txt->setText( this->one_laozi_data.front());
        this->one_laozi_data.pop_front();
    });







    //获取配置文件的内容
    config_file = new QFile("./laozi_config.txt");
    QList<QString> config_data;
    if( config_file->open(QIODevice::ReadWrite | QIODevice::Text))
    {
        while (!config_file->atEnd())
        {

            static int i = 0;

            config_data.append( QByteArray(config_file->readLine()));
            if(config_data[i] != "123\n" && i==0)
            {
                this->min->setText(config_data[i].remove("\n"));
            }
            else if(config_data[i] != "123\n" && i==1)
            {
                this->max->setText(config_data[i].remove("\n"));
            }
            else if(config_data[i] != "123\n" && i==2)
            {
                this->equal->setText(config_data[i].remove("\n"));
            }
            else if(config_data[i] != "123\n" && i==3)
            {
                this->not_equal->setText(config_data[i].remove("\n"));
            }


            i++;
        }



    }
    config_file->close();
    config_file->open(QIODevice::WriteOnly | QIODevice::Text);



    //读取道德经内容
    QFile file(":/res/laozi.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<QString> r_temp;
        //读取数据
        int i_temp =1;
        while (!file.atEnd())
        {
            if(++i_temp% 2)
            {
                file.readLine();
                continue;
            }
            r_temp.append( QByteArray(file.readLine()));
        }


        //这一坨循环用于分割字符串，同时保留分割符号
        //目前支持这些符号 ,.:;!?，。：；！、？  可酌情增减
        //支持utf-8编码数据
        for(int k =0;k<81;k++)
        {

            char temp[128]={0};
            char temp_data[555]={0};
            strcpy(temp_data,r_temp[k].toStdString().data());
            for (int i=0,j=0;i<(int)strlen(temp_data);i++)
            {
                if(temp_data[i] == 0B00101100
                        ||temp_data[i] == 0B00101110
                        ||temp_data[i] == 0B00111010
                        ||temp_data[i] == 0B00111011
                        ||temp_data[i] == 0B00100001
                        ||temp_data[i] == 0B00111111
                        ||(unsigned char)temp_data[i] == 0B11101111
                        ||(unsigned char)temp_data[i] == 0B11100011
                        ||(unsigned char)temp_data[i] == 0B11101111
                        ||(unsigned char)temp_data[i] == 0B11101111
                        ||(unsigned char)temp_data[i] == 0B11101111
                        ||(unsigned char)temp_data[i] == 0B11100011
                        ||(unsigned char)temp_data[i] == 0B11101111)

                {
                    if (temp_data[i] == 0B00101100
                            ||temp_data[i] == 0B00101110
                            ||temp_data[i] == 0B00111010
                            ||temp_data[i] == 0B00111011
                            ||temp_data[i] == 0B00100001
                            ||temp_data[i] == 0B00111111)
                    {

                        temp[j++]=temp_data[i];
                        this->laozi_data[k].push_back(temp);
                        memset(temp,0,128);
                        j=0;
                        continue;
                    }

                    if((unsigned char)temp_data[i] ==   0B10111100
                            ||(unsigned char)temp_data[i+1] == 0B10000000
                            ||(unsigned char)temp_data[i+1] == 0B10111100
                            ||(unsigned char)temp_data[i+1] == 0B10111100
                            ||(unsigned char)temp_data[i+1] == 0B10111100
                            ||(unsigned char)temp_data[i+1] == 0B10000000
                            ||(unsigned char)temp_data[i+1] == 0B10111100)

                    {
                        if((unsigned char)temp_data[i+2] == 0B10001100
                                ||(unsigned char)temp_data[i+2] == 0B10000010
                                ||(unsigned char)temp_data[i+2] == 0B10000010
                                ||(unsigned char)temp_data[i+2] == 0B10011011
                                ||(unsigned char)temp_data[i+2] == 0B10000001
                                ||(unsigned char)temp_data[i+2] == 0B10000001
                                ||(unsigned char)temp_data[i+2] == 0B10011111)
                        {
                            memcpy(temp+j,temp_data+i,3);
                            this->laozi_data[k].push_back(temp);
                            i+=2;
                            memset(temp,0,128);
                            j=0;

                        }
                        else    //第三个的判断
                        {
                            temp[j++]=temp_data[i];
                            temp[j++]=temp_data[i+1];
                            if(temp_data[i+2] ==(unsigned char)0B00000000)
                            {
                                break;
                            }


                        }


                    }
                    else    //第二个判断
                    {
                        temp[j++]=temp_data[i];
                        if(temp_data[i+1] ==(unsigned char)0B00000000)
                        {
                            break;
                        }

                    }


                }
                else    //第一个判断
                {

                    temp[j++]=temp_data[i];

                }
            }

        }
    }
    else
    {
        this->txt->setText("资源文件加载失败！");
    }
    file.close();

    //绑定文本框变化的信号
    connect(this->max,&QLineEdit::textEdited,this,&laozi_widget::thr_text_edited);
    connect(this->min,&QLineEdit::textEdited,this,&laozi_widget::thr_text_edited);
    connect(this->not_equal,&QLineEdit::textEdited,this,&laozi_widget::thr_text_edited);
    connect(this->equal,&QLineEdit::textEdited,this,&laozi_widget::thr_text_edited);
    connect(this,&laozi_widget::sig_thr_text_edited,this,laozi_widget::thr_text_edited);



}

laozi_widget::~laozi_widget()
{
    if(*this->hint_max_min->pixmap() == this->gou)
    {

        config_file->write(this->min->text().toUtf8()+'\n');
        config_file->write(this->max->text().toUtf8()+'\n');

    }
    else
    {

        config_file->write("123\n123\n");

    }


    if(*this->hint_equal->pixmap() == this->gou)
    {
        config_file->write(this->equal->text().toUtf8()+'\n');
    }
    else
    {
        config_file->write("123\n");

    }


    if(*this->hint_not_equal->pixmap() == this->gou)
    {
        config_file->write(this->not_equal->text().toUtf8()+'\n');
    }
    else
    {
        config_file->write("123\n");

    }

    config_file->close();
    delete config_file;
}

void laozi_widget::thr_text_edited()
{
    //创建线程容器
    QThread* temp_thr =new QThread;
    //创建自己的线程对象
    line_edit_thr* my_thr = new line_edit_thr;
    //绑定线程容器的 start 函数发出的信号到，自己的线程对象中的槽函数
    connect(temp_thr,&QThread::started,my_thr,&line_edit_thr::run_1);
    //回收 QThread 对象的资源
    connect(temp_thr,&QThread::finished,temp_thr,&QThread::deleteLater);
    //回收 自己写的类 对象资源
    connect(temp_thr,&QThread::finished,my_thr,&line_edit_thr::delete_this);
    //把自己创建的线程对象移动到线程容器中
    my_thr->moveToThread(temp_thr);

    //开启线程槽函数
    temp_thr->start();

    //槽函数代码执行完毕后，退出线程
    temp_thr->quit();
    temp_thr->exit();

    //qDebug()<<"主线程id="<<QThread::currentThreadId();

}


line_edit_thr::line_edit_thr(QObject *p) : QObject(p)
{
    this->my_app_data = app_data::get_app_data();
}

//run_1 老子页面中，三个单行编辑变化时，执行的子线程
void  line_edit_thr::run_1()
{
    //打印线程id的方法
    //qDebug()<<"子线程id="<<QThread::currentThreadId();

    //获取到老子页面的对象
    laozi_widget* temp_laozi =  ((laozi_widget*)(((MainWindow*)this->my_app_data->main_widget)->stacked->widget(1)));


    //max min输入框操作
    //输入框不为空
    if(temp_laozi->min->text() != "" || temp_laozi->max->text() != "")
    {
        //数据正确
        if(temp_laozi->max->text().toInt() >= 1 && temp_laozi->max->text().toInt() <=80&&
                temp_laozi->max->text().toInt()> temp_laozi->min->text().toInt()&&
                temp_laozi->min->text().toInt()>= 1&& temp_laozi->min->text().toInt()<=81)
        {
            temp_laozi->hint_max_min->setPixmap(temp_laozi->gou);

        }
        else    //数据错误
        {
            temp_laozi->hint_max_min->setPixmap(temp_laozi->cha);


        }
    }
    else    //输入框为空
    {
        temp_laozi->hint_max_min->setPixmap(temp_laozi->wen);

    }



    //equal 输入框的操作

    if(temp_laozi->equal->text() != "")
    {
        QStringList temp_list  =  temp_laozi->equal->text().split("-");
        QList<int> list_int;

        if(temp_list.length() <1)
        {
            temp_laozi->hint_equal->setPixmap(temp_laozi->cha);
            goto next;
        }

        for(int i=0;i<temp_list.length();i++)
        {
            bool temp_list_ok = false;
            list_int.push_back( temp_list[i].toInt(&temp_list_ok));
            if(!temp_list_ok)
            {
                temp_laozi->hint_equal->setPixmap(temp_laozi->cha);
                goto next;
            }
        }

        for(int i=0;i<list_int.length();i++)
        {
            if(!(list_int[i] <= 81 && list_int[i]>= 1))
            {
                temp_laozi->hint_equal->setPixmap(temp_laozi->cha);
                goto next;
            }

        }

        temp_laozi->hint_equal->setPixmap(temp_laozi->gou);

    }
    else
    {
        temp_laozi->hint_equal->setPixmap(temp_laozi->wen);
    }

next:
    //not_equal 输入框的操作


    if(temp_laozi->not_equal->text() != "")
    {
        QStringList temp_list  =  temp_laozi->not_equal->text().split("-");
        QList<int> list_int;

        if(temp_list.length() <1)
        {
            temp_laozi->hint_not_equal->setPixmap(temp_laozi->cha);
            return;
        }

        for(int i=0;i<temp_list.length();i++)
        {
            bool temp_list_ok = false;
            list_int.push_back( temp_list[i].toInt(&temp_list_ok));
            if(!temp_list_ok)
            {
                temp_laozi->hint_not_equal->setPixmap(temp_laozi->cha);
                return;
            }
        }

        for(int i=0;i<list_int.length();i++)
        {
            if(!(list_int[i] <= 81 && list_int[i]>= 1))
            {
                temp_laozi->hint_not_equal->setPixmap(temp_laozi->cha);
                return;
            }

        }

        temp_laozi->hint_not_equal->setPixmap(temp_laozi->gou);

    }
    else
    {
        temp_laozi->hint_not_equal->setPixmap(temp_laozi->wen);
    }



    return;
}

void line_edit_thr::delete_this()
{
    delete this;
}

void hint_lab::mousePressEvent(QPaintEvent *)
{

}

void hint_lab::mouseReleaseEvent(QMouseEvent *)
{

}


laozi_lab::laozi_lab(QWidget* p):QLabel(p)
{
    my_app_data = app_data::get_app_data();


}
//重写道德经lab鼠标释放事件
void laozi_lab::mouseReleaseEvent(QMouseEvent *)
{
    QQueue<QString> &temp_queue = ((laozi_widget*)((MainWindow*)this->my_app_data->main_widget)->stacked->widget(1))->one_laozi_data;
    if(temp_queue.size()>0)
    {

        laozi_widget * temp_laozi = ((laozi_widget*)((MainWindow*)this->my_app_data->main_widget)->stacked->widget(1));
        temp_laozi->txt->setText(temp_laozi->txt->text() + temp_queue.front());
        temp_queue.pop_front();
    }

}




