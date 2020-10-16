#include "zhouyi.h"

//void zhouyi_tab_widget::paintEvent(QPaintEvent *)
//{
//    qDebug()<<"111";
//    //创建画家 this表示画图设备 让画家在当前窗口绘图
//    QPainter painter(this);
//    //创建一支画笔，同时指定颜色
//    QPen pen(QColor(255,0,0));
//    //可以设置笔的风格 虚线
//    //pen.setStyle(Qt::DotLine);
//    //可以设置笔的粗细
//    pen.setWidth(10);
//    //让画家拿起画笔
//    painter.setPen(pen);

//    //画线 给出两个点的坐标 画一条直线
//    painter.drawLine(QPoint(0,0),QPoint(1000,1000));
//    this->update();
//}

zhouyi_tab_widget::zhouyi_tab_widget(QWidget *parent):QTabWidget(parent)
{
    my_app_data = app_data::get_app_data();

    //设置tab_widget标头大小
    this->setStyleSheet("QTabBar::tab{width:"+ QString::number( my_app_data->width_ture/TAB_WIDGET_NUM)+"}");


    //多个页面，初始化
    QString web_name[TAB_WIDGET_NUM]= {" 本卦","变卦","解卦"};
    for(int i=0;i<TAB_WIDGET_NUM;i++)
    {
        QWidget* temp_widget =  (QWidget*)new zhouyi_widget(this);
        this->addTab(temp_widget,web_name[i]);
    }
    for (int i = 0;i<TAB_WIDGET_NUM;i++)
    {
        ((zhouyi_widget*)this->widget(i))->gua_name->setText("地火明夷\n");
        ((zhouyi_widget*)this->widget(i))->gua_info->setText("大衍之数五十，其用四十有九。分而为二以象两，挂一以象三，揲之以 四以象四时，归奇于扐以象闰，五岁再闰，故再扐而后挂。");
        ((zhouyi_widget*)this->widget(i))->gua_img->setText("---------\n---------\n---------\n---------\n---------\n---------");

    }

    //按钮起卦
    this->suji = new QPushButton("速记",this);
    this->suji->resize(my_app_data->width*32,my_app_data->height*9);
    this->suji->move(my_app_data->width * 34,my_app_data->height*75);
    this->suji->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    connect(this->suji,&QPushButton::clicked,this,[=](){
        QVector<int> temp_vec = this->get_one_gua();
        temp_vec[0] = temp_vec[0] -1;
        temp_vec[1] = temp_vec[1] -1;

        for (int i =0;i<temp_vec.length();i++)
        {
            if(i==2)
            {
                QString temp_str_3;
                ((zhouyi_widget*)this->widget(i))->gua_name->setText("预留");
                ((zhouyi_widget*)this->widget(i))->gua_img->setText("预留");

                if(temp_vec[i] == 1)
                {

                    //(1) 。
                    for (int j = 2;  j < 8; j++)
                    {
                        if(QString::compare(my_app_data->zhouyi_txt[temp_vec[0]][j].left(2),my_app_data->zhouyi_txt[temp_vec[1]][j].left(2)))
                        {
                            ((zhouyi_widget*)this->widget(i))->gua_name->setText(my_app_data->zhouyi_txt[temp_vec[0]][0]);
                            ((zhouyi_widget*)this->widget(i))->gua_img->setText("一爻变者，以本卦变爻的爻辞占。\n");
                            temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][j] +'\n';
                            ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                        }
                    }


                }
                else if(temp_vec[i] == 2)
                {
                    for(int j= 2 ;j<8;j++)
                    {
                        //(2) 二爻变者，以本卦二变的爻辞占，以上爻的爻辞为主。
                        if(QString::compare(my_app_data->zhouyi_txt[temp_vec[0]][j].left(2),my_app_data->zhouyi_txt[temp_vec[1]][j].left(2)))
                        {
                            ((zhouyi_widget*)this->widget(i))->gua_name->setText( my_app_data->zhouyi_txt[temp_vec[0]][0]);
                            ((zhouyi_widget*)this->widget(i))->gua_img->setText("二爻变者，以本卦二变的爻辞占，以上爻的爻辞为主。\n");
                            temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][j] + '\n';
                            ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                        }
                    }


                }
                else if(temp_vec[i] == 3)
                {
                    //(3) 三爻变者，以本卦及之卦的卦辞占，以本卦的卦辞为主。
                    ((zhouyi_widget*)this->widget(i))->gua_name->setText( my_app_data->zhouyi_txt[temp_vec[0]][0] + '\n'+ my_app_data->zhouyi_txt[temp_vec[1]][0]);
                    ((zhouyi_widget*)this->widget(i))->gua_img->setText(" 三爻变者，以本卦及之卦的卦辞占，以本卦的卦辞为主。");
                    temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][1] + '\n';
                    temp_str_3 += my_app_data->zhouyi_txt[temp_vec[1]][1] + '\n';
                    ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                }
                else if(temp_vec[i] == 4)
                {
                    //(4) 四爻变者，以之卦中二不变的爻辞占，以下爻的爻辞为主。
                    for(int j= 2 ;j<8;j++)
                    {
                        if(!QString::compare(my_app_data->zhouyi_txt[temp_vec[0]][j].left(2),my_app_data->zhouyi_txt[temp_vec[1]][j].left(2)))
                        {
                            ((zhouyi_widget*)this->widget(i))->gua_name->setText(my_app_data->zhouyi_txt[temp_vec[1]][0]);
                            ((zhouyi_widget*)this->widget(i))->gua_img->setText("四爻变者，以之卦中二不变的爻辞占，以下爻的爻辞为主。");
                            temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][j] + '\n';
                            ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                        }
                    }

                }
                else if(temp_vec[i]== 5)
                {
                    //(4)五爻变者，以之卦中不变的爻辞占。
                    for(int j= 2 ;j<8;j++)
                    {
                        if(!QString::compare(my_app_data->zhouyi_txt[temp_vec[0]][j].left(2),my_app_data->zhouyi_txt[temp_vec[1]][j].left(2)))
                        {
                            ((zhouyi_widget*)this->widget(i))->gua_name->setText(my_app_data->zhouyi_txt[temp_vec[1]][0]);
                            ((zhouyi_widget*)this->widget(i))->gua_img->setText("五爻变者，以之卦中不变的爻辞占。");
                            temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][j] + '\n';
                            ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                        }
                    }
                }
                else if(temp_vec[i]== 6)
                {
                    //六爻全变者，乾坤两卦以用九和用六的辞占，并参考之卦卦辞。余六十二卦占以之卦卦辞。
                    QString temp_str4;
                    if(temp_vec[0] == 0)
                    {
                        temp_str_3 +="用九：见群龙无首，吉。\n";
                        temp_str4 += "乾为天";
                    }
                    if(temp_vec[0]==1)
                    {
                        temp_str_3 +="用六：利永贞。\n";
                        temp_str4 += "坤为地";
                    }
                    else
                    {
                        temp_str_3 += my_app_data->zhouyi_txt[temp_vec[1]][1] + '\n';
                        temp_str4 += my_app_data->zhouyi_txt[temp_vec[1]][0];
                    }
                    ((zhouyi_widget*)this->widget(i))->gua_name->setText(temp_str4);
                    ((zhouyi_widget*)this->widget(i))->gua_img->setText("六爻全变者，乾坤两卦以用九和用六的辞占。并参考之卦卦辞。余六十二卦占以之卦卦辞。");
                    ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);

                }
                else if(temp_vec[i]== 0)
                {
                    ((zhouyi_widget*)this->widget(i))->gua_name->setText(my_app_data->zhouyi_txt[temp_vec[0]][0]);
                    ((zhouyi_widget*)this->widget(i))->gua_img->setText("六爻全不变者，以本卦卦辞占。");
                    temp_str_3 += my_app_data->zhouyi_txt[temp_vec[0]][1] + '\n';
                    ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str_3);
                }


                return ;


            }

            //本卦和变卦的展示
            QString temp_str;
            QString temp_str_img;
            for (int k=2,j=7;k<my_app_data->zhouyi_txt.first().length();k++,j--)
            {
                temp_str += my_app_data->zhouyi_txt[temp_vec[i]][k];
                if(my_app_data->zhouyi_txt[temp_vec[i]][j].indexOf("九") <= 5 &&my_app_data->zhouyi_txt[temp_vec[i]][j].indexOf("九") >=0 )
                {
                    temp_str_img+="---------\n";

                }
                else
                {
                    temp_str_img+="---    ---\n";
                }
            }


            ((zhouyi_widget*)this->widget(i))->gua_img->setText(temp_str_img);
            ((zhouyi_widget*)this->widget(i))->gua_info->setText(temp_str);
            temp_str = my_app_data->zhouyi_txt[temp_vec[i]][0] + '\n';
            temp_str += my_app_data->zhouyi_txt[temp_vec[i]][1];
            ((zhouyi_widget*)this->widget(i))->gua_name->setText(temp_str);


        }
    });


    //读取周易数据
    QFile file(":/res/64_utf-8.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QList<QString> r_temp;
        //读取数据
        while (!file.atEnd())
            r_temp.append( QByteArray(file.readLine()));


        for (int i =0 ;i<64;i++)
        {
            QList<QString> gua;
            for (int j =0 ; j < 8;j++)
            {
                if(j == 0)
                {
                    r_temp[i*9 +j].remove("（");
                    r_temp[i*9 +j].replace(r_temp[i*9 +j].indexOf("）"),100,QString(""));
                    r_temp[i*9 +j] =r_temp[i*9 +j].trimmed();
                }
                else if(j== 1)
                {
                    r_temp[i*9 +j].replace(r_temp[i*9 +j].indexOf("《"),r_temp[i*9 +j].indexOf("：")+1,QString(""));
                    r_temp[i*9 +j] =r_temp[i*9 +j].trimmed();
                }
                gua.push_back(r_temp[i*9 +j]);

            }

            my_app_data->zhouyi_txt.insert(i,gua);
        }
    }
    file.close();

}

