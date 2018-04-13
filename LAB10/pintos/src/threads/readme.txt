##########---------This is readme file for pintos assignment.  ----------##########


->First I installed qemu and working condition for it i.e. tcsh
	And i have to make certain changes in .bashrc and .tcshrc file.

-> In order to install qemu i followed the following link from youtube 
   "https://www.youtube.com/results?search_query=pintos+install".

-> The path for that is "/home/shams/Desktop/os-pg/pintos/src/threads/..."

-> In order to build or compile file use "make" in the following directory 
   "/Desktop/os-pg/pintos/src/threads"

	And to run the code use command "pintos run alarm-multiple"

->Part 1
	I made my own test case named hello.c and performed it using 
	"pintos run alarm-multiple".

	I order to do that I have to make a file name "hello.c" ,
	"hello.h" in the directory "/home/Desktop/os-pg/pintos/src/tests/threads"

	And have to do certain changes in the following files:

	In directory "/home/Desktop/os-pg/pintos/src/tests/threads" file "tests.c"
	was modified as :     {"hello",test_hello},
                              {"sort",test_sort}, at line 41 and 42 these lines were inserted.

	In directory "/home/Desktop/os-pg/pintos/src/tests/threads" file "tests.h"
	was modified as :     extern test_func test_hello;
                              extern test_func test_sort;  These line were inserted at line no. 
	35 and 36 respectively.

	In directory "/home/Desktop/os-pg/pintos/src/tests/threads" file "Make.tests"
	was modified as :     tests/threads_SRC += tests/threads/hello.c
	This line was inserted at line no. 39.

	These changes were made to use the function to perform the corresponding task 
	associated with that function.

->Part 2

	In this part I have to include both the functions i.e. print something and 
	sorting of 10 random numbers in single file and use that by creating thread.

	In sorting instruction was given to use random_bytes to generate 10 random numbers
	but by using that the numbers I got were too large so I divided them all with some number 
	to look better.

	Thread creation was done using the function :
	"thread_create (const char *name, int priority,thread_func *function, void *aux)".

	The modified function for thread creation used by me to create the thread is :
	"thread_create ("thread_sort",PRI_MAX, (thread_func *)test_sort, NULL);"

	Here actually there is no effect of changing the value of priority because it defined 
	in that way only. So in order to make that work I have to use the function timer_sleep()
	to make threads work the way it should work and perform the operation that it was supposed
	to perform.

	schedule() is responsible for switching threads.schedule() can only be called by three
	functions i.e. thread_block(), thread_exit(), and thread_yield().
	->It records the current thread in local variable.
	->Then it determines the next thread to run as local variable next 
          (by calling next_thread_to_run()), and then calls switch_threads() 
	  to do the actual thread switch.
	

