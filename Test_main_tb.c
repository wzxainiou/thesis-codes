#include <stdio.h>
#include <math.h>
#include "Test_main.h"

#define FloatingNumbers 32
#define Resolution 15

int main()
{
	float test[FloatingNumbers] = {15.1,16.0,16.0,16.0,16.0,16.0,16.0,17.0,18.2,19.3,20.0,21.0,22.0,23.5,24.0,32.0,
								   15.1,16.0,16.0,16.0,16.0,16.0,16.0,17.0,18.2,19.3,20.0,21.0,22.0,23.5,24.0,32.0};
	float result = 0.0;
	result = Test_main(test);

  printf("\n%f",result);
	return 0;

}
