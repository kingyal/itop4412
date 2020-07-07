/*Description:字符类设备节点的驱动
 *Author:ky
 *Date:2020-06-24
 *History:2020-06-24  1st
 *Note：可通过ls /sys/class/查看生成的class
 *		可通过ls /dev 查看生成的两个设备节点
 *		加载模块的时候还可以使用命令生成设备节点(不需要在代码中添加生成设备节点的代码)，例如：
 *			mknod dev/test0 c 249 0
 *			mknod dev/test0 c 249 1
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
/*device create等class结构体*/
#include <linux/device.h>
/*Linux中申请gpio的头文件*/
#include <linux/gpio.h>
/*三星平台的gpio配置函数头文件*/
/*三星平台exynos系列平台，gpio配置参数宏定义头文件*/
#include <plat/gpio-cfg.h>
/*三星平台4412平台，gpio宏定义头文件*/
#include <mach/gpio-exynos4.h> 

#define DEVICE_NAME "chr_node"
#define DEVICE_MINOR_NUM 2
#define DEVICE_MAJOR 0
#define DEVICE_MINOR 0

#define DATA_SIZE 3000

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ky");

static int led_gpios[] = {
	EXYNOS4_GPL2(0), EXYNOS4_GPK1(1)
};

#define LED_NUM  ARRAY_SIZE(led_gpios)

/*主设备号*/
int numdev_major = DEVICE_MAJOR;
/*次设备号*/
int numdev_minor = DEVICE_MINOR;

module_param(numdev_major, int, S_IRUSR);
module_param(numdev_minor, int, S_IRUSR);

static struct class *myclass;


struct reg_dev{
	char *data;
	unsigned long size;
	struct cdev cdev;
	
};

struct reg_dev *my_devices;

static int chr_dev_node_open(struct inode *inode, struct file *file)
{
	printk(KERN_EMERG "chr_dev_node_open success\n");
	return 0;
}

static int chr_dev_node_release(struct inode *inode, struct file *file)
{
	printk(KERN_EMERG "chr_dev_node_release success\n");
	return 0;	
}

static long chr_dev_node_unlocked_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	printk(KERN_EMERG "chr_dev_node_unlocked_ioctl success\n");
	switch (cmd) 
	{
		case 0:
		case 1:
			if (arg > LED_NUM) {
				return -EINVAL;
			}
			gpio_set_value(led_gpios[arg],cmd);
			break;
		default:
		    return -EINVAL;
	}
	return 0;	
}

static ssize_t chr_dev_node_read(struct file *file, char __user* buf, size_t count, loff_t *f_ops)
{
	printk(KERN_EMERG "chr_dev_node_read success\n");
	return 0;	
}

static ssize_t chr_dev_node_write(struct file *file, const char __user* buf, size_t count, loff_t *f_ops)
{
	printk(KERN_EMERG "chr_dev_node_write success\n");
	return 0;	
}

static loff_t chr_dev_node_llseek(struct file *file, loff_t offset, int ence)
{
	printk(KERN_EMERG "chr_dev_node_llseek success\n");
	return 0;	
}

struct file_operations my_fops = {
	.owner = THIS_MODULE,
	.open = chr_dev_node_open,
	.release = chr_dev_node_release,
	.unlocked_ioctl = chr_dev_node_unlocked_ioctl,
	.read = chr_dev_node_read,
	.write = chr_dev_node_write,
	.llseek = chr_dev_node_llseek,
};

static int gpio_init()
{
	int i = 0;
	int ret;
	
	for (i = 0; i < LED_NUM; i++) {
			ret = gpio_request(led_gpios[i], "LEDS");
	if(ret){
		printk(KERN_EMERG "request GPIO %d for LED  failed, ret = %d\n", DEVICE_NAME, ret);
		return -1;
	}
	
	s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
	
	gpio_set_value(led_gpios[i], 0);
	}
	return 0;
}
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
		printk(KERN_EMERG "cdev add %d failed, err = %d\n", numdev_minor + index, err);
	} else {
		printk(KERN_EMERG "cdev add %d success\n", numdev_minor + index);
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
	
	myclass = class_create(THIS_MODULE, DEVICE_NAME);
	
	my_devices = kmalloc(DEVICE_MINOR_NUM * sizeof(struct reg_dev), GFP_KERNEL);
	if (!my_devices) {
		printk(KERN_EMERG "kmalloc failed\n");
		goto ERR_KMALLOC;
	}
	memset(my_devices, 0, DEVICE_MINOR_NUM * sizeof(struct reg_dev));
	
	for (i = 0; i < DEVICE_MINOR_NUM; i++) {
		my_devices[i].data = kmalloc(DATA_SIZE, GFP_KERNEL);
		memset(my_devices[i].data, 0, DATA_SIZE);
		/*注册设备*/
		reg_init_cdev(&my_devices[i], i);
		/*创建设备节点*/
		device_create(myclass, NULL, MKDEV(numdev_major, numdev_minor + i), NULL, DEVICE_NAME"%d", i);
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
		device_destroy(myclass,  MKDEV(numdev_major, numdev_minor + i));
		cdev_del(&my_devices[i].cdev);
		kfree(my_devices[i].data);
	}
	class_destroy(myclass);
	
	kfree(my_devices);
	
	for (i = 0; i < LED_NUM; i++) {
		gpio_free(led_gpios[i]);
	}
	
	unregister_chrdev_region(MKDEV(numdev_major, numdev_minor), DEVICE_MINOR_NUM);
}

module_init(hello_init);
module_exit(hello_exit);

