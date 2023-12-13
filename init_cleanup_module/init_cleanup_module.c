/* filename : hello.c */
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");

int init_module(void) /* module_init() */
{
	printk("Loading my first device driver...\n");
	return 0;
}

void cleanup_module(void) /* module_exit() */
{
	printk("Unloading my first device driver..\n");
}
