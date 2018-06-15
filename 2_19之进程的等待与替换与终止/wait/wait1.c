/*************************************************************************
	> File Name: wait1.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: 2017年07月18日 星期二 02时42分35秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{

	pid_t pid;
	pid = fork();
	if(pid < 0)
	{
		perror("fork error");
		return 1;
	}
	else if(pid == 0)
	{
		printf("child is run , pid is :%d\n",getpid() );
		sleep(5);
		exit(233);
	}
	else
	{
		int status = 0;
		pid_t ret = waitpid(-1,&status, 0);//阻塞等待
		printf("this is test for wait\n");
		if( WIFEXITED(status) && ret == pid) //正常退出
		{
			printf("wait child 5s success,child return code is :%d\n",WEXITSTATUS(status) );
		}
		else
		{
			printf("wait child failed ,return .\n");
			return 1;
		}
	}

	//cout << "hello..."<<endl;
	printf("hello...\n");
	return 0;
}

