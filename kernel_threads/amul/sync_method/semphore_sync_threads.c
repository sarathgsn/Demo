

/* 
 * this module will create kernel thread and sync them by using 
 * semaphore lock mechanism  in kernel in this program there is is a 
 * critcal section varable I(ey) which is accessed by two thread 
 * function threadfn1 and threadfn2 where in threadfn1 ssleep(2) 
 * causes context switch will be happen and threadfn2 will never 
 * print the variable i value  by applying semaphore lock we can 
 * achieve  the synchronization between these threads 
 *
 * */


#include "kernel_header.h"


MODULE_DESCRIPTION("Create kernel_thraed and sync them usin semaphore") ; 


struct task_struct *kth ;   /*kthread_createt  return   */ 
int i = 0 ;                /*global critical_section_variable */ 

/*static inittilization of semaphore variable in unlock mode */
DEFINE_SEMAPHORE(kthread_lock) ;


/*
 *  Dynamic way of initializing the semaphore 
 *  Initialize the semaphore to unlocked state
 *
 * int count = 2 ; 
 * struct semaphore semaphore_name ;
 * semaphore_init(&semaphore_name , count) ; 
 *
 * initialize the dynamically created semaphore with count one
 * init_MUTEX(struct semaphore *)   
 *
 * initialize the dynamically created semaphore with count zero 
 * init_MUTEX_LOCK(struct semaphore *);
 *
 *
 * */

/* function to get pid of any running process*/
int mget_pid (struct task_struct *kth) 
{
    int process_id ;
    kth = current ; 

    return (process_id = (int) kth->pid) ; 
}

/*
 * thread function which will be run after calling by
 * kthreadd_wakeup
 * */


/*
 * semaphore methods: 
 *
 * 1. down_interruptible(struct semaphore*) 
 * tries to aquire the given semaphore and enter interruptible 
 * sleep if it is contended 
 *
 * 2. down(struct semaphore*) ; 
 * tries to aquire the given semaphore and enter uninterruptible 
 * sleep if it is contended
 *
 * 3. down_trylock(struct semaphore*);
 * 4. up(struct semaphore*) ; 
 *
 * */

int threadfn1(void* data) 
{
    struct task_struct th1 ;

    /*apply the semaphore lock for sync the threads */
    down(&kthread_lock) ; 
    printk (KERN_INFO "called_thread : %s\t%s\t" ,  __FUNCTION__ , 
            (char*)data);
    printk (KERN_INFO "thread_id :%d\n" , mget_pid(&th1));
    /*
     * create race condition for variable make delay so that othre 
     * thread  can get scheduled and and both will not execute 
     * the if condition 
     * */ 
    ssleep(2);
    if ( i == 0 ) { 
        printk (KERN_INFO "I= %d\n" , i);
        i = i+20 ; 
        printk (KERN_INFO "I+20 = %d\n" , i);
    }

    /*free the lock so that other thread can access the 
     * common resource i 
     * */
    up(&kthread_lock) ; 
    do_exit(0); 
}

/*
 * thread function which will be run after calling by kthreadd_wakeup
 * */

int threadfn2(void* data) 
{
    struct task_struct th2 ;

    /*
     * the semaphore_trylock will lock only when lock is availble 
     *  otherwise it return zero and do not block the process
     *  */
    down_trylock(&kthread_lock) ;

    /* 
     * this call will be in block state untill lock gets 
     * release by other process 
     * */

    down(&kthread_lock) ;
    printk (KERN_INFO "called_thread :%s\t%s\t" ,  __FUNCTION__ , 
            (char*)data )  ; 
    printk (KERN_INFO "thread_id :%d\n" ,mget_pid(&th2)) ;

    if ( i == 20 ) { 
        printk (KERN_INFO "I= %d\n" , i );
        i = i+30 ; 
        printk (KERN_INFO "I+30 = %d\n" , i );
    }

    up(&kthread_lock) ; 
    do_exit(0); 
}


/*
 * my_ioctl function to print the process id of process &  psudo  driver 
 * */
long Kthread_create (struct file * fp , unsigned int pid , long unsigned ppid )
{

    /* 
     * create a new thread to handle some  job there 
     * */
    kth = kthread_create(threadfn1 ,"kthread_create" , "Kthread1")  ; 
    if (!IS_ERR(kth)) {
        wake_up_process(kth) ; 
    }

    /*
     * othr way of creating thread inside kernel kthread_run 
     * will create and wakeup the thread and add the entry 
     * in the thread list  
     * */


    kth = kthread_run(threadfn2 , "kthread_run" , "Kthread2") ; 
    if (IS_ERR(kth)) 
        printk (KERN_ERR "Fail : kthread_run\n" );

    ssleep(5) ;
    printk ("Function : %s  I = %d\n" ,  __FUNCTION__ ,i);
    /* 
     * release the resources of thread 
     * */

    printk (KERN_INFO "Exting Function :%s\n" , __FUNCTION__); 
    return 0;
}

EXPORT_SYMBOL(Kthread_create) ; 
