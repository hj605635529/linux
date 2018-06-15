/*************************************************************************
	> File Name: pipe.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Wed 22 Feb 2017 11:46:32 PM PST
 ************************************************************************/


#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>


//匿名管道 单向的，只能用于有血缘关系的，常用于父子进程。
//5.写端一直写，读端一直不读取，就可以测出管道的大小了。
int main()
{
	int pipefd[2] = {0,0};
	if (pipe(pipefd) < 0)//int pipe(int pipefd[2]) 通过调用从pipe中拿出两个管道文件描述符，0表示读，1表示写。 成功的时候返回0，失败的时候返回-1.
	{
		perror("pipe");
		return 1;
	}

	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		return 2;
	}
	else if (id == 0)
	{//child -> writer

		close(pipefd[0]); //关闭读端
		const char *msg = "h";
		int count = 0;
		while (1)
		{
			write(pipefd[1],msg,strlen(msg));  //往管道中写，所以是pipefd[1],
			count++;
			printf("count = %d\n",count);
		}

		close(pipefd[1]);  //写完关闭写端
		exit(0);
	}
	else
	{//father -> read

		close(pipefd[1]); //关闭写端

		while (1)
		{
			;
		}

		
		close(pipefd[0]);//读完，关闭读端
	}



	return 0;
}
