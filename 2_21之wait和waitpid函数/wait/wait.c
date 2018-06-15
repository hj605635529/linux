/*************************************************************************
	> File Name: wait.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 21 Feb 2017 09:23:25 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>



int main()
{
	int count = 0;
	pid_t pid = fork();
	int status = -1;

	if (pid < 0)
	{
		printf("fork error \n");
	}
	else if (pid > 0)
	{//father
		printf("this is parent ,pid = %d\n",getpid());
		pid_t id = wait(&status);//等待子进程，返回值为子进程的pid,
		printf("child process is end,id = %d\n",id);
	}
	else
	{
		printf("this is child,pid =%d,ppid = %d\n",getpid(),getppid());
		int i = 0;
		for (i =0 ;i < 10; i++)
		{
			count++;
			sleep(2);
			printf("count = %d\n",count);
		}
		exit(5);
	}

	printf("end of program from pid = %d\n",getpid()); //子进程结束，此时getpid（）得到的是父进程的pid.

	printf("child exit status is %d\n",WEXITSTATUS(status)); //子进程正常退出，退出码
	printf("id = %d\n",wait(NULL)); //如果没有子进程，此时等待会返回-1.
	return 0;
}
