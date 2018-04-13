/##########****Readme file for lab9 assignment "Memomry"  *****###########\

Question 1 :

	malloc() : 	It is used for dynamic memory allocation at runtime.It is a C library function that allocates the 
				requested memory and returns a pointer to it.Allocates requested size of bytes and returns 
				a void pointer pointing to the first byte of the allocated space.
				This function returns a pointer to the allocated memory, or NULL if the request fails.
				
				e.g: int *x;
					 x = (int*)malloc(50 * sizeof(int));    
					 free(x); 
				
				Precautions: a) Always check if the call was successful.
							 b) Type cast the pointer properly.
							 c) if allocating memory for a string, don't forget to allocate , one 
							    extra byte for the null terminator of the string.
				
				
	calloc() :  It is used for memory allocation at runtime.Allocates space for an array of elements, initialize 
				them to zero and then return a void pointer to the memory.calloc function is normally used for 
				allocating memory to derived data types such as arrays and structures. If it fails to locate enough
			    space it returns a NULL pointer.
			    
			    e.g: struct employee
					{
					 char *name;
					 int salary;
					};
					typedef struct employee emp;
					emp *e1;
					e1 = (emp*)calloc(30,sizeof(emp));

				
				
				
   realloc() :  The function realloc() reallocates a memory block with a specific new size. If you call realloc() 
   				the size of the memory block pointed to by the pointer is changed to the given size in bytes. 
   				This way you are able to expand and reduce the amount of memory you want to use (if available of course.)
   				If the pointer is NULL then the function will behave exactly like the function malloc(). It will assign
   				a new block of a size in bytes and will return a pointer to it.
   				If the size is 0 then the memory that was previously allocated is freed as if a call of the function 
   				free() was given. It will return a NULL pointer in that case.
   				
   				e.g: void * realloc ( void * ptr, size_t size );
   				
   				Precautions: a) While deleting a location pointed to by a pointer, make sure that the pointer points 
   								to null, otherwise there are dangling pointers and memory leaks.
   							 b) Pointers increment/decrement according to their size and not the value pointed to by 
   							 	them. So be careful while incrementing/decrementing pointers.

   				
   				
    free() :   It releases previously allocated memory.If ptr is NULL, no operation is performed.
    		   If free(ptr) has already been called before, undefined behavior occurs.
    		   
    		   e.g: void free (void * ptr); 
    		   
    		   Precautions: a) free should not be used to deallocate a pointer which was already deallocated.
    		   
    		   
    alloca() : Allocate memory that is automatically freed.	The alloca() function allocates size bytes of space in the stack
       		   frame of the caller.  This temporary space is automatically freed when the function that called alloca() returns 
       		   to its caller.
       		   The alloca() function returns a pointer to the beginning of the allocated space.  If the allocation causes stack 
       		   overflow, program behavior is undefined.	
       		   
       		   e.g:  #include <alloca.h>
       				 void *alloca(size_t size); 
       				 
       				 #define LARGE 100
					 char *str = (char *) alloca(LARGE);
       				 
       		   Precautions:  a)  If the allocation causes stack overflow, program behavior is undefined. Therefore care should 
       		   					 be taken while using alloca();

    
    
    longjmp() : The C library function void longjmp(jmp_buf environment, int value) restores the environment saved by the most 
    			recent call to setjmp() macro in the same invocation of the program with the corresponding jmp_buf argument.
    			This function does not return any value.
    			
    			e.g: void longjmp(jmp_buf environment, int value)
    			
    				 environment − This is the object of type jmp_buf containing information to restore the environment at the 
    				 setjmp's calling point.
    				 
    				 value − This is the value to which the setjmp expression evaluates.
    				 
    				 int main()
					{
					   int val;
					   jmp_buf env_buffer;

					   val = setjmp( env_buffer );
					   
					   if( val != 0 ) 
					   {
						  printf("Returned from a longjmp() with value = %s\n", val);
						  exit(0);
					   }
					   printf("Jump function call\n");
					   jmpfunction( env_buffer );
					   
					   return(0);
					}

					void jmpfunction(jmp_buf env_buf)
					{
					   longjmp(env_buf, "tutorialspoint.com");
					}
    				   
  
     brk() : brk() change the location of the program break, which defines the end of the process's data segment 
     		 (i.e., the program break is the first location after the end of the uninitialized data segment).  Increasing 
     		 the program break has the effect of allocating memory to the process; decreasing the break deallocates memory.
  			 brk() sets the end of the data segment to the value specified by addr, when that value is reasonable, the 
  			 system has enough memory, and the process does not exceed its maximum data size .
  			 
  			 On success, brk() returns zero.  On error, -1 is returned, and errno is set to ENOMEM.
  			 
  			 e.g: #define _XOPEN_SOURCE_EXTENDED 1
				  #include <unistd.h>

				  int brk(void *addr);
  
  
    
    
    mmap() :  mmap() creates a new mapping in the virtual address space of the calling process.  The starting address for 
    		  the new mapping is specified in addr.  The length argument specifies the length of the mapping.
    		  The mmap() function shall establish a mapping between the address space of the process at an address pa for 
    		  len bytes to the memory object represented by the file descriptor fildes at offset off for len bytes.
    		  A successful mmap() call shall return pa as its result.
    		  
    		  On success, mmap() returns a pointer to the mapped area.  On error, the value MAP_FAILED (that is, (void *) -1) 
    		  is returned, and errno is set to indicate the cause of the error.
    		  
    		  Use of mmap() may reduce the amount of memory available to other memory allocation functions.
    		  The mmap() function allows access to resources via address space manipulations, instead of read()/ write(). 
    		  Once a file is mapped, all a process has to do to access it is use the data at the address to which the file was mapped.
    		  
    		  e.g: #include <sys/mman.h>

				   void *mmap(void *addr, size_t len, int prot, int flags,int fildes, off_t off);
       			   
       		  
    munmap() :  The munmap() system call deletes the mappings for the specified address range, and causes further references 
    			to addresses within the range to generate invalid memory references.  The region is also automatically unmapped 
    			when the process is terminated.  On the other hand, closing the file descriptor does not unmap the region.
  
  				On success, munmap() returns 0.  On failure, it returns -1, and errno is set to indicate the cause of the error 
  				(probably to EINVAL).
  
  				e.g: #include <sys/mman.h>

                     int munmap(void *addr, size_t len);
                     
                The munmap() function is only supported if the Memory Mapped Files option or the Shared Memory Objects option is supported.
                     
  				
  				Precautions: a) To avoid corruption in multithreaded applications, mutexes are used internally to protect the 
  								memory-management data structures employed by these functions.
  							 b) Each arena is a large region of memory that is internally allocated by the system (using brk(2) 
  							 	or mmap(2)), and managed with its own mutexes.
  						     c) In a multithreaded application in which threads simultaneously allocate and free memory, there 
  						        could be contention for these mutexes.
  						     d) To scalably handle memory allocation in multithreaded applications, glibc creates additional 
  						     	memory allocation arenas if mutex contention is detected
  
  
 
 
    		   
