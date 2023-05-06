#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>

/*
内核模块，工作队列

*/

static struct workqueue_struct *queue = NULL;
static struct work_struct work;

//工作队列处理程序
static void work_handler(struct work_struct *data)	
{
	printk(KERN_ALERT"work_handler is running!\n");
}

static int __init work_test_init(void)
{
	queue = create_singlethread_workqueue("helloworld");	//创建一个单线程工作队列
	if(!queue)
		goto err;
	
	INIT_WORK(&work, work_handler);	//创建工作
//	schedule_delay_work(&work, 100);	//调度工作提交至缺省的events工作线程,但延迟处理
	schedule_work(&work);		//调度工作提交至缺省的events工作线程
	printk("mark！！！\n");
	
	return 0;
	
	err:
	return -1;
}

static void __exit work_test_exit(void){
	destroy_workqueue(queue);
	printk(KERN_ALERT"work queue destroyed!\n");
	return 0;
}

module_init(work_test_init);
module_exit(work_test_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mr Yu");
MODULE_DESCRIPTION("tasklet test");
MODULE_ALIAS("tasklet_test");