zhouyi_widget::zhouyi_widget(QWidget *parent):QWidget(parent)
{


    //挂的名称
    my_app_data = app_data::get_app_data();
    this->gua_name = (QLabel*)new zhouyi_labl(this);
    this->gua_name->resize(QSize(my_app_data->width*46,my_app_data->height*22));    //大小
    this->gua_name->move(my_app_data->width*3,my_app_data->height);     //位置
    this->gua_name->setStyleSheet("border:1px solid black;");   //边框
    this->gua_name->setFont(QFont ( "Microsoft YaHei", 15, 87 )); // 字体
    this->gua_name->setWordWrap(true);  //自动换行
    this->gua_name->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);    //上下左右对齐
    this->gua_name->show();

    //挂的图像
    this->gua_img = (QLabel*)new zhouyi_labl(this);
    this->gua_img->resize(QSize(my_app_data->width*45,my_app_data->height*22));
    this->gua_img->move(my_app_data->width*52,my_app_data->height);
    this->gua_img->setStyleSheet("border:1px solid black;");
    this->gua_img->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    this->gua_img->setWordWrap(true);
    this->gua_img->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->gua_img->show();

    //挂的信息
    this->gua_info = (QLabel*)new zhouyi_labl(this);
    this->gua_info->resize(QSize(my_app_data->width*94,my_app_data->height*45));
    this->gua_info->move(my_app_data->width*3,my_app_data->height*24);
    this->gua_info->setStyleSheet("border:1px solid black;");
    this->gua_info->setFont(QFont ( "Microsoft YaHei", 15, 87 ));
    this->gua_info->setWordWrap(true);
    this->gua_info->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->gua_info->show();
}

