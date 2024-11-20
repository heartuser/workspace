#ifndef __INT_LEDMATRIX_H__
#define __INT_LEDMATRIX_H__
#include "Com_Util.h"
#include <STC89C5xRC.H>

#define SER      P10
#define SCK      P12
#define RCK      P11

#define MATRIX_LED_EN   P35

void Int_LEDMatrix_Init();
void Int_LEDMatrix_SetPic(u8 *pic);
void Int_LEDMatrix_RefreshByTimer0();
void Int_LEDMatrix_Shift(u8);

#endif /* __INT_LEDMATRIX_H__ */