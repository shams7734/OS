#include<stdio.h>
#include "threads/thread.h"
#include "sort.h"
#include "random.h"
#include<kernel/console.h>

int a[10],b[1000],i,j,temp,k;
tid_t tid;

void test_sort(void);
void test_sort1(void);
void test_sort2(void);
void random_no(void);
void sorting(void);
void print(void);

void test_sort(void)
{
	printf("Thread ID is : %d\n",tid);
	
	random_bytes(b,100*sizeof(int));
	
	for(i=0;i<100;i++)
	{
		for(j=0;j<10;j++)
		{
			if(b[i]<b[j])
			{
				temp=b[i];
				b[i]=b[j];
				b[j]=temp;
			}
		}
	}
	
	for(i=0;i<100;i++)
	{
		//printf("%d\n",b[i]);
		j=i;
	}
	for(i=0;i<100000000;i++)
	{
		for(j=0;j<10;j++)
		{
			k=j;
		}
	}
	printf("\nyello! ni aya mai!. This is thread 1 executing. Itte time bad apna time aya.\n");
	
	
}
void test_sort1(void)
{
	random_bytes(a,10*sizeof(int));
	
	printf("Thread name is : %s\n",thread_current ()->name);
	

}
void test_sort2(void)
{
	random_bytes(a,10*sizeof(int));
	
	printf("Thread_Priority is : %d\n",thread_get_priority ());
	
	
}

void random_no(void)
{
	
	random_bytes(a,10*sizeof(int));
	for(i=0;i<10;i++)
		a[i]=a[i]/99999999;
}

void sorting(void)
{
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
}

void print(void)
{
	printf("The sorted array is :\n");
	for(i=0;i<10;i++)
	{
		printf("%d\n",a[i]);
	}
	
}

void test_sortn(void)
{

	printf("\n###########----Thread1 Created.----##########\n");
	tid = thread_create ("thread_sort",PRI_MAX, (thread_func *)test_sort, NULL);
	//thread_print_stats();
	thread_yield();
	printf("##########----Thread1 Ended------##########\n\n\n");
	//thread_print_stats();
	
	
	printf("###########----Thread2 Created.----##########\n");
	thread_create ("thread_sort1",PRI_MAX, (thread_func *)test_sort1, NULL);
	//thread_print_stats();
	thread_yield();
	printf("##########----Thread2 Ended------##########\n\n\n");
	//thread_print_stats(); 
	
	
	printf("###########----Thread3 Created.----##########\n");
	thread_create ("thread_sort2",PRI_MAX, (thread_func *)test_sort2, NULL);
	//thread_print_stats();
	thread_yield();
	printf("##########----Thread3 Ended------##########\n\n\n");
	//thread_print_stats();
	
	
	printf("********####---Extra 30 percent part Execution---####********\n\n\n");
	
	printf("###########----Thread random_number Created.----##########\n");
	thread_create ("thread_random",PRI_DEFAULT, (thread_func *)random_no, NULL);
	printf("\nExecutig Thread random_number\n\n");
	thread_yield();
	printf("##########----Thread random_number Ended------##########\n\n\n");
	
	
	printf("###########----Thread sorting Created.----##########\n");
	thread_create ("thread_sorting",PRI_DEFAULT, (thread_func *)sorting, NULL);
	printf("\nExecutig Thread sorting\n\n");
	thread_yield();
	printf("##########----Thread sorting Ended------##########\n\n\n");
	
	
	printf("###########----Thread print Created.----##########\n");
	thread_create ("thread_print",PRI_DEFAULT, (thread_func *)print, NULL);
	printf("\nExecutig Thread print\n\n");
	thread_yield();
	printf("##########----Thread print Ended------##########\n\n");
	
	thread_print_stats();
	
}


	
