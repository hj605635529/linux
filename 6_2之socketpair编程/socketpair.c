/*************************************************************************
	> File Name: socketpair.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Fri 02 Jun 2017 06:44:14 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	int fd[2];

	socketpair(AF_UNIX,SOCK_STREAM,0,fd);  //sockpair创建双向管道，本机通信

	pid  = fork();
	if(pid < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(pid == 0) //child
	{
		close(fd[0]);
		char *msg1 = "i am child";
		char buf1[512];
		while(1)
		{
			write(fd[1],msg1,strlen(msg1));
			ssize_t s = read(fd[1],buf1,sizeof(buf1) -1);
			buf1[s] = 0;  //因为这里不是从键盘中读入字符串，所以这里不需要s-1.
			printf("child say:%s\n",buf1);
		}

	}
	else //father
	{
		close(fd[1]);
		char *msg2 = "i am father";
		char buf2[512];
		while(1)
		{
			write(fd[0],msg2,strlen(msg2));
			ssize_t s = read(fd[0],buf2,sizeof(buf2) -1);
			buf2[s] = 0;  //因为这里不是从键盘中读入字符串，所以这里不需要s-1.
			printf("father say:%s\n",buf2);
		}

	}

	return 0;
}
