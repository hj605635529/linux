/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 25 Apr 2017 06:48:00 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

int main()
{
	while(1)
	{
		printf("get pid :%d\n",getpid());
		sleep(1);
	}
	return 0;
}
