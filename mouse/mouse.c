#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
 

 
static int mouse_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
 printk(KERN_INFO " MOUSE DRIVE PLUGGED %x : %x \n", id -> idVendor, id -> idProduct);   

}    
 static void mouse_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "mouse_driver is  now disconnected ");
}
 
static struct usb_device_id mouse_table[] =
{
    { USB_DEVICE(0x046d, 0xc05a) },
    {} /* Terminating entry */
};
MODULE_DEVICE_TABLE (usb, mouse_table);
 
static struct usb_driver mouse_driver =
{
    .name = "mouse_driver",
    .probe = mouse_probe,
    .disconnect = mouse_disconnect,
    .id_table = mouse_table,
};
 
static int __init mouse_init(void)
{
    return usb_register(&mouse_driver);
}
 
static void __exit mouse_exit(void)
{
    usb_deregister(&mouse_driver);
}
 
module_init(mouse_init);
module_exit(mouse_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("sharath");
MODULE_DESCRIPTION("MOuse driver");
