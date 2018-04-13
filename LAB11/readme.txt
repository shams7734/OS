#######********This is readme for Lab11 assignment based on OS_Memory*****######

Question 1 : 

		Paging divides the linear address space into fixed-size pages. Pages can be mapped into the physical address space 
		or external storage.
		
		This fixed size is 4096 bytes for the x86_64 Linux kernel. To perform the translation from linear
		address to physical address, special structures are used. 
		
		Every structure is 4096 bytes and contains 512 entries (this only for PAE and IA32_EFER.LME modes).
		Paging structures are hierarchical and the Linux kernel uses 4 level of paging in the x86_64 architecture.
		
		The CPU uses a part of linear addresses to identify the entry in another paging structure which is at the 
		lower level, physical memory region (page frame) or physical address in this region (page offset)

		the Linux kernel in x86_64 uses 4-level page tables. Their names are:

    	a)Page Global Directory
		b)Page Upper Directory
		c)Page Middle Directory
		d)Page Table Entry

		The kernel always uses 4 levels of page tables, which can accommodate both normal 32 bit, PAE, and long mode.
		In normal 32 bit, you get this:
										                              /-> Page table
										PM4L -> PDT -> Page Directory --> Page table
																	  \-> Page table
		But in PAE, you get this:
								PM4L -> PDT -> 512 Page Directories -> 1024 Page tab
		
		And in Long mode, you get this:
										PM4L -> 512 PDTs -> 512 Page Directories -> 1024 Page tables	

		But because of the 4 levels always, the rest of the kernel has a unified interface across 32 bits, PAE, and long mode. 


		references: https://0xax.gitbooks.io/linux-insides/content/Theory/Paging.html
					http://stackoverflow.com/questions/12557267/linux-kernel-memory-management-paging-levels




Question 2: 


		Code :
			#include <stdio.h> 
			#include <stdlib.h>
			#include <pthread.h> 
			#include <unistd.h> 
			#include <sys/types.h>
			int main()
			{
				int a,b,*c;
				a=5,b=7;
				c=(int *)malloc(4*sizeof(int));
				printf("the pid of above program is::%d\n", getpid());
				while(1);
	
			}

		Output of the code is:    the pid of above program is::2626
														    // Infinite loop continues...
		
		shams@shams-arrow:~/Desktop$ cat /proc/2626/maps		
		00400000-00401000 r-xp 00000000 08:09 137962                             /home/shams/Desktop/a.out
		00600000-00601000 r--p 00000000 08:09 137962                             /home/shams/Desktop/a.out
		00601000-00602000 rw-p 00001000 08:09 137962                             /home/shams/Desktop/a.out
		02077000-02098000 rw-p 00000000 00:00 0                                  [heap]
		7fb7a359a000-7fb7a375a000 r-xp 00000000 08:09 1839779                    /lib/x86_64-linux-gnu/libc-2.23.so
		7fb7a375a000-7fb7a3959000 ---p 001c0000 08:09 1839779                    /lib/x86_64-linux-gnu/libc-2.23.so
		7fb7a3959000-7fb7a395d000 r--p 001bf000 08:09 1839779                    /lib/x86_64-linux-gnu/libc-2.23.so
		7fb7a395d000-7fb7a395f000 rw-p 001c3000 08:09 1839779                    /lib/x86_64-linux-gnu/libc-2.23.so
		7fb7a395f000-7fb7a3963000 rw-p 00000000 00:00 0 
		7fb7a3963000-7fb7a3989000 r-xp 00000000 08:09 1839751                    /lib/x86_64-linux-gnu/ld-2.23.so
		7fb7a3b6d000-7fb7a3b70000 rw-p 00000000 00:00 0 
		7fb7a3b86000-7fb7a3b88000 rw-p 00000000 00:00 0 
		7fb7a3b88000-7fb7a3b89000 r--p 00025000 08:09 1839751                    /lib/x86_64-linux-gnu/ld-2.23.so
		7fb7a3b89000-7fb7a3b8a000 rw-p 00026000 08:09 1839751                    /lib/x86_64-linux-gnu/ld-2.23.so
		7fb7a3b8a000-7fb7a3b8b000 rw-p 00000000 00:00 0 
		7ffd34ad1000-7ffd34af2000 rw-p 00000000 00:00 0                          [stack]
		7ffd34bb4000-7ffd34bb6000 r--p 00000000 00:00 0                          [vvar]
		7ffd34bb6000-7ffd34bb8000 r-xp 00000000 00:00 0                          [vdso]
		ffffffffff600000-ffffffffff601000 r-xp 00000000 00:00 0                  [vsyscall]


		The address space:
							Stack
							  |
							  |
							Heap
							  |
							  |
						  Data Segment
						  	  |
						  	  |
						  Code Segment
		
		In the above output we can see that we can see that heap segment is created and its lies just above the data segment
		(02077000-02098000), this shows heap memory is created by increasing program break location (i.e.) using brk syscall).		
		
		By the above output we can clearly see the address of the stack segement and i.e. (7ffd34ad1000-7ffd34af2000) and 
		the address of the heap segment of the code and i.e. (02077000-02098000).
		The topmost segment in the process address space is the stack, which stores local variables and function parameters 
		in most programming languages.
		Each thread in a process gets its own stack.
		
		Speaking of the heap, it comes next in our plunge into address space. The heap provides runtime memory allocation, 
		like the stack, meant for data that must outlive the function doing the allocation, unlike the stack.
		
		The act of maintaining separate heap and freelist data structures for each thread is called per thread arena.
		For 32 bit systems:
     			Number of arena = 2 * number of cores.
		For 64 bit systems:
     			Number of arena = 8 * number of cores.
		
		If we run the same piece of code on different terminals the addresses are different each time.
		
		
	
	
		references: https://gist.github.com/CMCDragonkai/10ab53654b2aa6ce55c11cfc5b2432a4 

					http://duartes.org/gustavo/blog/post/anatomy-of-a-program-in-memory/ 

					https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/
	
		
