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
#include<string.h>

//client: 写 

int main()
{

	int fd = open("./fifo有名管道",O_WRONLY); //open返回新的文件描述符。只写的形式打开，返回这个文件的描述符。

	if (fd < 0)
	{
		perror("open");
		return 2;
	}
	
	char buf[128]; //这个数组的意思是从键盘中读取的字符流，最后要将这个字符流发送给另外一个进程。
	while(1)
	{
		printf("Please Enter#");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1); //从键盘中读，好发给server
		if (s>0)//在这里简单的假设从键盘中读取不会出错。
		{
			//buf[s] = '\0'; //会读取到我们最后按的回车符。
			buf[s-1] = '\0';  //把回车符换成了结束符。

			write(fd,buf,strlen(buf)); //将字符串写入这个文件不需要将\0写入。
		}
	}

//写端关闭，读端读完后，会退出。
	close(fd);//关闭这个文件
	return 0;
}


