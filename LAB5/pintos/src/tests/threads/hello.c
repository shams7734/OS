#include<stdio.h>
#include "threads/thread.h"
#include "hello.h"
#include "random.h"
#include<kernel/console.h>
#include "devices/timer.h"
void test_hello(void)
{
	printf("###########----Hello World.This is Shams.----##########\n");
	thread_create ("thread_sort",PRI_MAX, (thread_func *)test_sort, NULL);
	timer_sleep(200); 
}
void test_sort(void)
{
	int a[10],i,j,temp;
	random_bytes(a,10*sizeof(int));
	for(i=0;i<10;i++)
		a[i]=a[i]/99999999;
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

	
