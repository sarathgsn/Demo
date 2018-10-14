
#ifndef _KERNEL_HEADER_H
#define _KERNEL_HEADER_H

/*include the system files  */                                                  
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/sched/task.h>
#include <linux/binfmts.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/completion.h>
#include <linux/cred.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/workqueue.h>
#include <linux/security.h>
#include <linux/mount.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/resource.h>
#include <linux/notifier.h>
#include <linux/suspend.h>
#include <linux/rwsem.h>
#include <linux/ptrace.h>
#include <linux/async.h>
#include <linux/uaccess.h>
#include <linux/fs.h>      
#include <linux/cdev.h>  
#include <linux/device.h> 
#include <asm/uaccess.h> 
#include <linux/export.h>  
#include <linux/kthread.h> 
#include <linux/delay.h> 
#include <linux/mutex.h>
#include <linux/types.h>
#include <asm/atomic.h>
#include <asm/bitops.h>
#include <linux/list.h>
#include <linux/kfifo.h>
#include <linux/interrupt.h>
#include <linux/irqreturn.h>
#include <asm/irq.h>
#include <linux/signal.h>
#include <asm/signal.h>
#include <linux/mc146818rtc.h>
#include <linux/proc_fs.h>


#define display_msg(kernel_msg,...) if ((printk(kernel_msg, ##__VA_ARGS__))<0)\   return(-1) ; 

#define handle_error(msg) do{printk(KERN_ERR #msg) ; return(-1) ;\
} while(0) ; 

#define FIRST_MINOR 0                                                           
#define NR_DEV 1          /*number of device number */                          
#define FIFO_SIZE 32

#if 1 
#define DYNAMIC_INIT_Q 1
#else 
#define STATIC_INIT_Q 1
#endif

#if 1
#define STATIC_TASKLET 1 
#else 
#define RUNTIME_TASKLET 1
#define PRIORITY 1
#endif 

#if 0
#define STATIC_WORKQUEUE 1 
#else 
#define RUNTIME_WORKQUEUE 1
#endif 

#if 1
#define STATIC_WAIT_EVENT 1 
#else 
#define RUNTIME_WAIT_EVENT 1
#endif

#if 1
#define STATIC_IRQ 1 
#else 
#define RUNTIME_IRQ 1
#endif 

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("mp.amlendu@globaledgesoft.com") ;

extern long Kthread_create (struct file *  , unsigned  int, long unsigned  );
extern int my_Open  (struct inode * , struct file * );
extern int my_Release (struct inode * , struct  file * ); 
extern long Atomic_Integer_Operation(void) ; 
extern long Link_List_Operations(void) ; 
extern long Queue_Operations(void) ; 
extern long Stack_Operations(void) ; 
extern long Waiting_and_Blocking_Operations(void) ; 
extern int push_in_stack (struct file*, const char*, size_t, loff_t*); 
extern int pop_from_stack (struct file*, char*, size_t, loff_t*); 
extern long List_person(void) ;
extern int print_from_stack(struct list_head*) ;
extern ssize_t fifo_write(struct file *, const char __user *,
        size_t count, loff_t *);  
extern ssize_t fifo_read(struct file *, char __user *,size_t, loff_t *) ; 
extern long Tasklet_Operations(void) ; 
extern long Workqueue_Operations(void) ; 
extern long Interrupt_Handling(void) ; 
extern void test_tasklet_handler(unsigned long) ; 
extern void test_workqueue_handler(struct work_struct*) ; 
extern size_t my_Write (struct file*, const char __user*, size_t, loff_t*); 
extern ssize_t my_Read(struct file *, char __user*, size_t, loff_t *) ;
extern int test_write_proc(struct file*,const char*, size_t, loff_t*) ;
extern int test_read_proc(struct file*, char*, size_t, loff_t*) ; 
extern long Softirq_Operations(void) ; 
extern long Proc_Operations(void) ; 

int my_Init (void);                                                      
void my_Exit (void);   


#endif 
