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

	if (id == 0) //child
	{

		while (1)
		{
			printf("child:pid:%d  ppid:%d\n",getpid(),getppid());
			sleep(1);
		}
		printf("work is done,child is begin done..\n");
		exit(21);
	}
	else  //father
	{

		printf("father:pid :%d  ppid :%d\n", getpid(),getppid());

		int status = -1;
		//pid_t ret = waitpid(id,&status,0);//0表示阻塞式等待，WNOHANG表示非阻塞式等待
		pid_t ret = waitpid(id,&status,WNOHANG);//0表示阻塞式等待，WNOHANG表示非阻塞式等待
		printf("ret = %d\n",ret);
		if (ret == id)
		{
			printf("wait is success... code = %d  signal = %d\n",(status>>8)&0xff ,status & 0xff);
		}
		else
		{
			printf("wait is failed..status=%d\n",status);
		}
	}

	return 0;


}
