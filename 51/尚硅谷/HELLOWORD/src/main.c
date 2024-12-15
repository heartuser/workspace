#include <STC89C5xRC.H> //包含STC89C52的头文件
#include <INTRINS.H>

void Delay_1MS(unsigned int count);
void numToShow(unsigned int num,unsigned int wei);
void showWei(unsigned int num);
void main()
{
    unsigned int HZ = 500;// 刷新频率
    long number = 0;// 需要显示的数字
    unsigned int wei = 0;
    unsigned int temp = 0;// 每一位的数字
    long tempNumber = 0;
    char showNumber[8];
    int i = 0;
    int count = 0;
    while (1)
    {
        tempNumber = (number<0?-number:number);
        for (i = 0; i < 8; i++)
        {
            showNumber[i] = tempNumber % 10;
            tempNumber /= 10;
            if (tempNumber == 0){
                    wei = i;
                break;
            }
        }
        if (number < 0)
        {
            showNumber[++wei] = 10;
        }
        while (++count < 70) {
            int j = 0;
            for (j = 0; j <= wei; j++)
            {
                P0 = 0;
                showWei(j);
                numToShow(showNumber[j],j);
                Delay_1MS(1000 / HZ);
            }
        }
        count = 0;
        number++;
    }
    
}
void Delay_1MS(unsigned int count) //@11.0592MHz
{
    unsigned char data i, j;

     while (count > 0) {
         _nop_();
         i = 2;
         j = 199;
         do {
             while (--j)
                 ;
         } while (--i);
         count--;
     }
}
void numToShow(unsigned int num,unsigned int wei){
    unsigned char temp = 0;
    unsigned char mysegable[] = {
        0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40,0x00
    };// 0,1,2,3,4,5,6,7,8,9,-,空白
    temp = mysegable[num];
    if (wei == 0) // 如果是个位就点亮小数点
    {
        temp += 0x80;
    }
    P0 = temp;
}
void showWei(unsigned int num){
    P2 = (num << 2);
}

