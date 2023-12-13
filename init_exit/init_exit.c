/* filename : init_exit.c */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_INFO(intree, "Y");
MODULE_DESCRIPTION("init_exit module");
MODULE_AUTHOR("BANG, HGU");

static int __init ie_init(void) /* module_init()에서 호출되도록*/ 
{
	printk("Loading my first device driver from ie_init...\n");
	return 0;
}

static void __exit ie_exit(void) /* module_exit() */
{
	printk("Unloading my first device driver from ie_exit...\n");
}

module_init(ie_init);
module_exit(ie_exit);