QVector<int> zhouyi_tab_widget::get_one_gua()
{
    //按顺序存储384爻减少查询数据量、查询次数
    char buf11[64][6] = { {'1','1','1','1','1','1'},
                          {'0','0','0','0','0','0'},{'1','0','0','0','1','0'},
                          {'0','1','0','0','0','1'},{'1','1','1','0','1','0'},
                          {'0','1','0','1','1','1'},{'0','1','0','0','0','0'},
                          {'0','0','0','0','1','0'},{'1','1','1','0','1','1'},
                          {'1','1','0','1','1','1'},{'1','1','1','0','0','0'},
                          {'0','0','0','1','1','1'},{'1','0','1','1','1','1'},
                          {'1','1','1','1','0','1'},{'0','0','1','0','0','0'},
                          {'0','0','0','1','0','0'},{'1','0','0','1','1','0'},
                          {'0','1','1','0','0','1'},{'1','1','0','0','0','0'},
                          {'0','0','0','0','1','1'},{'1','0','0','1','0','1'},
                          {'1','0','1','0','0','1'},{'0','0','0','0','0','1'},
                          {'1','0','0','0','0','0'},{'1','0','0','1','1','1'},
                          {'1','1','1','0','0','1'},{'1','0','0','0','0','1'},
                          {'0','1','1','1','1','0'},{'0','1','0','0','1','0'},
                          {'1','0','1','1','0','1'},{'0','0','1','1','1','0'},
                          {'0','1','1','1','0','0'},{'0','0','1','1','1','1'},
                          {'1','1','1','1','0','0'},{'0','0','0','1','0','1'},
                          {'1','0','1','0','0','0'},{'1','0','1','0','1','1'},
                          {'1','1','0','1','0','1'},{'0','0','1','0','1','0'},
                          {'0','1','0','1','0','0'},{'1','1','0','0','0','1'},
                          {'1','0','0','0','1','1'},{'1','1','1','1','1','0'},
                          {'0','1','1','1','1','1'},{'0','0','0','1','1','0'},
                          {'0','1','1','0','0','0'},{'0','1','0','1','1','0'},
                          {'0','1','1','0','1','0'},{'1','0','1','1','1','0'},
                          {'0','1','1','1','0','1'},{'1','0','0','1','0','0'},
                          {'0','0','1','0','0','1'},{'0','0','1','0','1','1'},
                          {'1','1','0','1','0','0'},{'1','0','1','1','0','0'},
                          {'0','0','1','1','0','1'},{'0','1','1','0','1','1'},
                          {'1','1','0','1','1','0'},{'0','1','0','0','1','1'},
                          {'1','1','0','0','1','0'},{'1','1','0','0','1','1'},
                          {'0','0','1','1','0','0'},{'1','0','1','0','1','0'},
                          {'0','1','0','1','0','1'} };
    //存储爻阴阳
    char buf[6] = { 0 };
    //存储卦ID
    int gua_id = 0;
    //存储变爻数量
    int yao = 0;
    //保存 卦id 和 爻阴阳的信息
    QVector<int> gua_info;


    //获取每一爻的信息保存
    for (int i = 0; i < 6; i++)
    {
        int n = this->get_one_yao() / 4;

        if (n == 6)
        {
            memset(&buf[i], '6', 1);

        }
        else if (n == 7)
        {
            memset(&buf[i], '7', 1);

        }
        else if (n == 8)
        {
            memset(&buf[i], '8', 1);

        }
        else if (n == 9)
        {
            memset(&buf[i], '9', 1);
        }
    }

    //其中偶数代表阴，奇数代表阳，两极为太，两中为少，即：6为太阴，8为少阴，7为少阳，9为太阳。

    //依次和64卦比较,得到本卦ID
    for (int i = 0; i < 64; i++)
    {
        //和每一个卦比较
        for (int j = 0; j < 6; j++)
        {
            //把6、7、8、9、转换成0、1，变卦中6、8为阴爻，变卦中7、9为阳爻
            char tmp_buf = '0';
            if (buf[j] == '7' || buf[j] == '9')
            {
                tmp_buf = '1';
            }
            //比较一爻
            if (tmp_buf == buf11[i][j])
            {
                //5爻都对，取得卦id
                if (j == 5)
                {
                    gua_id = i + 1;
                    gua_info.push_back(gua_id);
                }
            }
            else//某个爻比较失败，比较下一卦
            {
                break;
            }

        }
    }



    //依次和64卦比较,得到变卦ID
    for (int i = 0; i < 64; i++)
    {
        //和每一个卦比较
        for (int j = 0; j < 6; j++)
        {
            char tmp_buf = '0';
            if (buf[j] == '7' || buf[j] == '6')
            {
                tmp_buf = '1';
            }
            //比较一爻
            if (tmp_buf == buf11[i][j])
            {
                //5爻都对，取得卦id
                if (j == 5)
                {
                    gua_id = i + 1;
                    gua_info.push_back(gua_id);
                }
            }
            else//某个爻比较失败，比较下一卦
            {
                break;
            }

        }
    }

    //变卦数量
    for (int i = 0; i < 6; i++)
        if (buf[i] == '6' || buf[i] == '9')
            yao++;



    gua_info.push_back(yao);
    return gua_info;
}

