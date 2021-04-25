#include <stdio.h>
#include <stdlib.h>

#define FloatingNumbers 10
#define Resolution 15


//transform the floating number to char
void getFloatBin(float num,char bin[32])
{
    int t = 1;
    int *f = (int*)(&num);
    for(int i=0;i<32;i++)
    {

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

    DecimalToBinary = DecimalToBinary / pow(2,j);
    remainder = DecimalToBinary%2;
    decimalNumber = remainder;

    return decimalNumber;
}

int FindMaxExp(int x[] , int n)
{
    int maxExp,i;
    maxExp=x[0];
    for(i=1;i<n;i++)
    {
        if(maxExp < x[i])
        {
            maxExp = x[i];
        }
    }
    return maxExp;
}



int DecimalPlus(int ManBlock[FloatingNumbers])
{
    int Sum = 0;
    for(int i=0;i<FloatingNumbers;i++)
    {
        Sum = Sum + ManBlock[i];
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
	float resultFloat = 0.0;


	int man[25]={0};
	int ManSum = 0;
	// gain the exps and mans of all floating point numbers.
	for(int j=0;j<FloatingNumbers;j++)
	{
        char floating[32];
        //man[j][1] = 1;
        man[1] = 1;
        printf("Floating point is :%f",test[j]);
        printf("exp in Binary is");
        getFloatBin(test[j],floating);

        //devide all floating point nummbers into signal, exp and man
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
        for(int expCount=0;expCount<8;expCount++)
        {
            expSum += convertBinaryToDecimal((int)exp[7-expCount],expCount);
        }
        expSum = expSum - 127;
        printf("exp = %d\n ",expSum);

        // get the Man for each number(Decimal)
        ManSum = 0;
        for(int ManCount=0;ManCount<24;ManCount++)
        {
            ManSum += convertBinaryToDecimal((int)man[23-ManCount],ManCount);
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
    int MaxExp = FindMaxExp(EXP,FloatingNumbers);
    printf("MaxEXP =  %d\n",MaxExp);

    // set all the mans for the block
    for(int ManTransCounter=0;ManTransCounter<FloatingNumbers;ManTransCounter++)
    {
        //compute the gap between exp and expMax
        int ExpGap = MaxExp - EXP[ManTransCounter];

        // set the man
        ManBlock[ManTransCounter] = MAN[ManTransCounter] >> ExpGap;

        printf("Man[%d] = %d",ManTransCounter, ManBlock[ManTransCounter]);
        printf( "\n");

        ManBlock[ManTransCounter] = ManBlock[ManTransCounter] / pow(2,Resolution);
        printf("Man00[%d] = %d",ManTransCounter, ManBlock[ManTransCounter]);
        printf( "\n");
    }

    //get the SUM
    int BlockSum = 0;
    BlockSum = DecimalPlus(ManBlock);
    printf("\nBlockSum = %d\n",BlockSum);

    //get the Result
    int BlockPiont = 22 - MaxExp- Resolution;

    resultFloat = (float)BlockSum / pow(2,BlockPiont);

    printf( "%f\n",resultFloat);




    // dot product for any two numbers in the blocks
    int dotTest1 = 9; //any one in the block
    int dotTest2 = 8; //any one in the block
    int ManTest1[24]={0};
    int ManTest2[24]={0};


    //get the binary for the first number
    printf("\nManBlock[dotTest1] = ",ManTest2);
    int ManTestCounter = 23;
    for(ManTestCounter; ManTestCounter>=0;ManTestCounter--)
    {
        ManTest1[ManTestCounter] = DecimalToBinary(ManBlock[dotTest1],ManTestCounter);
        printf("%d",ManTest1[ManTestCounter]);
    }

    //get the binary for the second number
    printf("\nManBlock[dotTest1] = ",ManTest2);
    ManTestCounter = 23;
    for(ManTestCounter; ManTestCounter>=0;ManTestCounter--)
    {
        ManTest2[ManTestCounter] = DecimalToBinary(ManBlock[dotTest2],ManTestCounter);
        printf("%d",ManTest2[ManTestCounter]);
    }

    // dot product

    int Dot = 0;
    Dot = DecimalDot(ManBlock,dotTest1,dotTest2);
    printf("\n%d",Dot);

    float DotFloat = 0.0;
    int DotResolution = 0;
    DotResolution = (17 - Resolution) * 2;
    DotFloat = (float)Dot / pow(2,DotResolution);
    printf("\n%f",DotFloat);

    return resultFloat;

}

int main()
{
	float test[FloatingNumbers] = {15.1,17.0,18.2,19.3,20.0,21.0,22.0,23.5,24.0,32.0};
	float resultFloat = 0.0;

	resultFloat = Test_main(test);

    printf("\n%f",resultFloat);
	return 0;

}
