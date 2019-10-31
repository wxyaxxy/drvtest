#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/printk.h>


static ssize_t first_drv_write(struct file *file, const char __user *buf, size_t count, loff_t *ppos)
{
    printk("write\n");
    return 0;
}

static int first_drv_open(struct inode *inode, struct file *file)
{
    printk("open\n");
    return 0;
}

static struct file_operations first_drv_fops={
  .owner = THIS_MODULE,
  .open =  first_drv_open,
  .write = first_drv_write,
};

int first_drv_init(void)
{
    register_chrdev(111,"first_drv",&first_drv_fops);
    return 0;
}

void first_drv_exit(void)
{
    unregister_chrdev(111,"fisrt_drv");
}

module_init(first_drv_init);
module_exit(first_drv_exit);
MODULE_AUTHOR("Mocean Laboratories <info@mocean-labs.com>");
MODULE_LICENSE("GPL");
