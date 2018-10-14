#include<asm/current.h>
#include <linux/init.h>
#include <linux/module.h>
#include<linux/sched.h>
//MODULE_LICENSE("Dual BSD/GPL");
int var =100;
static int hello_init(void)
{
 //   struct task_struct *ptr = current;
    printk( "Hello,  world %d\n",current->pid);
    return 0;
}
static void hello_exit(void)
{
    printk( "Goodbye, cruel world\n");
}
module_init(hello_init);
module_exit(hello_exit);
//EXPORT_SYMBOL(var);




