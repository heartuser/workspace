#ifndef __INT_BUZZER_H__
#define __INT_BUZZER_H__

#include "Com_Util.h"
#include <STC89C5xRC.H>

void Int_Buzzer_Buzz(double frequency, double time);
void Int_Buzzer_Note(u8 switchNum);

#endif /* __INT_BUZZER_H__ */