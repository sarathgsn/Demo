#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/kthread.h>

static struct task_struct *thread_st;
//    Function executed by kernel thread
static int thread_fn(void *unused)
{  
	int i = 0;
	while ( i < 2 )
	{   i++;
		printk(KERN_INFO "Thread Running\n");
		ssleep(5);
	}
     


	printk(KERN_INFO "Thread Stopping\n");

//	while(kthread_should_stop()) {
//		kthread_stop(thread_st);
//	}

	//    do_exit(0);
	return 0;
}
// Module Initialization

static int __init init_thread(void)
{
printk(KERN_INFO "Creating Thread\n");
//Create the kernel thread with name 'mythread'
	thread_st = kthread_create(thread_fn, NULL, "mythread");
	if (thread_st) {
		printk("Thread Created successfully\n");
		wake_up_process(thread_st);
	}else
	printk(KERN_INFO "Thread creation failed\n");
return 0;                                                                                
}
// Module Exit
static void __exit cleanup_thread(void)
{
	printk("Cleaning Up\n");
}
MODULE_LICENSE("GPL");
module_init(init_thread);
module_exit(cleanup_thread);
