#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int debug = 1;
module_param(debug, int, 0644);
MODULE_PARM_DESC(debug, "debugging information");
#define dprintk(args...) if(debug){printk(KERN_DEBUG args);}
static int myparm = 10;
module_param(myparm, int, 0644);
MODULE_PARM_DESC(myparm, "kernel module parameter experiment.");

static int __init parm_init(void){
	dprintk("my linux kernel module init.\n");
	dprintk("module parameter = %d\n", myparm);
	return 0;
}
static void __exit parm_exit(void){
	printk("see you next time!\n");
}

module_init(parm_init);
module_exit(parm_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mr Yu");
MODULE_DESCRIPTION("kernel module paramter experiment");
MODULE_ALIAS("myparm");
