

#include "kernel_header.h"

MODULE_DESCRIPTION("Module Describe Atomic functions and their proprties");

/* Declaration of Atomic variable */
atomic_t v ;
/*Decare and initialize the atomic varible by Zero  */
atomic_t u = ATOMIC_INIT(0) ;
/* for bit wise Atomic  operation */
volatile long unsigned int word = 0 ; 

/* Atomic instruction and operation */
long Atomic_Integer_Operation(void) 
{
    /*read the current value of variable v  */
    printk (KERN_INFO "atomic_read(&v) : %d\n" , atomic_read(&v));

    /* set the v value to 4 */
    atomic_set(&v , 4) ;
    printk (KERN_INFO "atomic_set(&v , 4) : %d\n", atomic_read(&v)); 
    
    /*add 4 to the v atomically   */
    atomic_add(4 , &v); 
    printk (KERN_INFO "atomic_add(4 , &v) : %d\n" , atomic_read(&v)); 
    
    /*subtract 4 from v atomically  */
    atomic_sub(4,&v) ;
    printk (KERN_INFO "atomic_sub(&v , 4) : %d\n" , atomic_read(&v)); 
    
    /*increment the value of variable v atomically  */
    atomic_inc(&v) ;
    printk (KERN_INFO "atomic_inc(&v) : %d\n" , atomic_read(&v)); 
    
    /*decrement the variable  v value  atomically  */
    atomic_dec(&v) ;
    printk (KERN_INFO "atomic_dec(&v) : %d\n" ,atomic_read(&v));
    
    /*
     * add to variable and return true if result is negative 
     * otherwise False 
     * */
    if (atomic_add_negative(4 , &v)<0) 
        printk (KERN_INFO "atomic_add_negative(4 , &v)\n") ; 
    else {
        printk (KERN_INFO "atomic_add_negative(4 , &v)" 
                "value is not negative\n") ; 
    }

    /*Atomically substract 4 from v and return true if result is zero */
    if (atomic_sub_and_test(4,&v)) 
    printk (KERN_INFO "atomic_sub_and_test(4 , &v) : TRUE (ZERO):  %d" , 
        atomic_sub_and_test(4 , &v));
    else  
    printk (KERN_INFO "atomic_sub_and_test(4 , &v) : FALSE: %d" , 
        atomic_sub_and_test(4 , &v));

    /*Atomically Decrement v  by one and return true if result is zero */
    if (atomic_dec_and_test(&v)) 
    printk (KERN_INFO "atomic_dec_and_test( &v) : TRUE (ZERO):v:  %d\t%d" , 
        atomic_dec_and_test(&v) ,atomic_read(&v));
    else  
    printk (KERN_INFO "atomic_sub_test (&v) : FALSE: %d" , 
        atomic_dec_and_test(&v));

    /*Atomically INcreament v  by one and return true if result is zero */
    if (atomic_dec_and_test(&v)) 
    printk (KERN_INFO "atomic_dec_and_test( &v) : TRUE (ZERO):  %d" , 
        atomic_dec_and_test(&v));
    else  
    printk (KERN_INFO "atomic_sub_test (&v) : FALSE: %d" ,
        atomic_dec_and_test(&v));

    /*Atomically add 4 in v and return result  */
    printk (KERN_INFO "atomic_add_return(&v) : %d\n" , 
        atomic_add_return(4,&v)); 

    /*Atomically sub 4 in v and return result  */
    printk (KERN_INFO "atomic_sub_return(&v) : %d\n" , 
        atomic_sub_return(4,&v)); 

    /*Atomically Inc  v and return result  */
    printk (KERN_INFO "atomic_inc_return(&v) : %d\n" , 
        atomic_inc_return(&v)); 

    /*Atomically dec and return result  */
    printk (KERN_INFO "atomic_dec_return(&v) : %d\n" , 
        atomic_dec_return(&v)); 


    /*
     * bit wise operation in Atmomic functions
     * */


    /*set the nth bit position in given int  */
    set_bit(1,&word) ; 
    printk (KERN_INFO "set_bit(1,&word) %ld\n" , word);

    /*clear the nth bit position in given int  */
    clear_bit(1,&word) ; 
    printk (KERN_INFO "clear_bit(1,&word) %ld\n" , word);

    /*flip the nth position in given int(toggle)  */
    change_bit(1,&word) ; 
    printk (KERN_INFO "change_bit(1,&word) %ld\n" , word);

    /*test and set the nth bit and return previous value*/
    printk (KERN_INFO "test_and_set_bit(3, &word) %d\n" ,
            test_and_set_bit(3, &word));

    /*test and clear the nth bit and return previous value*/
    printk (KERN_INFO "test_and_clear_bit(3, &word) %d\n" ,
            test_and_clear_bit(3, &word));

    /*test and toggle the nth bit and return previous value*/
    printk (KERN_INFO "test_and_change_bit(3, &word) %d\n" ,
            test_and_change_bit(3, &word));

    /*test the nth bit and return the bit position value*/
    printk (KERN_INFO "test_bit(3, &word) %d\n" ,
            test_bit(3, &word));


    return 0; 

}


EXPORT_SYMBOL(Atomic_Integer_Operation) ; 
