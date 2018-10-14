
#include "kernel_header.h"


/*
 * this Module is use to initialize the kernel module 
 * and destroy the kernel module having open and close 
 * file operation can be access by application at 
 * user space this module will create class for device 
 * and accept the coomand line argument of device name 
 * and make the device entry in /dev folder 
 * 
 * */


MODULE_DESCRIPTION("init module and exit module") ;  

/*
 * Module file capabilties 
 * */
struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_Open ,
    .release = my_Release,
    .read = fifo_read, 
    .write = fifo_write,
    .llseek = noop_llseek 
};


/*
 * global  variables
 * */

char* devname ;           /*to pass command line device name */
int mejNo ;                /*encodes mejor number and min number */
static dev_t mydev ;       /* mejor and minor number strucure */
struct cdev* my_cdev ;     /* holds char device driver descriptor */

struct kfifo test_fifo ; 
static DEFINE_MUTEX(mmutex_lock);

/* 
 * to accepts input from cammand line 
 * */

module_param (devname , charp ,0000);

/*
 * class device structure 
 * */
static struct class * mychar_class ;
static struct device *mychar_device ;



/*
 * my_init : init function of kernel modules (Constructor)
 * */

int __init my_Init (void)
{
    int ret = -ENODEV;
    int status ;

    printk (KERN_INFO  "initializinng charector device :%s \n" ,devname);

    /*
     * allocating device number dynamically
     * (refgister the range of device no) 
     * the static way of allocation 
     * register_chrdev_region() ; 
     *
     * */

    status = alloc_chrdev_region (&mydev , FIRST_MINOR , NR_DEV, devname);
    if ( status < 0) {
        printk (KERN_NOTICE  "Device number allocation failed_%d\n", status );
        goto err ;
    }

    printk (KERN_INFO  "Device number allocated %d\n", MAJOR(mydev) );	

    /*
     * allocate memory for  my dev
     * */
    my_cdev = cdev_alloc (); 
    if (NULL == my_cdev ) {
        printk (KERN_ERR  "Device number allocated %d\n "
                "for Module %s\n", MAJOR(mydev) , devname );
        goto err_cdev_alloc ;
    }

    /*
     * initialization of my_cdev with fops
     * */
    cdev_init (my_cdev,&fops); 
    my_cdev ->owner = THIS_MODULE;

    /* 
     * add my cdev to  the list in the already existing list 
     * */

    status = cdev_add (my_cdev , mydev, NR_DEV); 
    if (status ) {	
        printk (KERN_ERR  "cdev failed \n ");
        goto err_cdev_add ;
    }

    /*
     *  create a class and system entry in sys fs
     *  */

    mychar_class = class_create (THIS_MODULE , devname);
    if(IS_ERR( mychar_class) ) {
        printk (KERN_ERR  "Class create fauiled ");
        goto err_class_create;
    }

    /*
     * create char device in sys fs and an device entry 
     * will be made in dev directory
     * */

    mychar_device = device_create (mychar_class, NULL ,mydev , NULL , devname );
    if ( IS_ERR ( mychar_device)) {	
        printk (KERN_ERR  "Device create failed\n"  );
        goto err_device_create ;
    }

    return 0;

    /*
     * error handling level 
     * */
err_device_create : 
    class_destroy ( mychar_class ) ;
err_class_create :
    cdev_del ( my_cdev ) ;
err_cdev_add :
    kfree (my_cdev) ;
err_cdev_alloc : 
    unregister_chrdev_region (mydev , NR_DEV);
err : 
    return ret;
}

/*
 * my exit : clean up function  of kernel modules (Destructor) 
 * */
void my_Exit ( void ) 
{
    printk (KERN_INFO  "Exiting the char device %s\n " , devname);
    device_destroy (mychar_class , mydev);
    class_destroy (mychar_class);
    cdev_del (my_cdev);
    unregister_chrdev_region (mydev , NR_DEV);
    kfifo_free(&test_fifo) ; 
    return ;  
}


/*
 * my_open function for psudo driver
 * */

int my_Open (struct inode * inode , struct file * filep )
{
    printk (KERN_INFO "file open successful \n");
    return 0;
}

/*
 * my_release function to release the psudo  driver 
 * */
int my_Release (struct inode * in , struct file * fp )
{
    printk (KERN_INFO  "file close successful \n");
    return 0;
}



ssize_t fifo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    /*allocte the kernel ring buffer  */
    if ((ret = kfifo_alloc(&test_fifo, FIFO_SIZE, GFP_KERNEL))!=0)
        handle_error(kfifo_alloc_fail) ;

    /* apply mutex lock before writing into kernel fifo buffer*/
    if (mutex_lock_interruptible(&mmutex_lock))
        return -ERESTARTSYS;

    /* write into kernel fifo buffer from user space*/
    if ((ret = kfifo_from_user(&test_fifo, buf,count , &copied))!=0)
        handle_error(fail_kfifo_from_user)  ;

    printk (KERN_INFO "Copied from user:%d\n" ,count);
    printk (KERN_INFO "Copied from user:%d\n" ,*buf);

    /*unlock the mutex variable for reader */
    mutex_unlock(&mmutex_lock);

    return ret ? ret : copied;
}

ssize_t fifo_read(struct file *file, char __user *buf,
        size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    /*apply the mutex lock before read the data from kernel ring buffer */
    if (mutex_lock_interruptible(&mmutex_lock))
        return -ERESTARTSYS;

    /*copy data to the user buffer */
    while(kfifo_avail(&test_fifo)){

        if(kfifo_is_empty(&test_fifo)) 
            break ; 

        ret = kfifo_to_user(&test_fifo, buf,count, &copied);
        kfifo_out(&test_fifo ,buf,sizeof(*buf)) ;
        printk (KERN_INFO "dequeued Element %d\n" , *buf);
    }

    mutex_unlock(&mmutex_lock);

    return ret ? ret : copied;
}

/*
 * release the kenel module function 
 * */
module_init (my_Init);
module_exit (my_Exit);

