#include <stdio.h>
#include <stdlib.h>
#include "Test_main.h"


//transform the floating number to char
void getFloatBin(float num,char bin[32])
{
    int t = 1;
    int *f = (int*)(&num);

getFloatBin_Loop:
    for(int i=0;i<32;i++)
    {
//#pragma HLS unroll
#pragma HLS pipeline
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
//#pragma HLS unroll
#pragma HLS pipeline
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
DecimalPlusLoop:
    for(int i=0;i<(FloatingNumbers/(2*BlockNumbers));i++)
    {
//#pragma HLS unroll
#pragma HLS pipeline
    	Sum = Sum + Dot[i];
    }
    return Sum;
}

float FloatingPlus(float resultFloat[FloatingNumbers/(2*BlockNumbers)])
{
    float Sum = 0;
    for(int i=0;i<(FloatingNumbers/(2*BlockNumbers));i++)
    {
//#pragma HLS unroll
#pragma HLS pipeline
    	Sum = Sum + resultFloat[i];
    }
    return Sum;
}


int DecimalDot(int i, int j)
{
    int Sum = 0;
    Sum = i * j;

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
//#pragma HLS unroll
#pragma HLS pipeline
		char floating[32];
        man[1] = 1;
        getFloatBin(test[j],floating);

        //devide all floating point nummbers into signal, exp and man
Bit_Loop:
        for(int i=0;i<32;i++)
        {
//#pragma HLS unroll
#pragma HLS pipeline
        	if(i>=9){
                //get the man for each number(binary)
                man[i-7] = floating[i];
            }
            else if(0 == i){

                // get the signal for each number
                man[0] = floating[0];
            }
            else{

                //get the exp for each number(binary)
                exp[i-1] = floating[i];
            }

        }

        // get the exp for each number(Decimal)
        expSum = 0;

Exp_Loop:
        for(int expCount=0;expCount<8;expCount++)
        {
//#pragma HLS unroll
#pragma HLS pipeline
        	expSum += exp[7-expCount] << expCount;
        }
        expSum = expSum - 127;

        // get the Man for each number(Decimal)
        ManSum = 0;

Man_Loop:
        for(int ManCount=0;ManCount<24;ManCount++)
        {
//#pragma HLS unroll
#pragma HLS pipeline
        	ManSum += man[23-ManCount] << ManCount;
        }

        // include all the exps into EXP[]
        EXP[j] = expSum;

        // include all the mans into MAN[]
        MAN[j] = ManSum;

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
//#pragma HLS unroll
#pragma HLS pipeline
    	SubCounter0 = 0;
        int SubNumber = SubCounter * Half_ManNumbers;
Sub_Exp_Loop2:
        for(SubCounter0;SubCounter0<Half_ManNumbers;SubCounter0++)
        {
//#pragma HLS unroll
#pragma HLS pipeline
        	SubExp[SubCounter0] = EXP[SubNumber + SubCounter0];
            SubExp[SubCounter0+Half_ManNumbers] = EXP[SubNumber + SubCounter0+Half_FloatingNumbers];
        }
        MaxExp[SubCounter] = FindMaxExp(SubExp,ManNumbers);
    }


    int BlockDotSum[BlockNumbers] = {0};
    int BlockSum[BlockNumbers] = {0};
    int Dot[Half_ManNumbers];

Sub_Block_Loop:
    for(int SubDotCounter=0;SubDotCounter<BlockNumbers;SubDotCounter++)
    {
        // set all the mans for the block
//#pragma HLS unroll
#pragma HLS pipeline
    	int SubDotNumber = SubDotCounter * Half_ManNumbers;

Sub_Block_Loop2:
        for(int ManTransCounter=0;ManTransCounter<Half_ManNumbers;ManTransCounter++)
        {
            //compute the gap between exp and expMax
//#pragma HLS unroll
#pragma HLS pipeline
        	int SubDotNumber0 = SubDotNumber + ManTransCounter;//first number's order in the input
            int SubDotNumber1 = SubDotNumber + ManTransCounter + Half_FloatingNumbers;//second number's order in the input

            int ExpGap0 = MaxExp[SubDotCounter] - EXP[SubDotNumber0];
            int ExpGap1 = MaxExp[SubDotCounter] - EXP[SubDotNumber1];

            // set the man
            ManBlock[SubDotNumber0] = MAN[SubDotNumber0] >> ExpGap0;
            ManBlock[SubDotNumber1] = MAN[SubDotNumber1] >> ExpGap1;

            ManBlock[SubDotNumber0] = ManBlock[SubDotNumber0] >> Resolution;
            ManBlock[SubDotNumber1] = ManBlock[SubDotNumber1] >> Resolution;

            Dot[ManTransCounter] = DecimalDot(ManBlock[SubDotNumber0],ManBlock[SubDotNumber1]);
        }

        BlockSum[SubDotCounter] = DecimalPlus(Dot);
        //get the Result
        BlockPiont = (22 - MaxExp[SubDotCounter]- Resolution) * 2;

        resultFloat[SubDotCounter] = (float)BlockSum[SubDotCounter] / pow(2,BlockPiont);
    }

    //get the SUM
    float TotalBlockSum = 0;
    TotalBlockSum = FloatingPlus(resultFloat);
    printf("\nTotalBlockSum = %f\n",TotalBlockSum);

    return TotalBlockSum;
}
