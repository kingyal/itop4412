/*Description:动态申请字符类设备号
 *Author:ky
 *Date:2020-06-24
 *History:2020-06-24  1st
 *Note：可通过cat /proc/devices查看主设备号
 *		注册设备的本质是想linux设备文件中添加数据
 */
/*包含初始化宏定义：module_init和module_exit*/ 
#include <linux/init.h>
/*包含初始化加载模块：MODULE_LICENSE*/ 
#include <linux/module.h>
/*包含module_param和module_param_array*/ 
#include <linux/moduleparam.h>
/*包含module_param和module_param_array中的perm头文件*/ 
#include <linux/stat.h>
/*三个字符设备函数*/
#include <linux/fs.h>
/*MKDEV转换设备号数据类型的宏定义*/
#include <linux/kdev_t.h>
/*字符设备结构体*/
#include <linux/cdev.h>
/*分配内存空间函数头文件*/
#include <linux/slab.h>

#define DEVICE_NAME "asscdev"
#define DEVICE_MINOR_NUM 2
#define DEVICE_MAJOR 0
#define DEVICE_MINOR 0

#define DATA_SIZE 3000

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ky");

/*主设备号*/
int numdev_major = DEVICE_MAJOR;
/*次设备号*/
int numdev_minor = DEVICE_MINOR;

module_param(numdev_major, int, S_IRUSR);
module_param(numdev_minor, int, S_IRUSR);


struct reg_dev{
	char *data;
	unsigned long size;
	struct cdev cdev;
	
};

struct reg_dev *my_devices;

struct file_operations my_fops = {
	.owner = THIS_MODULE,
};

static void reg_init_cdev (struct reg_dev *dev, int index) {
	int err;
	int devno = MKDEV(numdev_major, numdev_minor + index);
	/*设备初始化*/
	cdev_init(&dev->cdev, &my_fops);
	dev->cdev.owner = THIS_MODULE;
	dev->cdev.ops = &my_fops;
	/*设备注册到系统*/
	err = cdev_add(&dev->cdev, devno, 1);
	
	if (err) {
		printk(KERN_EMERG "cdev add %d failed, err = %d\n", index, err);
	} else {
		printk(KERN_EMERG "cdev add %d success\n", index);
	}
}

static int hello_init(void) 
{
	int ret = 0;
	int i;
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
	
	my_devices = kmalloc(DEVICE_MINOR_NUM * sizeof(struct reg_dev), GFP_KERNEL);
	if (!my_devices) {
		printk(KERN_EMERG "kmalloc failed\n");
		goto ERR_KMALLOC;
	}
	memset(my_devices, 0, DEVICE_MINOR_NUM * sizeof(struct reg_dev));
	
	for (i = 0; i < DEVICE_MINOR_NUM; i++) {
		my_devices[i].data = kmalloc(DATA_SIZE, GFP_KERNEL);
		memset(my_devices[i].data, 0, DATA_SIZE);
		
		reg_init_cdev(&my_devices[i], i);
	}
	
	
	return 0;
	
ERR_KMALLOC:
	unregister_chrdev_region(MKDEV(numdev_major, numdev_minor), DEVICE_MINOR_NUM);
}

static void hello_exit(void)
{
	int i;
	printk(KERN_EMERG "HELLO WORLD exit!\n");
	
	for (i = 0; i < DEVICE_MINOR_NUM; i++) {
	cdev_del(&my_devices[i].cdev);
	}
	
	unregister_chrdev_region(MKDEV(numdev_major, numdev_minor), DEVICE_MINOR_NUM);
}

module_init(hello_init);
module_exit(hello_exit);

