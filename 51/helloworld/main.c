#include <STC89C5xRC.H>
#include <INTRINS.H>
void Delay1000ms(void)	//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	i = 8;
	j = 1;
	k = 243;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main(){
	unsigned char temp = 0x01;
	while (1)
  {
		 P2 = ~temp;
		 Delay1000ms();
		 temp = temp << 1;
		if (temp == 0){
			temp = 0x01;
		}
  }
}