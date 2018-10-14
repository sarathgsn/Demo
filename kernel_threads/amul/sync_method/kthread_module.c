

/* 
 * this module will create kernel thread and sync them by using 
 * delay function call  in kernel 
 * */


#include "kernel_header.h"


MODULE_DESCRIPTION("Create kernel_thraed and sync them") ; 


struct task_struct *kth ;   /*kthread_createt  return   */ 
int i = 20 ;                /*global critical_section_variable */ 

/* 
 * function to get pid of any running process 
 *
 * */

int mget_pid (struct task_struct *kth) 
{
    int process_id ;
    kth = current ; 

    return (process_id = (int) kth->pid) ; 
}


/*
 * this functio will pole for pending signal in 
 * kernel to be executed only allowed signal will 
 * can interrupt(executed)  
 * */

static int thread_fn(void *data)
{
    int process_id  ;
    struct task_struct th3 ; 

    /*Allow the SIGKILL signal*/

    process_id  = mget_pid(&th3) ;
    allow_signal(SIGKILL);
    while (!kthread_should_stop()) { 
        printk(KERN_INFO "Thread Running : %s\t%s %d\n" , (char*)data,
                "<use> <kill -9", process_id);
        ssleep(5);
        /* 
         * Check if the signal is pending
         * */
        if (signal_pending(kth))
            break;
    }

    printk(KERN_INFO "Thread Stopping\n");
    do_exit(0);
    return 0;
}

/*
 * thread function which will be run after calling by kthreadd_wakeup
 * */

int threadfn1(void* data) 
{
    printk (KERN_INFO "called_thread : %s\t%s\t" ,  __FUNCTION__ , 
            (char*)data);
    if ( i == 20 ) { 
        printk (KERN_INFO "I= %d\n" , i );
        i = i+20 ; 
    } 

    /*
     * make some micro second delay for context swich 
     * */
    udelay(2) ;
    do_exit(0); 
}

/*
 * thread function which will be run after calling by kthreadd_wakeup
 * */

int threadfn2(void* data) 
{
    printk (KERN_INFO "called_thread :%s\t%s\t" ,  __FUNCTION__ , 
            (char*)data )  ; 

    if ( i == 40 ) { 
        printk (KERN_INFO "I= %d\n" , i );
        i = i+30 ; 
    }

    do_exit(0); 
}


/*
 * my_ioctl function to print the process id of process &  psudo  driver 
 * */
long Kthread_create (struct file * fp , unsigned int pid , long unsigned ppid )
{


    printk (KERN_INFO  "Process id is = %d\nParent id is = %ld\n",
            pid, ppid);

    /* 
     * create a new thread to handle some  job there 
     * */
    kth = kthread_create(threadfn1 ,"kthread_create" ,"%s" , "Msg")  ; 
    if (!IS_ERR(kth)) {
        wake_up_process(kth) ; 
    }

    /*
     * othr way of creating thread inside kernel kthread_run 
     * will create and wakeup the thread and add the entry 
     * in the thread list  
     * */

    kth = kthread_run(threadfn2 , "kthread_run" , "%s" , "Msg") ; 
    if (IS_ERR(kth)) 
        printk (KERN_ERR "Fail : kthread_run\n" );

    udelay(20) ; 
    printk ("Function : %s  I = %d\n" ,  __FUNCTION__ ,i);

    /* 
     * release the resources of thread 
     * */

    kthread_stop(kth) ; 

    kth = kthread_run(thread_fn , "SIGNAL_handling" , "%s" , "Msg") ; 
    if (IS_ERR(kth)) 
        printk (KERN_ERR "Fail : kthread_run\n" );

    return 0;
}

EXPORT_SYMBOL(Kthread_create) ; 
