/*************************************************************************
	> File Name: test3.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 06:18:51 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>


void fun1()
{
	printf("this is fun function\n");
}

void fun2()
{
	printf("this is fun2 function\n");
}

void fun3()
{
	printf("this is fun3 function\n");
}
int main()
{

	printf("this is man function\n");
	atexit(fun1);
	printf("the fun1 is back\n");
	atexit(fun2);
	printf("the fun2 is back\n");
	atexit(fun3);
	printf("the fun3 is back\n");
	sleep(5);

	return 0;



}
