/* filename : iom_virtual_dd.c */
/* PWD = ~/work/dd/iom_virtual_dd */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>

#define DEV_NAME "/dev/iom_virtual_dd"
#define iom_virtual_dd_MAJOR_NUM 0

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
MODULE_DESCRIPTION("iom_virtual_dd module");
MODULE_AUTHOR("BANG_iotclass.HGU");

int iom_virtual_dd_open (struct inode *, struct file *);
int iom_virtual_dd_release (struct inode *, struct file *);
ssize_t iom_virtual_dd_read (struct file *, char __user *, size_t, loff_t *);
ssize_t iom_virtual_dd_write (struct file *, const char __user *, size_t, loff_t *);
long iom_virtual_dd_ioctl (struct file *, unsigned int, unsigned long);

struct file_operations iom_virtual_dd_fops = {
	.owner = THIS_MODULE,
	.open = iom_virtual_dd_open,
	.release = iom_virtual_dd_release,
	.read = iom_virtual_dd_read,
	.write = iom_virtual_dd_write,
	.unlocked_ioctl = iom_virtual_dd_ioctl,
};

unsigned int major_num;


int iom_virtual_dd_open (struct inode *inode, struct file *filep)
{
	printk("iom_virtual_dd_open(): open virtual device!!!\n");
	return 0;
}

int iom_virtual_dd_release (struct inode *inode, struct file *filep)
{
	printk("iom_virtual_dd_release(): close virtual device!!!\n");
	return 0;
}

ssize_t iom_virtual_dd_read (struct file *filep, char __user *buf, size_t count, loff_t *f_ops)
{
	printk("iom_virtual_dd_read() function\n");
	return 0;
}

ssize_t iom_virtual_dd_write (struct file *filep, const char __user *buf, size_t count, loff_t *f_ops)
{
	printk("iom_virtual_dd_write() function\n");
	return 0;
}

long iom_virtual_dd_ioctl (struct file *filep, unsigned int cmd, unsigned long arg)
{
	printk("iom_virtual_dd_ioctl() function\n");
	return 0;
}

// This is the starting point of the kernel module by insmod
static int __init iom_virtual_dd_init(void)
{
	major_num = register_chrdev(iom_virtual_dd_MAJOR_NUM, DEV_NAME, &iom_virtual_dd_fops);		
	if (major_num < 0)
	{
		printk(KERN_WARNING"%s: can't get or assign major number %d\n", DEV_NAME, major_num);
		return major_num;
	}

	printk("Success to load the device %s. Major number is %d\n", DEV_NAME, major_num);

	return 0;
}

// This is the exit point of the kernel module my rmmod
static void __exit iom_virtual_dd_exit(void)
{
	unregister_chrdev(major_num, DEV_NAME);
	printk("Unloaded device is %s..\n", DEV_NAME);
}


module_init(iom_virtual_dd_init); // init_module()
module_exit(iom_virtual_dd_exit); // cleanup_module()
