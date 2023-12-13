/* filename: iom_led_dd.c */
/* PWD = ~/work/dd/iom_led_dd */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/io.h> /* outb() */
#include <linux/uaccess.h> /* copy_from_user() */

#define DEV_NAME "/dev/iom_led"
#define iom_led_dd_MAJOR_NUM 0
#define LED_PIN_NUM 21

#define IOREMAP_SIZE 0x40 // GPFSEL0 ~ GPLEV1 register

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
MODULE_DESCRIPTION("iom_mydeice module");
MODULE_AUTHOR("SM.HGU");

int iom_led_dd_open (struct inode *, struct file *);
int iom_led_dd_release (struct inode *, struct file *);
// ssize_t iom_led_dd_read (struct file *, char __user *, size_t, loff_t *);
ssize_t iom_led_dd_write (struct file *, const char __user *, size_t, loff_t *);
// long iom_led_dd_ioctl (struct file *, unsigned int, unsigned long);


struct file_operations iom_led_dd_fops = {
        .owner = THIS_MODULE,
        .open = iom_led_dd_open,
        .release = iom_led_dd_release,
        // .read = iom_led_dd_read,
        .write = iom_led_dd_write,
        // .unlocked_ioctl = iom_led_dd_ioctl,
};

int major_num;
static int gpio_pin21_usage = 0;
static unsigned int * ioremapped_gpio_addr;

#include "../rpi4_gpio_control.c"

int iom_led_dd_open (struct inode *inode, struct file *filep)
{
	 if( gpio_pin21_usage != 0 )
	 {
	 	return EBUSY;
	 }

	 gpio_pin21_usage = 1;

    return 0;
}

int iom_led_dd_release (struct inode *inode, struct file *filep)
{
	 gpio_pin21_usage = 0;

    gpio_clr(LED_PIN_NUM, GPIO_CLR);

    printk("iom_led_dd_release(): close %s device!!!\n", DEV_NAME);
    return 0;
}

#ifdef UNUSED_CODE
ssize_t iom_led_dd_read (struct file *filep, char __user *buf, size_t count, loff_t *f_ops)
{
    printk("iom_led_dd_read() function\n");
    return 0;
}
#endif


ssize_t iom_led_dd_write (struct file *filep, const char __user *buf, size_t count, loff_t *f_ops)
{
	 unsigned char value;
	 const char * dtmp = buf;

	 printk("iom_led_dd_write() function\n");
	 
	 if ( copy_from_user(&value, dtmp, count) )
		return -EFAULT;

	 if ( value )
	 {
		 gpio_set(LED_PIN_NUM, GPIO_SET);
	 } 
	 else 
	 {
		 gpio_clr(LED_PIN_NUM, GPIO_SET);
	 }

    return count;
}

#ifdef UNUSED_CODE
long iom_led_dd_ioctl (struct file *filep, unsigned int cmd, unsigned long arg)
{
    printk("Access iom_led_dd_ioctl() function\n");
        return 0;
}
#endif

// This is the starting point of the kernel module by insmod 
static int __init iom_led_dd_init(void)
{
        int major_num;

        major_num = register_chrdev(iom_led_dd_MAJOR_NUM, DEV_NAME, &iom_led_dd_fops);

        if (major_num < 0)
        {
                printk(KERN_WARNING"%s: can't get or assign major number %d\n", DEV_NAME, major_num);
                return major_num;
        }

		  ioremapped_gpio_addr = ioremap(GPIO_BASE, IOREMAP_SIZE);

		  gpio_select(LED_PIN_NUM, GPIO_OUTPUT); // setting gpio direction
		  gpio_clr(LED_PIN_NUM, GPIO_SET); // gpio clear, active=HIGH => LED PIN을 Low로 설정
		  

        printk("Success to load the device %s. Major number is %d\n", DEV_NAME, major_num);

        return 0;

}

static void __exit iom_led_dd_exit(void)
{
		  // default mod for GPIO pin is INPUT
		  gpio_select(LED_PIN_NUM, GPIO_INPUT);
		  
		  iounmap(ioremapped_gpio_addr);

        unregister_chrdev(major_num, DEV_NAME);
        printk("Unloaded device is %s..\n", DEV_NAME);
}


module_init(iom_led_dd_init);
module_exit(iom_led_dd_exit);
