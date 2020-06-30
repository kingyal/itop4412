/*Description:动态申请字符类设备号
 *Author:ky
 *Date:2020-06-24
 *History:2020-06-24  1st
 *Note：可通过cat /proc/devices查看主设备号
 */
 
#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>

#define DEVICE_NAME "asscdev"
#define DEVICE_MINOR_NUM 2
#define DEVICE_MAJOR 0
#define DEVICE_MINOR 0

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ky");

int numdev_major = DEVICE_MAJOR;
int numdev_minor = DEVICE_MINOR;

module_param(numdev_major, int, S_IRUSR);
module_param(numdev_minor, int, S_IRUSR);

static int hello_init(void) 
{
	int ret = 0;
	dev_t num_dev;
	printk(KERN_EMERG "numdev_major = %d\n", numdev_major);
	printk(KERN_EMERG "numdev_minor = %d\n", numdev_minor);

	if (numdev_major) {
		num_dev = MKDEV(numdev_major, numdev_minor);
		ret = register_chrdev_region(num_dev, DEVICE_MINOR_NUM, DEVICE_NAME);
	} else {
		ret = alloc_chrdev_region(&num_dev, numdev_minor, DEVICE_MINOR_NUM, DEVICE_NAME);
		numdev_major = MAJOR(num_dev);
		printk(KERN_EMERG "alloc chrdev register success\n");
		printk(KERN_EMERG "numdev_major = %d\n", numdev_major);
	}
	if (ret < 0) {
		printk(KERN_EMERG "register_chrdev_region failed\n");
	}
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");
	
	unregister_chrdev_region(MKDEV(numdev_major, numdev_minor), DEVICE_MINOR_NUM);
}

module_init(hello_init);
module_exit(hello_exit);

