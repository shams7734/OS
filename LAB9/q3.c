#include<stdio.h>
				#include<stdlib.h>

				int a;
				void test(int x);
				void test(int x)
				{
					printf("Address of test i.e function(test) = %p\n", (void *)&x);
				}

				int main()
				{
					int b,*p;
					p = (int *)malloc(4*sizeof(int));
					printf("Address of stack = %p\n",(void *)&b);
					printf("Address of heap = %p\n", (void *)&p);
					printf("Address of data segment = %p\n",(void *)&a);
					printf("Address of code segment = %p\n",(void *)&main);
					test(7);
					return 0;
				}
