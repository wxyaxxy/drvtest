#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

int main(int argc,char *argv[])
{
    int fd,retvalue;
    char *filename;
    if(argc!=2)
    {
        printf("Error usage\n");
        return -1;
    }
    fd = open("/dev/buzz",O_RDWR);
    if(fd<0)
    {
        printf("....\n");
        printf("can not open file\n");
        return -1;
    }
    unsigned int zhi = 0;
    zhi = atoi(argv[1]);
    printf("zhi=%d\n",zhi);
    if(zhi)
    {
        retvalue = write(fd,&zhi,1);
        printf("zhi fei 0");
        if(retvalue <0)
        {
            printf("write file failed\n");
        }
    }
    else
    {
        retvalue = write(fd,&zhi,1);
        printf("zhi shi 0");
        if(retvalue <0)
        {
            printf("write file failed\n");
        }
    }
    retvalue = close(fd);
    if(retvalue<0)
    {
        printf("close failed");
        return -1;
    }

    return 0;
}