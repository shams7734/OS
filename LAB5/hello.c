#include<stdio.h>
#include "hello.h"
#include<kernel/console.h>
void test_hello(void)
{
	printf("###########----Hello World.This is Shams.----##########\n");
}
void test_sort(void)
{
	int a[10],i,j,temp;
	random_bytes(a,10*sizeof(int));
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			if(a[i]<a[j])
			{
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		printf("%d\n",a[i]);
	}
}
	
