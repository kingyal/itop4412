/*Description:直接注册杂项设备的设备节点
 *Author:ky
 *Date:2020-06-24
 *History:2020-06-24  1st
 */
 
#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>
/*注册杂项设备*/
#include <linux/miscdevice.h>
/*驱动注册的文件结构体*/
#include <linux/fs.h>

#define DEVICE_NAME "test_ky"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ky");

static int test_open(struct inode *Inode, struct file *File){
	printk(KERN_EMERG "\t test_open\n");
	return 0;
}

static int test_release(struct inode *Inode, struct file *File){
	printk(KERN_EMERG "\t test_release\n");
	return 0;
}

static long test_unlocked_ioctl(struct file *File, unsigned int cmd, unsigned long arg){
	printk(KERN_EMERG "\t test_unlocked_ioctl\n");
	printk(KERN_EMERG "\t cmd = %d, arg = %ld\n", cmd ,arg);
	
	if(cmd > 1){
		printk(KERN_EMERG "test.ko: cmd = 0 or cmd = 1\n");
		return 1;
	}
	
	if(arg > 1){
		printk(KERN_EMERG "test.ko: arg = 1\n");
		return 1;
	}
	
	return 0;	
}

struct file_operations test_ops ={
	.owner = THIS_MODULE,
	.open = test_open,
	.release = test_release,
	.unlocked_ioctl = test_unlocked_ioctl,
};

struct miscdevice test_dev ={
	.minor = MISC_DYNAMIC_MINOR,   //自动分配
	.name = DEVICE_NAME,
	.fops = &test_ops,
};

static int test_init(void) 
{
	printk(KERN_EMERG "HELLO WORLD enter!\n");

	misc_register(&test_dev);   //注册设备节点
	return 0;
}

static void test_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");

	misc_deregister(&test_dev);	
}

module_init(test_init);
module_exit(test_exit);

