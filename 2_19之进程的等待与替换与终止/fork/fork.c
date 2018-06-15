/*************************************************************************
	> File Name: fork.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 11:51:36 PM PST
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

	pid_t id = fork();
	if(id < 0)
	{
		perror("fork error");
	}
	else if (id == 0)
	{
		glob++;
		val++;
	}
	else
	{
		sleep(5);
	}
	printf("pid = %d, ppid=%d, glob = %d, var = %d\n",getpid(), getppid(), glob, val );
	return 0;
}