int  zhouyi_tab_widget::get_one_yao()
{
    //数50用49
    int n = 49;
    for (int i = 0; i < 3; i++)
    {
        //分而为二
        int nt = (qrand() % (n - 1) + 1);//随机数为1-48
        int nd = n - nt;

        //挂一象三
        if (qrand() % 2 == 0)
        {
            nt--;
        }
        else
        {
            nd--;
        }

        //揲之以四 以象四时
        //除以4产生的余数不要，如果余数为0减4
        int tmpnt = nt;
        int tmpnd = nd;
        nt = nt / 4 * 4;
        nd = nd / 4 * 4;
        if (nt == tmpnt && nt != 0)
        {
            nt -= 4;
        }
        if (nd == tmpnd && nd != 0)
        {
            nd -= 4;
        }

        n = nt + nd;
    }
    return n;
}

void zhouyi_tab_widget::mousePressEvent(QMouseEvent *ev)
{
    qDebug()<<this->x;
    this->x= ev->globalX();
    this->y = ev->globalY();

}

void zhouyi_tab_widget::mouseReleaseEvent(QMouseEvent *ev)
{
    if( this->x -ev->globalX() >= my_app_data->width*20 )
    {
        if(this->y -ev->globalY() <= my_app_data->height*20)
        {

            if( this->currentIndex() >= TAB_WIDGET_NUM-1)
            {
                this->setCurrentIndex(0);
            }
            else
            {
                this->setCurrentIndex(this->currentIndex()+1);
            }


        }

    }


    if(ev->globalX() - this->x  >= my_app_data->width*20 )
    {
        if(ev->globalY()-this->y  <= my_app_data->height*20)
        {

            if( this->currentIndex()  == 0)
            {
                this->setCurrentIndex(TAB_WIDGET_NUM-1);
            }
            else
            {
                this->setCurrentIndex(this->currentIndex()-1);
            }


        }

    }


}


