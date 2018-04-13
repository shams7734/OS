#include <linux/kernel.h>

 asmlinkage long sys_hello(void)
{
        printk("Hello world.This is Shams first sys_call.\n");
        return 0;
 }
