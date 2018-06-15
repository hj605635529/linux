/*************************************************************************
	> File Name: myvolatile.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 01 May 2017 08:36:36 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>

volatile int count = 0;//告诉编译器，不要优化，每次从内存中拿值。


void handler(int signo)
{
	printf("signo = %d\n",signo);
	count++;
}


int main()
{

	signal(2,handler);

	while(!count);
	printf("进程结束\n");
	return 0;
}
