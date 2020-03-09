#include <linux/init.h>
#include <linux/module.h>

/*驱动注册的头文件，包含驱动的结构体和注册和卸载的函数*/
#include <linux/platform_device.h>
/*注册杂项设备*/
#include <linux/miscdevice.h>
/*驱动注册的文件结构体*/
#include <linux/fs.h>
/*Linux中申请gpio的头文件*/
#include <linux/gpio.h>
/*三星平台的gpio配置函数头文件*/
/*三星平台exynos系列平台，gpio配置参数宏定义头文件*/
#include <plat/gpio-cfg.h>
#include <mach/gpio.h>
/*三星平台4412平台，gpio宏定义头文件*/
#include <mach/gpio-exynos4.h> 

#define DRIVER_NAME "hello"
#define DEVICE_NAME "hello"

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("ky");

static int hello_open(struct inode *Inode, struct file *File){
	printk(KERN_EMERG "\t hello_open\n");
	return 0;
}

static int hello_release(struct inode *Inode, struct file *File){
	printk(KERN_EMERG "\t hello_release\n");
	return 0;
}

static long hello_unlocked_ioctl(struct file *File, unsigned int cmd, unsigned long arg){
	printk(KERN_EMERG "\t hello_unlocked_ioctl\n");
	printk(KERN_EMERG "\t cmd = %d, arg = %ld\n", cmd ,arg);
	
	if(cmd > 1){
		printk(KERN_EMERG "cmd = 0 or cmd = 1\n");
		return ;
	}
	
	if(arg > 1){
		printk(KERN_EMERG "arg = 1\n");
		return ;
	}
	
	gpio_set_value(EXYNOS4_GPL2(0),cmd);
	
	return 0;	
}

struct file_operations hello_ops ={
	.owner = THIS_MODULE,
	.open = hello_open,
	.release = hello_release,
	.unlocked_ioctl = hello_unlocked_ioctl,
};

struct miscdevice hell_dev ={
	.minor = MISC_DYNAMIC_MINOR,   //自动分配
	.name = DEVICE_NAME,
	.fops = &hello_ops,
};

static int hello_probe(struct platform_device *pdv){
	int ret = 0;
	
	printk(KERN_EMERG "\tinitialized\n");
	
	ret = gpio_request(EXYNOS4_GPL2(0), "LEDS");
	if(ret < 0){
		printk(KERN_EMERG "gpio_request EXYNOS4_GPL2(0) failed\n");
		return ret;
	}
	
	s3c_gpio_cfgpin(EXYNOS4_GPL2(0), S3C_GPIO_OUTPUT);
	
	gpio_set_value(EXYNOS4_GPL2(0), 0);
	
	misc_register(&hell_dev);   //注册设备节点
	return 0;
}

static int hello_remove(struct platform_device *pdv){
	printk(KERN_EMERG "\remove\n");
	misc_deregister(&hell_dev);
	return 0;
}

static void hello_shutdown(struct platform_device *pdv){
	
	;
}

static int hello_suspend(struct platform_device *pdv, pm_message_t state){
	
	return 0;
}

static int hello_resume(struct platform_device *pdv){
	
	return 0;
}

struct platform_driver hello_driver = {
	.probe = hello_probe,
	.remove = hello_remove,
	.shutdown = hello_shutdown,
	.suspend = hello_suspend,
	.resume = hello_resume,
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
	}
};

static int hello_init(void) 
{
	int DriverState;
	
	printk(KERN_EMERG "HELLO WORLD enter!\n");
	DriverState = platform_driver_register(&hello_driver);
	
	printk(KERN_EMERG "\tDriverState is %d\n",DriverState);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_EMERG "HELLO WORLD exit!\n");
	
	platform_driver_unregister(&hello_driver);	
}

module_init(hello_init);
module_exit(hello_exit);

