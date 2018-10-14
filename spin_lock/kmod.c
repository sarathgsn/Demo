#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>//kthreads
#include <linux/spinlock.h>//spin locks
#include <linux/completion.h>//completion variables
#include<linux/delay.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("sharath");
MODULE_DESCRIPTION("testing");		

static struct task_struct *th_id = NULL;
static struct task_struct *th_id1 = NULL;
static int i = 0;
static int j = 0;
static int condition = 1;
DEFINE_MUTEX(lock);
//DEFINE_SPINLOCK(my_lock);
 int counter = 0;
spinlock_t my_lock;
//spinlock_t my_lock = SPIN_LOCK_UNLOCKED;


static int thread_function1(void *data)
{    
        int *ptr = (int*)&data;
    //  mutex_lock(&lock);
    //   spin_lock(&my_lock);
        counter += 1;
        printk("counter in thread 2 is = %d\n", counter);
  //      mutex_unlock(&lock);
//	spin_unlock(&my_lock);
	return 0;
}
static int thread_function(void *data)
{      int *ptr = (int *)&data; 
        mutex_lock(&lock);
//        spin_lock(&my_lock);
        counter += 1;
        printk(" job started  = %d\n", counter);
      //  printk("counter in thread = %d = %d\n", *ptr, counter);
        msleep(10000);
                 printk(" job finished = %d\n", counter);
         mutex_unlock(&lock);
      //  spin_unlock(&my_lock);
	return 0;
}

static int __init mystart(void)
{
        mutex_init(&lock);
        int a = 1;
       int b = 2;
        void *ptr = &a;
        void *str = &b;
//	spin_lock_init(&my_lock);
	printk("i am initializing \n");
//	while( condition == 0)
	printk(KERN_INFO"i want to create a thread \n");
	
	while(j++ != 3){
		th_id = kthread_run(thread_function, ptr, "thread1");
	//	th_id1= kthread_run(thread_function1, str, "thread2");
	
//		if(th_id1 == NULL){
//			printk("thread1 creation failed\n");
//			return 0;
//		}
//		if(th_id == NULL){
//			printk("thread creation failed\n");
//			return 0;
//		}
//		wake_up_process(th_id);
        //        ssleep(5);
//		wake_up_process(th_id1);
	}
	
	return 0;
}

static void __exit myend(void)
{
	printk("i am going out \n");
	//kthread_stop(th_id);
}

module_init(mystart);
module_exit(myend);
