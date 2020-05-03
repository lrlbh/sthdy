#include "app_data.h"

app_data::app_data()
{
    this->Copy_Paste= QApplication::clipboard();   //获取系统剪贴板指针
    //QString originalText = clipboard->text();	     //获取剪贴板上文本信息
    //clipboard->setText("哈哈");

}

app_data* app_data::get_app_data()
{
    return  my_app_data;

}

app_data * app_data::my_app_data = new app_data;
