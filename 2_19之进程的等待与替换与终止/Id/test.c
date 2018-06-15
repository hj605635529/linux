/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 11:28:03 PM PST
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

int main()
{

	printf("pid = %d, ppid = %d, uid = %d,gid =  %d,euid =  %d,egid =  %d\n",
			getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());

	char *msg = "hello world\n";
	FILE *fp = fopen("./log","w");
	if (fp == 0)
	{
		perror("fail\n");
		return -1;
	}

	int count = 10;
	while (count)
	{
		fwrite(msg,1,strlen(msg),fp);
		count--;
	}

	



	return 0;
}
