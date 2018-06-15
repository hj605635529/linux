/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Thu 16 Feb 2017 01:53:23 AM PST
 ************************************************************************/

#include<stdio.h>

int fun()
{
	printf("this is a fun fun\n");
	int i = 0;
	int sum = 0;

	for (; i <=100; i++ )
	{
		sum += i;
	}
	return sum;
}

int main()
{
	printf("this is a main fun\n");
	int sum = 0; 
	sum = fun();
	printf("sum = %d\n",sum);
	return 0;
}
