/*************************************************************************
	> File Name: guer.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 30 Jul 2017 12:52:34 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	pid_t id = fork();
	if(id == 0)
	{
		while(1)
		{
			printf("hello child\n");
		}

	}
	else
	{
		printf("father died....\n");
		exit(0);
	}

	return 0;

}
