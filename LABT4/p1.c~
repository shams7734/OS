#include<stdio.h>
#include<stdlib.h>
#include<linux/kernel.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdbool.h>

int main()
{
	bool flag[2] = {false, false};
	int turn,count=0,i=0;
	
	pid_t pid;
	
	while(1)
	{
		pid = fork();
		if(pid<0)
		{
			printf("Something wrong happened with process\n");
			exit(0);
		}
		if(pid==0)
		{
			printf("Child process started\n");
			flag[0] = true;
			turn = 1;
			while (flag[1] && turn == 1)
			{}
			count++; 
			printf("Count is %d\n",count);    
				 
			flag[0] = false;
		
		}
		
		else
		{
			printf("Parent process waiting\n");
			flag[1] = true;
			turn = 0;
			while (flag[0] && turn == 0)
			{}
			count--;
			printf("Count is %d\n",count);        
			flag[1] = false;
			
			wait(NULL);
			
		}
		
		i++;
	}	
		
}
