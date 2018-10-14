#include<linux/kernel.h> 
#include<linux/module.h> 
#include<linux/init.h> 

int simham = 100;
int tiger = 200;
static int hello_init(void) 
{
 printk(KERN_WARNING "Hello, world \n ");
 
 return 0; 
} 

static void hello_exit(void)
{
 printk(KERN_INFO "Goodbye, world \n"); 
}

EXPORT_SYMBOL_GPL(simham);
module_init(hello_init);
module_exit(hello_exit);

