#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/cdev.h>
#include <asm/io.h>
#include <asm/switch_to.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/uaccess.h>

#define MYCDEV_MAJOR 300  /*主设备号，通过cat /proc/devices 查询，选择未使用的设备号*/
#define MYCDEV_SIZE 1024


static int mycdev_open(struct inode *inode, struct file *fp){
	return 0;
}

static int mycdev_release(struct inode *inode, struct file *fp){
	return 0;
}

/*实现read程序*/
static ssize_t mycdev_read(struct file *fp, char __user *buf, size_t size, loff_t *pos){
	unsigned long p = *pos;
	unsigned int count = size;
	char kernel_buf[MYCDEV_SIZE] = "This is mycdev driver!";
	int i;
	
	if(p >= MYCDEV_SIZE)
		return -1;
	if(count > MYCDEV_SIZE)
		count = MYCDEV_SIZE - p;
	if(copy_to_user(buf, kernel_buf, count) != 0){
		printk("read error!\n");
		
		return -1;
	}
	
	printk("reader: %d bytes was read.\n", count);
	
	return size;
}

/*实现write程序*/
static ssize_t mycdev_write(struct file *fp, const char __user *buf, size_t size, loff_t *pos){
	return size;
}

/*填充file operations结构*/
static const struct file_operations mycdev_fops = {
	.owner = THIS_MODULE,
	.open = mycdev_open,
	.release = mycdev_release,
	.read = mycdev_read,
	.write = mycdev_write,
};


/*模块初始化函数*/
static int __init mycdev_init(void){
	printk("mycdev driver is now starting!\n");
	
	/*注册驱动程序*/
	int ret = register_chrdev(MYCDEV_MAJOR, "my_cdev_driver", &mycdev_fops);
	
	if(ret < 0){
		printk("register failed!\n");
		return 0;
	}else{
		printk("register successfully!\n");
	}
	
	return 0;
}

/*卸载模块函数*/
static void __exit mycdev_exit(void){
	printk("mycdev driver is now leaving!\n");
	unregister_chrdev(MYCDEV_MAJOR, " ");
}

module_init(mycdev_init);
module_exit(mycdev_exit);

MODULE_LICENSE("GPL");