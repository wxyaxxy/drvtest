#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>

#define CHRDEVBASE_MAJOR 200
#define CHRDEVBASE_NAME "chrdevbase"

static char readbuf[100];
static char writebuf[100];
static char kerneldata[]={"kernel data!"};

static int chrdevbase_open(struct inode *inode,struct file *filp)
{
    printk("open\n");
    return 0;
}

static ssize_t chrdevbase_read(struct file *filp,char __user *buf,size_t cnt,loff_t *offt)
{
    int retvalue = 0;
    memcpy(readbuf,kerneldata,sizeof(kerneldata));
    retvalue = copy_to_user(buf,readbuf,cnt);
    if(retvalue == 0)
    {
        printk("kernel sentdata ok \n");
    }
    else
    {
        printk("kernel sentdata failed\n");
    }
    return 0;
}
static ssize_t chrdevbase_write(struct file *filp,const char __user *buf,size_t cnt,loff_t *offt)
{
    int retvalue = 0;
    retvalue = copy_from_user(writebuf,buf,cnt);
    if(retvalue==0)
    {
        printk("kernel recevedata:%s\n",writebuf);
    }
    else
    {
        printk("kernel recevedat failed\n");
    }
    return 0;
}

static int chrdevbase_release(struct inode *inode,struct file *filp)
{
    printk("release!\n");
    return 0;
}

static struct file_operations chrdevbase_fops ={
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .read = chrdevbase_read,
    .write = chrdevbase_write,
    .release = chrdevbase_release,
};

static int __init chrdevbase_init(void)
{
    int retvalue = 0;
    retvalue = register_chrdev(CHRDEVBASE_MAJOR,CHRDEVBASE_NAME,&chrdevbase_fops);
    printk("register sucess\n");
    return 0;
}

static void __exit chrdevbase_exit(void)
{
    unregister_chrdev(CHRDEVBASE_MAJOR,CHRDEVBASE_NAME);
    printk("unregister\n");
}

module_init(chrdevbase_init);
module_exit(chrdevbase_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("wangbo");