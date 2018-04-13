Submitted by SHAMS ALI 2015KUCP1034 and DEEPAK 2015KUCP1039 
Objective : The assignment is concerened to adding basic system calls to the pintos, a light weight os.

To add system call we follow these steps:
1. There is a file in src/lib named syscallnr, i.e. systemcall number, This file keep the number of system calls in the system and some basic system call have been provided with their numbers preloaded to do the project. If one wants to add a dummy system call, one has to take number of system call first.
2. Second step is to define the system call in sycall.c in userprog directory. It is the crucial step and one need to map the provided number to the given system call otherwise it can give errors.
3. After defining the system call and mapping we need to compile the userprog directory and check if there are any errors or undefined reference.
4. We then compile the examples directory which consist of some predeclared programs for testing our codes, one simple program is halt.

To run the system call using disk:
1. We need to create a disk, typically size we use is around 2 mb.
2. Then we load our executables into the file system that we created.
3. We can now run and implement the system call that we need to use.
Commands used in this process are:
pintos-mkdisk filesys.dsk --filesys-size=2
pintos -f -q
pintos -p ../../examples/echo -a echo -- -q
pintos -q run 'echo x'
To run an executable echo

We have made a file named mysyscall.c and made its executable as my and loaded it into file space and executed system call as required.

The system call plays an important role as it take the os into kernel mode and have previlages that user mode don't have. It is of great help as user are not botherd to remember all the procedure to implement and do all low level activities as kernel. Hence it provide interface for user to interact with the system more easily and without bothering about security and previlages.