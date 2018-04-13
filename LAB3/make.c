#include"make.h"

int main()
{
	float a,b;
	printf("Enter any number\t");
	scanf("%f",&a);
	if(a>0)
	{
		b=sqrt(a);
		printf("The square root of the number is %f\n",b);
	}

	else
		printf("Invalid number.\n");
}
