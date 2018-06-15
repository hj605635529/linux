/*************************************************************************
	> File Name: env.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 09 Jul 2017 04:44:11 AM PDT
 ************************************************************************/

#include<stdio.h>


int main()
{
	int i = 0;
	extern char **environ;
	for(; environ[i] != NULL; ++i)
	{
		printf("%s\n",environ[i]);
	}

	return 0;

}
