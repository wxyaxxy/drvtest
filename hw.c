#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
    int fd,retvalue;
    char *filename;
    if(argc!=2)
    {
        printf("Error usage\n");
        return -1;
    }
    printf("%s\n",argv[1]);
    printf("canshu=%d\n",atoi(argv[1]));
    char *str = "12345.67";
    int n;
    n = atoi(str);
    printf("n=%d\n",n);
    printf("%s\n",str);
    return 0;
}