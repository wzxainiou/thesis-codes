#include <stdio.h>
#include <stdlib.h>
#define FloatingNumbers 32
#define Resolution 15
#define BlockNumbers 4

//transform the floating number to char
void getFloatBin(float num,char bin[32])
{
    int t = 1;
    int *f = (int*)(&num);

getFloatBin_Loop:
    for(int i=0;i<32;i++)
    {
        bin[i] = (*f)&(t<<31-i)?1:0;
    }
}

float BinaryToDecimal(int BinaryToDecimal, int i)
{
    float decimalNumber = 0;
    int remainder=0;
    while (BinaryToDecimal!=0)
    {
        remainder = BinaryToDecimal%10;
        BinaryToDecimal /= 10;
        decimalNumber += remainder*pow(0.5,i);
        ++i;
    }
    return decimalNumber;
}

int DecimalToBinary(int DecimalToBinary, int j)
{
    int decimalNumber=0;
    int remainder=0;

    DecimalToBinary = DecimalToBinary >> j;
    remainder = DecimalToBinary%2;
    decimalNumber = remainder;

    return decimalNumber;
}

int FindMaxExp(int x[] , int n)
{
    int maxExp,i = 0;
    maxExp=x[0];

FindMaxExp_Loop:
    for(i;i<n;i++)
    {
    	if(maxExp < x[i])
        {
            maxExp = x[i];
        }
    }
    return maxExp;
}

int DecimalPlus(int Dot[FloatingNumbers/(2*BlockNumbers)])
{
    int Sum = 0;
    for(int i=0;i<(FloatingNumbers/(2*BlockNumbers));i++)
    {
    	Sum = Sum + Dot[i];
    }
    return Sum;
}

float FloatingPlus(float resultFloat[FloatingNumbers/(2*BlockNumbers)])
{
    float Sum = 0;
    for(int i=0;i<(FloatingNumbers/(2*BlockNumbers));i++)
    {
    	Sum = Sum + resultFloat[i];
    }
    return Sum;
}


int DecimalDot(int ManBlock[FloatingNumbers],int i, int j)
{
    int Sum = 0;
    Sum = ManBlock[i] * ManBlock[j];

    return Sum;
}

