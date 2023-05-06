#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/interrupt.h>
/*
内核模块，小任务机制

*/

static struct tasklet_struct my_tasklet;

//小任务处理程序
static void tasklet_handler(unsigned long data)	
{
	printk(KERN_ALERT"tasklet_handler is running!\n");
}

static int __init tasklet_test_init(void)
{
	tasklet_init(&my_tasklet, tasklet_handler, 0);
	tasklet_schedule(&my_tasklet);
	printk("mark!!\n");
	return 0;
}

static void __exit tasklet_test_exit(void){
	tasklet_kill(&my_tasklet);
	printk(KERN_ALERT"tasklet_handler leaving!\n");
	return 0;
}

module_init(tasklet_test_init);
module_exit(tasklet_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mr Yu");
MODULE_DESCRIPTION("tasklet test");
MODULE_ALIAS("tasklet_test");
