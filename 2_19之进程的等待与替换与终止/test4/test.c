/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 09:51:32 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int main()
{

	printf("hello world");
	sleep(5);

	exit(0);


//pid_t id = fork();
//	if (id == 0)
//	{//child
//		printf("child:%d,%d\n",getpid(),getppid());
//		while(1);
//	}
//	else
//	{//father
//
//		printf("father:%d,%d\n",getpid(),getppid());
//		sleep(5);
//		exit(0);
//	}

//_Exit(0);
}
