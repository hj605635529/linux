/*************************************************************************
	> File Name: sigchld.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 01 May 2017 08:59:25 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<stdlib.h>


/*
void my_sigchld(int sig)
{
	int status = 0;
	pid_t ret = waitpid(-1,&status, 0);  //-1表示等待任何一个子进程。
	
	if(ret > 0)
	{
		printf("sig:%d,code:%d\n",status&0xff,(status>>8)&0xff);
	}
}
*/

//如果一个父进程有100个子进程，收到好多SIGCHLD信号，只会保存一份，只能wait一份，故应该修改代码//防止这种情况发生。

void my_sigchld(int sig)
{
	int status = 0;
	int ret = 0;
	while(( ret=waitpid(-1,&status,0))  > 0  )
	{
		printf("sig:%d\n",sig);
	}
}

int main()
{
	pid_t id = fork();
	if( id < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(id == 0) //child
	{
		sleep(10);  //保证父进程已经注册完信号处理函数，父，子进程谁先运行不知道
		printf("child is quit\n");
		exit(1);//子进程在终止的时候给父进程发SIGCHLD信号，
	}
	else
	{
		signal(SIGCHLD,my_sigchld);
		while(1)  //父进程一直做自己的事情，等到子进程发送信号才回收子进程的资源
		{
			sleep(1);
			printf("father is working\n");
		}
	}
return 0;
}
