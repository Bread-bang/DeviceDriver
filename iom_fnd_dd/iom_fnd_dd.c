/* filename: iom_fnd_dd.c */
/* PWD = ~/work/dd/iom_fnd_dd */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/io.h> /* outb() */
#include <linux/uaccess.h> /* copy_from_user() */

#define DEV_NAME "/dev/iom_fnd"
#define iom_fnd_dd_MAJOR_NUM 0

//GPIO pins used for the device like LED or FND
//#define LED_PIN_NUM 21
int fnd_pin[] = {5, 6, 13, 19, 26, 16, 20}; // a, b, c, d, e, f, g
int fnd_hex_val[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xd8, 0x80, 0x90}; // Common anode (active HIGH) : 0 ~ 9

#define IOREMAP_SIZE 0x40 // GPFSEL0 ~ GPLEV1 register

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
MODULE_DESCRIPTION("iom_mydeice module");
MODULE_AUTHOR("SM.HGU");

int iom_fnd_dd_open (struct inode *, struct file *);
int iom_fnd_dd_release (struct inode *, struct file *);
// ssize_t iom_fnd_dd_read (struct file *, char __user *, size_t, loff_t *);
ssize_t iom_fnd_dd_write (struct file *, const char __user *, size_t, loff_t *);
// long iom_fnd_dd_ioctl (struct file *, unsigned int, unsigned long);


struct file_operations iom_fnd_dd_fops = {
        .owner = THIS_MODULE,
        .open = iom_fnd_dd_open,
        .release = iom_fnd_dd_release,
        // .read = iom_fnd_dd_read,
        .write = iom_fnd_dd_write,
        // .unlocked_ioctl = iom_fnd_dd_ioctl,
};

int major_num;
//static int gpio_pin21_usage = 0;
static int gpio_fnd_device_usage = 0;
static unsigned int * ioremapped_gpio_addr;

#include "../rpi4_gpio_control.c"

int iom_fnd_dd_open (struct inode *inode, struct file *filep)
{
	 if( gpio_fnd_device_usage != 0 )
	 {
	 	return EBUSY;
	 }

	 gpio_fnd_device_usage = 1;

    return 0;
}

int iom_fnd_dd_release (struct inode *inode, struct file *filep)
{
	 int pinNo;

	 // apply HIGH to GPIO to turn off FND because of active-LOW configuration
	 for( pinNo =0; pinNo < sizeof(fnd_pin) / sizeof(fnd_pin[0]); pinNo++)
	 {
	 	gpio_set(fnd_pin[pinNo], SET_GPIO);
	 }

	 gpio_fnd_device_usage = 0;

    printk("iom_fnd_dd_release(): close %s device!!!\n", DEV_NAME);
    return 0;
}

#ifdef UNUSED_CODE
ssize_t iom_fnd_dd_read (struct file *filep, char __user *buf, size_t count, loff_t *f_ops)
{
    printk("iom_fnd_dd_read() function\n");
    return 0;
}
#endif


ssize_t iom_fnd_dd_write (struct file *filep, const char __user *buf, size_t count, loff_t *f_ops)
{
	 unsigned char value;
	 const char * dtmp = buf;
	 int x = 0;

	 printk("iom_fnd_dd_write() function\n");
	 
	 if ( copy_from_user(&value, dtmp, count) )
		return -EFAULT;
		
	 // Clear all FND pins
	 // Turn all segments off before writing new FND data
	 for ( x = 0; x < sizeof(fnd_pin) / sizeof(fnd_pin[0]); x++)
	 {
	 	gpio_set(fnd_pin[x], SET_GPIO);
	 }

	 // Write FND data to the FND device
	 if ( value >= 0 && value <= 9)
	 {
	   for ( x = 0; x < sizeof(fnd_pin) / sizeof(fnd_pin[0]); x++)
		{
			if (( fnd_hex_val[value] & (0x1 << x)) == 0 )
			{
				gpio_clr(fnd_pin[x], SET_GPIO); // active-LOW 
			}
		}
	 }

    return count;
}

#ifdef UNUSED_CODE
long iom_fnd_dd_ioctl (struct file *filep, unsigned int cmd, unsigned long arg)
{
    printk("Access iom_fnd_dd_ioctl() function\n");
        return 0;
}
#endif

// This is the starting point of the kernel module by insmod 
static int __init iom_fnd_dd_init(void)
{
        int major_num;
		  int x;

        major_num = register_chrdev(iom_fnd_dd_MAJOR_NUM, DEV_NAME, &iom_fnd_dd_fops);

        if (major_num < 0)
        {
                printk(KERN_WARNING"%s: can't get or assign major number %d\n", DEV_NAME, major_num);
                return major_num;
        }

		  ioremapped_gpio_addr = ioremap(GPIO_BASE, IOREMAP_SIZE);

		  // gpio_select(LED_PIN_NUM, GPIO_OUTPUT); // setting gpio direction
		  for (x = 0; x < sizeof(fnd_pin) / sizeof(fnd_pin[0]); x++)
		  {
		   	gpio_select(fnd_pin[x], GPIO_OUTPUT);
		  }

		  // Turn off FND device by applying HIGH signal to each segment
		  for (x = 0; x < sizeof(fnd_pin) / sizeof(fnd_pin[0]); x++)
		  {
		  		gpio_set(fnd_pin[x], SET_GPIO); // active = LOW
		  }

		  // gpio_clr(LED_PIN_NUM, GPIO_SET); // gpio clear, active=HIGH => LED PIN을 Low로 설정
		  

        printk("Success to load the device %s. Major number is %d\n", DEV_NAME, major_num);

        return 0;

}

static void __exit iom_fnd_dd_exit(void)
{
		  int x;

		  // default mod for GPIO pin is INPUT
		  // gpio_select(LED_PIN_NUM, GPIO_INPUT);
		  
		  // default mode for GPIO pins unused are INPUT
		  for (x = 0; x < sizeof(fnd_pin) / sizeof(fnd_pin[0]); x++)
		  {
		  		gpio_select(fnd_pin[x], GPIO_INPUT);
		  }

		  iounmap(ioremapped_gpio_addr);

        unregister_chrdev(major_num, DEV_NAME);
        printk("Unloaded device is %s..\n", DEV_NAME);
}


module_init(iom_fnd_dd_init);
module_exit(iom_fnd_dd_exit);
