/*************************************************************************
	> File Name: pipe.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: 2017年02月22日 星期三 19时53分04秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>

//server:  读

int main()
{
	umask(0);//表示不去除权限
	if(mkfifo("./fifo有名管道",0666|S_IFIFO) < 0)//在当前目录下创建一个管道文件fifo，如果<0表示创建失败,文件的权限是(mode & ~umask)
	{ //int mkfifo(const char* pathname,mode_t mode) mode表示你要创建文件的权限，S_IFIFO|0666指明创建一个命名管道且存取权限为0666。
		perror("mkfifo");
		return 1;
	}

	int fd = open("./fifo有名管道",O_RDONLY); //open返回新的文件描述符。只读的形式打开，返回这个文件的描述符。

	if (fd < 0)
	{
		perror("open");
		return 2;
	}
	
	char buf[128]; //从文件中读取，打印
	while(1)
	{
		ssize_t s = read(fd,buf,sizeof(buf)-1); //从文件中读取
		if (s>0)//s>0表示读取的字符数，s=0表示读到文件末尾了，s<0表示读取失败
		{
			buf[s] = '\0'; 
			printf("client# %s\n",buf);
		}
		else if (s==0) //写端关闭，才能读到文件末尾
		{
			printf("client quit! I should quit!\n");
			break;
		}
		else
		{
			perror("read");
			break;
		}

	}


	close(fd);//关闭这个文件
	return 0;
}
