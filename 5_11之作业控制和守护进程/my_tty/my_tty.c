/*************************************************************************
	> File Name: my_tty.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Thu 11 May 2017 02:38:08 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>


int main()
{
	printf("pid:%d\n",getpid());
	printf("in:%s\n",ttyname(0));
	printf("out:%s\n",ttyname(1));
	printf("err:%s\n",ttyname(2));
	return 0;
}


