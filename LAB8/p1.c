#include<stdio.h>
#include<stdlib.h>
int main()
{
	int amax,bmax,cmax,aav,bav,cav,arr[5],j,k;
	int p[5],ac[5],bc[5],cc[5],da[5],db[5],dc[5],i,temp=0;
	int na[5],nb[5],nc[5],set;
	printf("Types of resources are A,B,C\n");
	printf("Enter Max isntances of A,B,C\n");
	scanf("%d %d %d",&amax,&bmax,&cmax);
	for(i=0;i<5;i++)
	{
		printf("Enter Current allocation of A,B,C for 5 processes\n");
		scanf("%d %d %d",&ac[i],&bc[i],&cc[i]);
	}

	for(i=0;i<5;i++)
		temp=temp+ac[i];
		aav=temp;
		aav=amax-temp;
		
	temp=0;
	for(i=0;i<5;i++)
		temp=temp+bc[i];
		bav=temp;
		bav=bmax-temp;
		
		
	temp=0;
	for(i=0;i<5;i++)
		temp=temp+cc[i];
		cav=temp;
		cav=cmax-temp;
		
	//printf("%d\t %d\t %d\t",aav,bav,cav);
	
	temp=0;	
	for(i=0;i<5;i++)
	{
		printf("Max demand of A,B,C for 5 processes\n");
		scanf("%d %d %d",&da[i],&db[i],&dc[i]);
	}
	
			
	for(i=0;i<5;i++)
		na[i]=da[i]-ac[i];
		
	for(i=0;i<5;i++)
		nb[i]=db[i]-bc[i];
		
	for(i=0;i<5;i++)
		nc[i]=dc[i]-cc[i];

	printf("Need matrix is \n");
	for(i=0;i<5;i++)
	{
		printf("%d\t%d\t%d\n",na[i],nb[i],nc[i]);
	}

	printf("Order is \n");
	for(i=0;i<5;i++)
	{
		if( na[i]<=aav && nb[i]<=bav && nc[i]<=cav )
		{
			printf("P %d\t",i);
			set=1;
		}
		else
		{
			arr[j]=i;
			j++;
		}
	}
	
	for(i=0;i<j;i++)
	{
		for(k=0;k<j;k++)
		{
			if( na[(arr[i])]<=na[(arr[k])] && nb[(arr[i])]<=nb[(arr[k])] && nc[(arr[i])]<=nc[(arr[k])] )
			{
				temp=arr[i];
				arr[i]=arr[k];
				arr[k]=temp;
			}
		}
	}
	
	for(i=0;i<j;i++)
		printf("P %d\t",arr[i]);
	
	if( set!=1 )
		printf("Unsafe . Deadlock occured.\n");
		
	else
		printf("Safe sequence possible.\n");
	
}
