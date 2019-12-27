#include "app_data.h"

app_data::app_data()
{

}

app_data* app_data::get_app_data()
{
    return  my_app_data;

}

app_data * app_data::my_app_data = new app_data;
