#include <stdio.h>
#include <stdlib.h>
/*
num是要展示的float数,bin是保存所有二进制位的数组
*/

void getFloatBin(float num,char bin[])
{
    int t = 1;//用来按位与操作
    int *f = (int*)(&num);//将float的解释成int，即float的地址转成int*
    for(int i=0;i<32;i++)
    {
    //从最高位开始按位与，如果为1，则bin[i]=1，如果为0，则bin[i]=0
    //这里没有将bin存成字符，而是数字1 0
        bin[i] = (*f)&(t<<31-i)?1:0;
    }
}


int convertBinaryToDecimal(int convertBinaryToDecimal, int i)
{
    int decimalNumber = 0, remainder;
    while (convertBinaryToDecimal!=0)
    {
        remainder = convertBinaryToDecimal%10;
        convertBinaryToDecimal /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

int main()
{
	float test[10] = {15.0,17.0,18.2,19.3,20.0,21.0,22.5,23.0,24.0,32.0};
	int test1[10] = {0,0,0,0,0,0,0,0,0,0};
    char floating[32];
	char exp[8];
	char man[25];
	man[1] = 1;
	int manSum,expSum;
	for(int j=0;j<10;j++)
	{
        printf("测试float数为:%f",test[j]);
        printf("指数部分是");
        getFloatBin(test[j],floating);
        for(int i=0;i<32;i++)
        {
            if(i>=9){
                man[i-7] = floating[i];
                printf("%d",man[i-7]);

            }
            else if(0 == i){
                man[0] = floating[0];
                printf("%d",man[i]);
                printf(", ");
            }
            else{
                exp[i-1] = floating[i];
                printf("%d",exp[i-1]);
                if(i==8){
                    printf(", ");
                    expSum = 0;
                    for(int expCount=0;expCount<8;expCount++)
                    {
                        expSum += convertBinaryToDecimal((int)exp[7-expCount],expCount);
                    }
                    expSum = expSum - 127;
                    expSum = expSum - 127;
                    printf("exp = %d\n ",expSum);
                }
            }
        }
        printf("\n ");
        printf("man = ");
        //求man的值
        manSum = 0;
        for(int z=0;z<24;z++)
        {
           printf("%d",man[z]);
           manSum += convertBinaryToDecimal((int)man[z],z);

        }
        printf("\n ");
        test1[j] = manSum;
        printf("%d\n ",test1[j]);
	}

}
