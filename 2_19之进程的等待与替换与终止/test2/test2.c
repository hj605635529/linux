/*************************************************************************
	> File Name: test2.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 19 Feb 2017 05:45:06 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
int main()
{

	const char * msg = "hello printf\n";
	const char * msg1 = "hello fwrite\n";
	const char * msg2 = "hello write\n";
	printf("printf:%s",msg);
	fwrite(msg1,1,strlen(msg1),stdout);
	write(1,msg2,strlen(msg2));

	


	pid_t pid = fork();

	if (pid == 0)
	{//child


	}
	else
	{//father

	}

return 0;



}
