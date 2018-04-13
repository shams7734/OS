#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<termios.h>
#include<signal.h>
 			
 
int main(int argc,char *argv[])
 {
	int i,j,k,l,status,status1,status2=0,m,n,b;
	char *ch,*str,*str1,*use;
	char *ch1[10],*ch2[10];
	pid_t process_id;
	size_t size;

	ch=malloc(sizeof(char) * 50);         /* Dynamic memory allocation  */

	str1=malloc(sizeof(char) * 50);
	str=malloc(sizeof(char) * 50);
	
	for(i=0;i<10;i++)
		ch1[i]=malloc(sizeof(char) * 50);
	for(i=0;i<10;i++)
		ch2[i]=malloc(sizeof(char) * 50);
	while(1)
	{

		for(i=0;i<10;i++)
			ch1[i]=(char *)NULL;

		for(i=0;i<10;i++)
			ch2[i]=(char *)NULL;
	
		i=0,j=0,k=0,status=0,status1=0,status2=0,l=0,m=0,n=0,b=0;
		getcwd(ch,size);
		printf("\nshams@shams-ali:~$%s ",ch);
                //printf("%d\n",status);
		getline(&ch,&size,stdin);


		if(feof(stdin))               /* Ctrl+D Execution  */
		  {
		    printf("\n");
		    exit(1);
		  }
 		
		if(!strcmp(ch,"\n")) 
			continue;


		for(i=0;i<strlen(ch);i++)
			if(ch[i] == '\n')
			{
				ch[i] = '\0';break;
			}

		for(i=0;i<strlen(ch);i++)
			if(ch[i] == '|')
			{
				printf("Error: Command not found.");continue;
			}
		
		i=strcmp(ch,"exit");
		if(i==0)                     /* Execution of exit  */
		exit(1);
		
		
		
		i=0;
		str1=strtok(ch,"|");          /*Parsing the entered string and storing into string array */
		if(strlen(str1) != strlen(ch))
			status2 = 7;	
		ch2[i]=str1;
		i++;
		
		while(str1!=NULL)
		 {
			str1=strtok(NULL,"|");
			ch2[i]=str1;
			i++;
		 }

		m=i;

		
		
		ch2[i] = (char *)NULL; 

		i=0,j=0;
		
		for(i=0;i<m-1;i++)
		{
			str1=strtok(ch2[i]," ");          /*Parsing the entered string and storing into string array */
			ch1[j]=str1;
			j++;
		
			while(str1!=NULL)
			 {
				str1=strtok(NULL," ");
				ch1[j]=str1;
				j++;
			 }
		}
	
		m=j;
		
		ch1[j] = (char *)NULL; 

		/* code for execution of pipe */		

		if(status2==7)
		{
		   	printf("shams\n");
		    for( i=0; i<m-1; i++)
		    {
			int pd[2];
			pipe(pd);

			if (!fork()) {
			    dup2(pd[1], 1); // remap output back to parent
			    execvp(ch1[i],ch1);
			    perror("exec");
			    abort();
			}

			// remap output from previous child to input
			dup2(pd[0], 0);
			close(pd[1]);
		    }

		    execvp(ch1[i],ch1);
		    perror("exec");
		    abort();
		    status2=0;
	       }
		else{
         /* Execution of &  */

		for(l=0;l<j-1;l++)
		{
			
		        if(!(strcmp(ch1[l],"&")))
			{
			   status=5;
			   ch1[l]=(char *)NULL;
			}
			
			  
		}

	 /* Execution of cd command  */

	 j = strcmp(ch1[0],"cd");
	 if(j==0)
		k=1;	
	 if(k==1)
		{ 
		  strcpy(str,ch1[1]);
		  l=chdir(str);
		  if(l==-1){printf("Invalid directory\n");continue;}
		  else
		  {status1=1;continue;}    /* To skip the rest and continue from beginning  */
		}
	else
	 {

		 if ((process_id = fork()) < 0)            /* fork a child process  */
	   	   {     
		     printf("*ERROR: Child process can not be forked.\n");
		     exit(1);
		   }
		 else if (process_id == 0) 		   /* for the child process: */
		   {  
			if(status==5)
			{
				execvp(ch1[0], ch1);
				status =0;
			}
			else
			{
				execvp(ch1[0], ch1);
				waitpid(process_id,NULL,0);
			}
			       
		         if (execvp(ch1[0], ch1) < 0)         /* execute the command  */
			{     
		                printf("*ERROR: Command not found.\n");
 		                exit(1);
		        }  
		 
		   }

		
		 else 				/* for the parent */               
		 {
			if(status==5)
				{}
			else
				waitpid(process_id,NULL,0);
			status =0;
		 }                          /* wait */
		       
	  }
	}

      
   }  


}	



