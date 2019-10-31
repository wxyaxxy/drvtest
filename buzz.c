#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>


#define CHRDEVBASE_MAJOR 200
#define CHRDEVBASE_NAME "buzz"

#define GPIO1_BASE 0x4804C000
#define GPIO_OE (GPIO1_BASE+0x134) //0 output 1 input
#define GPIO_DATAOUT (GPIO1_BASE+0X13C) //1 HIGH 0 LOW

static void __iomem *XUNI_GPIO_OE;
static void __iomem *XUNI_GPIO_DATAOUT;

static int chrdevbase_open(struct inode *inode,struct file *filp)
{
    printk("open\n");
    return 0;
}

static ssize_t chrdevbase_read(struct file *filp,char __user *buf,size_t cnt,loff_t *offt)
{
    // int retvalue = 0;
    // memcpy(readbuf,kerneldata,sizeof(kerneldata));
    // retvalue = copy_to_user(buf,readbuf,cnt);
    // if(retvalue == 0)
    // {
    //     printk("kernel sentdata ok \n");
    // }
    // else
    // {
    //     printk("kernel sentdata failed\n");
    // }
    return 0;
}
static ssize_t chrdevbase_write(struct file *filp,const char __user *buf,size_t cnt,loff_t *offt)
{
    int retvalue = 0;
    unsigned char databuf[1];
    unsigned char buzzer_state=0;
    retvalue = copy_from_user(databuf,buf,cnt);
    if(retvalue==0)
    {
        // printk("kernel recevedata:%s\n",writebuf);
        buzzer_state=databuf[0];
        if(buzzer_state)
        {
            retvalue = readl(XUNI_GPIO_DATAOUT);
            retvalue |= (1<<28);// gao dian ping 
            writel(retvalue,XUNI_GPIO_DATAOUT);        
        }
        else
        {
            retvalue = readl(XUNI_GPIO_DATAOUT);
            retvalue &= ~(1<<28);// gao dian ping 
            writel(retvalue,XUNI_GPIO_DATAOUT); 
        }
        
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
    .write = chrdevbase_write,
    .release = chrdevbase_release,
    .read = chrdevbase_read
};

static int __init chrdevbase_init(void)
{
    int retvalue = 0;
    unsigned int val =0;

    XUNI_GPIO_OE = ioremap(GPIO_OE,4);
    XUNI_GPIO_DATAOUT = ioremap(GPIO_DATAOUT,4);
    val = readl(XUNI_GPIO_OE);
    val &= ~(1<<28);//pei zhi shu chu
    writel(val,XUNI_GPIO_OE);

    val = readl(XUNI_GPIO_DATAOUT);
    val |= (1<<28);// gao dian ping 
    writel(val,XUNI_GPIO_DATAOUT);


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