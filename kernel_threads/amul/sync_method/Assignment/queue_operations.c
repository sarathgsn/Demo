
#include "kernel_header.h"
MODULE_DESCRIPTION("Module describe Queue properties in kernel") ; 

struct kfifo test_fifo ; 
static DEFINE_MUTEX(read_lock);
static DEFINE_MUTEX(write_lock);

ssize_t fifo_write(struct file *file, const char __user *buf,
        size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    if ((ret = kfifo_alloc(&test_fifo, FIFO_SIZE, GFP_KERNEL))!=0)
        handle_error(kfifo_alloc_fail) ;

    if (mutex_lock_interruptible(&write_lock))
        return -ERESTARTSYS;

    if ((ret = kfifo_from_user(&test_fifo, buf,count , &copied))!=0)
        handle_error(fail_kfifo_from_user)  ;

    printk (KERN_INFO "Copied from user:%d\n" ,copied);
    printk (KERN_INFO "Copied from user:%d\n" ,count);
    printk (KERN_INFO "Copied from user:%s\n" ,buf);

    mutex_unlock(&write_lock);
    
    return ret ? ret : copied;
}

ssize_t fifo_read(struct file *file, char __user *buf,
        size_t count, loff_t *ppos)
{
    int ret;
    unsigned int copied;

    if (mutex_lock_interruptible(&read_lock))
        return -ERESTARTSYS;

    strcpy(buf ,"ok_user") ; 
    printk (KERN_INFO "Copying to user:%s\n" ,buf);
    ret = kfifo_to_user(&test_fifo, buf,count, &copied);
    mutex_unlock(&read_lock);

    return ret ? ret : copied;
}

