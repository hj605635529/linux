/*************************************************************************
	> File Name: listparams.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 05:29:43 AM PDT
 ************************************************************************/

#include<stdio.h>


int main(int argc, const char *argv[])
{
	int i = 0;
	for(; i < argc; ++i)
	{
		printf("argv[%d]:%s\n",i, argv[i]);
	}
	return 0;
}
