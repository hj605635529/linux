/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 20 Feb 2017 07:09:43 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{

	pid_t id = fork();

	if (id == 0)
	{

		while (1)
		{
			printf("child:pid:%d  ppid:%d\n",getpid(),getppid());
			sleep(1);
		}
		printf("work is done,child is begin done..\n");
		exit(21);
	}
	else
	{
		printf("father:pid :%d  ppid :%d\n,", getpid(),getppid());

		int status = 0;
		int ret = 0;
		do
		{
			printf("i am father,i am reading again...\n");
			sleep(1);
		}while((ret = waitpid(id,&status,WNOHANG ))==0); //WNOHANG 时，返回值为0，说明状态没有变化，也就是子进程没有退出。父进程还需要等待。返回值大于0，等待成功。返回子进程的ID.错误返回-1.

		if (ret == -1)
		{
			printf("failed...\n");
		}
		else
		{
			printf("wait is success.. code = %d  signal = %d\n",(status>>8)&0xff ,status & 0xff);
		}

	}

	return 0;
}