float Test_main(float test[FloatingNumbers])
{
	char exp[8] ={0};
	int manSum,expSum = 0;
	int EXP[FloatingNumbers] ={0};
	int MAN[FloatingNumbers] ={0};
	int ManBlock[FloatingNumbers]={0};
	int man[25]={0};
	int ManSum = 0;

	// gain the exps and mans of all floating point numbers.
FloattoFixed_Loop:
	for(int j=0;j<FloatingNumbers;j++)
	{
        char floating[32];
        man[1] = 1;
        printf("Floating point is :%f",test[j]);
        printf("exp in Binary is");
        getFloatBin(test[j],floating);

        //devide all floating point nummbers into signal, exp and man
Bit_Loop:
        for(int i=0;i<32;i++)
        {
        	if(i>=9){
                //get the man for each number(binary)
                man[i-7] = floating[i];
            }
            else if(0 == i){

                // get the signal for each number
                man[0] = floating[0];
                printf("%d",man[0]);
                printf(", ");
            }
            else{

                //get the exp for each number(binary)
                exp[i-1] = floating[i];
                printf("%d",exp[i-1]);
            }

        }

        // get the exp for each number(Decimal)
        expSum = 0;

Exp_Loop:
        for(int expCount=0;expCount<8;expCount++)
        {
        	expSum += exp[7-expCount] << expCount;
        }
        expSum = expSum - 127;
        printf("exp = %d\n ",expSum);

        // get the Man for each number(Decimal)
        ManSum = 0;

Man_Loop:
        for(int ManCount=0;ManCount<24;ManCount++)
        {
        	ManSum += man[23-ManCount] << ManCount;
        }

        printf("\n ManSum = %d\n",ManSum);

        // include all the exps into EXP[]
        EXP[j] = expSum;
        printf("EXP[%d] =  %d\n",j,EXP[j]);

        // include all the mans into MAN[]
        MAN[j] = ManSum;
        printf("MAN[%d] =  %d\n",j,MAN[j]);

	}

    //find out the largest exp for block
	int SubExp[FloatingNumbers/BlockNumbers] = {0};
	int SubCounter0 = 0;
	int MaxExp[BlockNumbers] = {0};
	int ManNumbers = FloatingNumbers/BlockNumbers;
	int Half_ManNumbers = FloatingNumbers/(BlockNumbers*2);
	int Half_FloatingNumbers = FloatingNumbers/2;
    int BlockPiont = 0;
	float resultFloat[Half_ManNumbers];

Sub_Exp_Loop:
    for(int SubCounter=0;SubCounter<BlockNumbers;SubCounter++)
    {
        SubCounter0 = 0;
        int SubNumber = SubCounter * Half_ManNumbers;
        //printf("************************SubNumber1 =  %d\n",SubNumber);
Sub_Exp_Loop2:
        for(SubCounter0;SubCounter0<Half_ManNumbers;SubCounter0++)
        {
            SubExp[SubCounter0] = EXP[SubNumber + SubCounter0];
            SubExp[SubCounter0+Half_ManNumbers] = EXP[SubNumber + SubCounter0+Half_FloatingNumbers];
            //printf("SubExp[%d] = %d\n",SubCounter0,SubExp[SubCounter0]);
            //printf("SubExp[%d] = %d\n",(SubCounter0+Half_ManNumbers),SubExp[SubCounter0 + Half_ManNumbers]);

        }
        MaxExp[SubCounter] = FindMaxExp(SubExp,ManNumbers);
        printf("MaxExp0[%d] =  %d\n",SubCounter,MaxExp[SubCounter]);
    }


    int BlockDotSum[BlockNumbers] = {0};
    int BlockSum[BlockNumbers] = {0};
    int Dot[Half_ManNumbers];

Sub_Block_Loop:
    for(int SubDotCounter=0;SubDotCounter<BlockNumbers;SubDotCounter++)
    {
        // set all the mans for the block
        int SubDotNumber = SubDotCounter * Half_ManNumbers;

Sub_Block_Loop2:
        for(int ManTransCounter=0;ManTransCounter<Half_ManNumbers;ManTransCounter++)
        {
            //compute the gap between exp and expMax
            int SubDotNumber0 = SubDotNumber + ManTransCounter;//first number's order in the input
            int SubDotNumber1 = SubDotNumber + ManTransCounter + Half_FloatingNumbers;//second number's order in the input

            int ExpGap0 = MaxExp[SubDotCounter] - EXP[SubDotNumber0];
            int ExpGap1 = MaxExp[SubDotCounter] - EXP[SubDotNumber1];

            // set the man
            ManBlock[SubDotNumber0] = MAN[SubDotNumber0] >> ExpGap0;
            ManBlock[SubDotNumber1] = MAN[SubDotNumber1] >> ExpGap1;

            printf("Man[%d] = %d",SubDotNumber0, ManBlock[SubDotNumber0]);
            printf( "\n");
            printf("Man[%d] = %d",SubDotNumber1, ManBlock[SubDotNumber1]);
            printf( "\n");

            ManBlock[SubDotNumber0] = ManBlock[SubDotNumber0] >> Resolution;
            ManBlock[SubDotNumber1] = ManBlock[SubDotNumber1] >> Resolution;

            printf("Man00[%d] = %d",SubDotNumber0, ManBlock[SubDotNumber0]);
            printf( "\n");
            printf("Man00[%d] = %d",SubDotNumber0, ManBlock[SubDotNumber1]);
            printf( "\n");

            Dot[ManTransCounter] = DecimalDot(ManBlock,SubDotNumber0,SubDotNumber1);

            printf("\nDot[%d] = %d\n",ManTransCounter,Dot[ManTransCounter]);
        }

        BlockSum[SubDotCounter] = DecimalPlus(Dot);
        printf("\nBlockSum = %d\n",BlockSum[SubDotCounter]);
        //get the Result
        BlockPiont = (22 - MaxExp[SubDotCounter]- Resolution) * 2;

        resultFloat[SubDotCounter] = (float)BlockSum[SubDotCounter] / pow(2,BlockPiont);

        printf( "resultFloat[%d] = %f \n",SubDotCounter,resultFloat[SubDotCounter]);
    }

    //get the SUM
    float TotalBlockSum = 0;
    TotalBlockSum = FloatingPlus(resultFloat);
    printf("\nTotalBlockSum = %f\n",TotalBlockSum);

    return TotalBlockSum;
}


int main()
{
	float test[FloatingNumbers] = {15.1,16.0,16.0,16.0,16.0,16.0,16.0,17.0,18.2,19.3,20.0,21.0,22.0,23.5,24.0,32.0,
                                    15.1,16.0,16.0,16.0,16.0,16.0,16.0,17.0,18.2,19.3,20.0,21.0,22.0,23.5,24.0,32.0};
	float result = 0.0;
	result = Test_main(test);

    printf("\n%f",result);
	return 0;

}
