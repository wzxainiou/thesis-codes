#include <stdio.h>
#include <stdlib.h>
/*
num��Ҫչʾ��float��,bin�Ǳ������ж�����λ������
*/

void getFloatBin(float num,char bin[])
{
    int t = 1;//������λ�����
    int *f = (int*)(&num);//��float�Ľ��ͳ�int����float�ĵ�ַת��int*
    for(int i=0;i<32;i++)
    {
    //�����λ��ʼ��λ�룬���Ϊ1����bin[i]=1�����Ϊ0����bin[i]=0
    //����û�н�bin����ַ�����������1 0
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
        printf("����float��Ϊ:%f",test[j]);
        printf("ָ��������");
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
        //��man��ֵ
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
