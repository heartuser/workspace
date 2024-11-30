#ifndef __DS1302_H__
#define __DS1302_H__
#include "Com_util.h"
typedef struct
{
    u8 second;
    u8 minute;
    u8 hour;
    u8 day;
    u8 month;
    u8 year;
    u8 day_of_week;
} Struct_Date;

void Int_DS1302_Init();

void Int_DS1302_SetDate(Struct_Date *p_st_date);

void Int_DS1302_GetDate(Struct_Date *p_st_date);

#endif /* __DS1302_H__ */