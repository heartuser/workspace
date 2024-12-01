#include "Int_DS18B20.h"
#include "Int_OLED.h"
#include "Int_DS1302.h"
#include <STDIO.H>

code char *WEEK_NAME[] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun"};

void main()
{
    char str[17];
    char tmp;
    Struct_Date st_date;
    st_date.second      = 0;
    st_date.minute      = 0;
    st_date.hour        = 10;
    st_date.month       = 12;
    st_date.day         = 1;
    st_date.day_of_week = 7;
    st_date.year        = 24;
    Int_OLED_Init();
    Int_OLED_Clear();
    Int_DS1302_Init();
    Int_DS1302_SetDate(&st_date);
    while (1) {
        Int_DS1302_GetDate(&st_date);
        tmp = Int_DS18B20_ReadTem();
        sprintf(str, "20%02d/%02d/%02d %s", (int)st_date.year, (int)st_date.month, (int)st_date.day, WEEK_NAME[st_date.day_of_week - 1]);
        Int_OLED_ShowStr(0, 0, str);
        sprintf(str, "%02d:%02d:%02d Tmp:%02d", (int)st_date.hour, (int)st_date.minute, (int)st_date.second, (int)tmp);
        Int_OLED_ShowStr(0, 1, str);
        Com_Util_Delay1ms(500);
    }
}