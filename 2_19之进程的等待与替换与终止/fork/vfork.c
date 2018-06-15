/*************************************************************************
	> File Name: vfork.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 17 Jul 2017 11:53:24 PM PDT
 ************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int glob = 6;
int main()
{
	int val = 88;
	printf("befork fork\n");

	pid_t id = vfork();
	if(id < 0)
	{
		perror("fork error");
	}
	else if (id == 0)
	{
		sleep(3);
		printf("this is child process\n");
		glob++;
		val++;
	}
	else
	{
		printf("this is father process\n");
	}
	printf("pid = %d, ppid=%d, glob = %d, var = %d\n",getpid(), getppid(), glob, val );
	return 0;
}
