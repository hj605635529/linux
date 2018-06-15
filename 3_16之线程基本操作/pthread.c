/*************************************************************************
	> File Name: pthread.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Thu 16 Mar 2017 02:33:57 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void * thread_run(void * arg)
{
	while (1)
	{
		printf("I am shm...mytid:%lu...pid:%d\n",pthread_self(),getpid());
		sleep(1);
	}
	return 0;
}

int main()
{

	pthread_t id;
	pthread_create(&id,NULL,thread_run,NULL);//这个id其实就是新线程的id
	printf("id = %lu\n",id);
	while (1)//两个线程的pid和ppid都是一样的，tid不同。
	{
		printf("I am main...mytid:%lu...pid:%d\n",pthread_self(),getpid());
		sleep(3);
	}
	return 0;
}
