#include "stack_widget_one.h"

stack_widget_one::stack_widget_one()
{
    my_app_data = app_data::get_app_data();



    //添加页面按钮 起卦
    this->suji = new QPushButton("速记",this);
    //按钮大小
    this->suji->resize(my_app_data->width*30,my_app_data->height*8);
    //按钮位置
//#ifndef ANDROID
    this->suji->move(my_app_data->width * 35,my_app_data->height*81);
//#endif
//#ifdef ANDROID
//    my_ui->stacked_tab_widget_pb->move(my_ui->width*0.3,my_ui->height*0.3*2+my_ui->height*0.05*3.5);
//#endif

    //添加多个页面
//    QString web_name[SHOW_GUA_WIDGET_NUM]= {"本卦","变卦","解卦"};
//    for(int i=0;i<SHOW_GUA_WIDGET_NUM;i++)
//    {
//        my_ui->stacked_tab_widget[i] = new one_widget(i,my_ui->stacked_tab);
//        my_ui->stacked_tab->addTab(my_ui->stacked_tab_widget[i],web_name[i]);
//    }

//    my_ui->stacked->addWidget(my_ui->stacked_tab);


}
