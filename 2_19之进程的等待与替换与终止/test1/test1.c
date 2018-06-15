/*************************************************************************
	> File Name: test1.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 04:56:48 PM PST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{
	close(1); //关闭输出流

	char * pst = "hello world\n"; 

	FILE * fp = fopen("./log","w");

	if (fp == NULL)
	{
		perror("fopen....\n");
		exit(1);
	}

	int count = 10;
	while (count--)
	{
		printf("%s",pst);
		fflush(stdout);
	}

	fclose(fp);

	return 0;


}
