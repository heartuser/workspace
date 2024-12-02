#include <STC89C5xRC.H>
#include "Com_Util.h"

void main()
{
    u8 light, i;
    light = 0x00;
    i     = 0x01;
    while (1) {
        if (((i << 1) != 0) && (((i << 1) & light) == 0)) {
            i <<= 1;
        } else {
            light |= i;
            i = 0x01;
        }
        P0 = ~(i | light);
        Com_Util_Delay1ms(200);
    }
}