#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<unistd.h>

int main(int argc,char *argv[])
{ 
	 FILE *fp;
	 char ch, ch1[100],ch2[100],ch3[100],str;
	 int i,m,n,l,temp,o,q,h ;
	 float a,b,c,d,e,f,g,j=0.0,k=0.0;
	 float x,y,z,arr[20][20],total=0.0,um=0.0,sm,im=0.0;



	 // error handling for version 1
	  
	 if(argc <1 || (argc >1 && argc !=3) || argc >3)
	  {
	  printf("Error:Number of arguments entered did not match the requirement of the code.Please enter only two arguments.\n"); 
	  exit(1);
	  }  //error handling ends here
	 	 
	 else
	 {

		 //*########### version 1 ############*//
		 
		 if(argc == 1)
			 {
                                 printf("Version 1 executing\n");
				 printf("*########################*\n\n");
				
				 if((fp=popen("cat /proc/cpuinfo | grep 'model name' | uniq","r"))==NULL)
				  {
				    printf("cannot open file");
				    exit(1);
				  }	 
				 ch = fgetc(fp);
				 printf("The processor type is\t");
				 while(ch!=':')
				  {
				    ch = fgetc(fp);
				  }
				 while(ch!=EOF)
				  { 
				   printf("%c",ch);
				   ch = fgetc(fp);	
				  }
				 fclose(fp);



				 fp=popen("cat /proc/version","r");
				 ch=fgetc(fp);
				 printf("The kernel version is\t:");
				 while(ch!='(')
				 { 
				   printf("%c",ch);
				   ch = fgetc(fp);
				 }
				printf("\n");
				 fclose(fp);



				 fp=popen("cat /proc/meminfo","r");
				 ch=fgetc(fp);
				 printf("The amount of memory configured into this sytem is\t");
				  while(ch!=':')
				  {
				    ch = fgetc(fp);
				  }
				 while ( (ch!= EOF ))
				 {
				    if (ch == '\n')
					break;
				    printf("%c",ch);
				    ch = fgetc(fp); 
				 }
				 printf("\n");
				 fclose(fp);



				 fp=popen("cat /proc/uptime","r");
				 ch=fgetc(fp);
				 printf("The amount of time since the system was last booted is\t: ");
				 while(ch!=EOF)
				  {
				    printf("%c",ch);
				    ch = fgetc(fp);
				  }
				 fclose(fp);
			 }



	   //*########### version 2############*//

		else if(argc==3)  // error handling for version 2
		 {
	  	  if((isalpha(argv[1][0]) || isalpha(argv[2][0])))
		 {
		  printf("Error:Invalid arguments entered.Arguments must be integers.No characters allowed.\n");
		  exit(1);
		 }
		  else if( !(isalnum(argv[1][0])) || !(isalnum(argv[2][0])) )
		 {
		  printf("Error:Invalid arguments entered.Arguments must be integer.No characters and special characters allowed.\n");
		  exit(1);
		 }
		 else if (atoi(argv[2])<=0 || atoi(argv[1])<=0 )
		 {
		   printf("Error:Invalid arguments entered.Arguments must be positive integer.\n");
		   exit(1);
		 }

		 else if(atoi(argv[2])<atoi(argv[1]) )
		 {
		  printf("Error:Invalid arguments entered.arg[2] must be greater than arg[1].\n");
		  exit(1);
		 }     // error handling ends here.

			 m=atoi(argv[2]);
			 n=atoi(argv[1]);
			 o=m/n;
			 
			 
			 for(i=0;;i++)
			 {
			    a=0,b=0,c=0,d=0,e=0,f=0,j=0,k=0,l=0,g=0,h=0;
			    um=0,sm=0,im=0,total=0,x=0,y=0,z=0;
			 
			    for(q=0;q<o;q++)
			   { 
			  
			  fp=popen("cat /proc/meminfo | grep 'MemTotal' | uniq","r");
			 fscanf(fp,"%s",ch3);
			 fscanf(fp,"%s",ch3);
			 z=atoi(ch3);
			 fclose(fp);
			  
			 fp=popen("cat /proc/meminfo | grep 'MemFree' | uniq","r");
			 fscanf(fp,"%s",ch1);
			 fscanf(fp,"%s",ch1);
			 x=atoi(ch1);
			 a=(x/z)*100;
			 j=j+a;
			 fclose(fp);

			 fp=popen("cat /proc/meminfo | grep 'MemAvailable' | uniq","r");
			 fscanf(fp,"%s",ch2);
			 fscanf(fp,"%s",ch2);
			 x=atoi(ch2);
			 b=(x/z)*100;
			 k=k+b;
			 fclose(fp);
			  

			  

			 fp=popen("cat /proc/stat","r");
			 fscanf(fp,"%s",ch1); 
			 fscanf(fp,"%s",ch1);
			  i=0;
			 while(ch1[0]!='c')
			 {
			  arr[q][i]=atoi(ch1);
			  total = total+arr[q][i];
			  i++;
			  fscanf(fp,"%s",ch1);
			 }
			 
			 c=c+arr[q][0];
			 um=um+((c/total)*100);
			 
			 
			 d=d+arr[q][2];
			 sm=sm+((d/total)*100);

			 
			 e=e+arr[q][3];
			 im=im+((e/total)*100);

			 fclose(fp);



			  
			     fp=popen("cat /proc/stat","r"); 
			     fscanf(fp,"%s",ch1);
			     while(ch1[0]!='p')
			     {
			      fscanf(fp,"%s",ch1);
			     }
			     fscanf(fp,"%s",ch1);
			     x=atoi(ch1);
			     f=x+f;
			    
			     fclose(fp);


			     fp=popen("cat /proc/stat","r");
			     fscanf(fp,"%s",ch1);
			     while(ch1[2]!='x')
			     {
			      fscanf(fp,"%s",ch1);
			     }
			     fscanf(fp,"%s",ch1);
			     x=atoi(ch1);
			     y=y+x;
			     
			     fclose(fp); 


			     fp=popen("cat /proc/diskstats","r");
			     fscanf(fp,"%s",ch1);
			     while(ch1[0]!='s')
			     {
			      fscanf(fp,"%s",ch1);
			     }
			     fscanf(fp,"%s",ch1);
			     x=atoi(ch1);
			     l=l+x;
			    for(i=0;i<4;i++)
			    fscanf(fp,"%s",ch1);
			    x=atoi(ch1);
			    g=g+x;
			     
			     fclose(fp);
			   }
			        printf("Version 2 executing\n");
				printf("*########################*\n\n");


				printf("Percentage of Free memory is %f\n",j/o);
				printf("Percentage of Available memory is %f\n",k/o);
				printf("\n");
				
				printf("The percentage of time the processor(s) spend in user mode is %f\n",um/o);
				printf("The percentage of time the processor(s) spend in system mode is %f\n",sm/o);
				printf("The percentage of time the processor(s) spend in idle mode is %f\n",im/o);
				printf("\n");
				
				printf("The rate (number per second) of process creations in the system is %f\n",f/o);

				printf("\n");
				

				printf("The rate (number per second) of context switches in the kernel is %f\n",y/o);

				printf("\n");
				

				printf("The rate (number of blocks per second) of disk read in the system is %d\n",l/o); 
				printf("The rate (number of blocks per second) of disk write in the system is %f\n",g/o); 

			        sleep(m);



			  }  

			  
		}
			    
			   
	}


}

 
