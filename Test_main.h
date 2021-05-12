#ifndef FIR_H_
#define FIR_H_
#define FloatingNumbers 32
#define Resolution 15
#define BlockNumbers 8

void getFloatBin(float num,char bin[32]);

float Test_main(float test[FloatingNumbers]);

float BinaryToDecimal(int BinaryToDecimal, int i);

int DecimalToBinary(int DecimalToBinary, int j);

int FindMaxExp(int x[] , int n);

int DecimalPlus(int ManBlock[FloatingNumbers]);

float FloatingPlus(float resultFloat[FloatingNumbers/(2*BlockNumbers)]);

int DecimalDot(int i, int j);

#endif