zhouyi_labl::zhouyi_labl(QWidget *parent) : QLabel(parent)
{
    my_app_data = app_data::get_app_data();
}


bool zhouyi_labl::event(QEvent *e)
{
    //拦截指定事件的事件
    //鼠标按下事件
    if(e->type() == QEvent::MouseButtonPress )
    {
        if(this->num == 0)
        {
            num++;
            QTimer::singleShot(1000,NULL,[=]()
            {
                this->num = 0;
            });

        }
        else
        {
            QLabel* toast = new QLabel(my_app_data->main_widget);
            toast->setText("已复制！");
            toast->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint); //置顶
            toast->move(my_app_data->width*44,my_app_data->height*84);
            toast->resize(my_app_data->width*100,my_app_data->height*10);
            toast->show();

            my_app_data->Copy_Paste->setText(this->text());
            QTimer::singleShot(1800,NULL,[=](){
                delete  toast;
            });
        }

        //返回true表示当前事件不要在处理
        return false;
    }

    //其他事件交还父类处理
    return QLabel::event(e);

}



/*
void zhouyi_labl::mouseDoubleClickEvent(QMouseEvent *event)
{
    QLabel* toast = new QLabel(my_app_data->zhouyi_widget);
    toast->setText("已复制！");
    toast->setWindowFlags(this->windowFlags()|Qt::WindowStaysOnTopHint); //置顶
    toast->move(my_app_data->width*45,my_app_data->height*40);
    toast->show();

    QTimer::singleShot(1000,NULL,[=](){
        delete  toast;
    });

    my_app_data->Copy_Paste->setText(this->text());
}



//void zhouyi_labl::mouseReleaseEvent(QMouseEvent *event)
//{
//    my_app_data->Copy_Paste->setText(this->text());
//}
*/