Question 2 :
		
		Memory Leak: A memory leak is a type of resource leak that occurs when a computer program incorrectly manages 
		 			 memory allocations in such a way that memory which is no longer needed is not released.
		 			 In object-oriented programming, a memory leak may happen when an object is stored in memory but cannot be 
					 accessed by the running code.
					 A memory leak has symptoms similar to a number of other problems and generally can only be diagnosed by 
					 a programmer with access to the program's source code.A memory leak reduces the performance of the computer 
					 by reducing the amount of available memory.
					 
					 
	   Code : 
	   
	   		 #include<stdio.h>
	   		 #include<stdlib.h>
	   		 int main()
	   		 {
	   		 	int a,b,*p;
	   		 	a=5,b=10;
	   		 	p=(int *)malloc(a*sizeof(int));
	   		 	return 0;
	   		 }
	   		 
	   		 This code shows memory leakage. In this code we allocated at runtime but at the end of the code after its use 
	   		 we did not deallocate that memory.So that memory can not be used by other process or programs and this will 
	   		 reduce the amount of available memory .
	   		 
	   Fixing Memory leak: This can be fixed if the alloated memory is freed using the function free() and make it available 
	 					   for the use or allocation of other processes.
	 					   
	 					   
	   Best Practices:  a) Assign NULL to a pointer after freeing (or deleting) it. This prevents the program from crashing should 
					       the pointer be accidentally freed again. Calling free or delete on NULL pointers is guaranteed 
					       not to cause a problem.
					    b) Do not allocate and deallocate memory in a loop as this may slow down the program and may 
						   sometime cause security malfunctions.
						c) When storing secrets such as passwords in memory, overwrite them with random data before 
						   deleting them. Need to note that free and delete merely make previously allocated memory unavailable, 
						   they don't really 'delete' data contained in that memory.
						d) Use unsigned integer types to hold the number of bytes to be allocated, when allocating memory dynamically. 
						   This weeds out negative numbers. Also check the length of memory allocated against a maximum value.
						e) When using C and C++ code together, if new has been used to allocate memory, use delete to free it. 
				    	   Do not use free. Likewise, if malloc or calloc has been used to allocate memory, use free when deallocating. 
				    	   Do not use delete.
				    	   
				    	   
				    	   

Question 3:  

		Code :  #include<stdio.h>
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

				
	   Observation : The addresses for stack and heap changes on different terminal.
	   				 But addresses of data segment and code segment remains same on different terminal.
	   				 I have attached screenshots also.






Question 4:		
		
		Code :  #include<stdio.h>
				int main()
				{
					int x=0;
					printf("Hello OS!!\n");
					return 0;
				}
				
				
	   Observation : The address binding takes place at runtime->loadtime not at runtime->executiontime.
	   				 I have attached screenshots for the same. 
   
   
   
   
   
   
    
