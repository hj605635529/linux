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

//2.写端没有关闭，而且写端没有向管道中写数据，那么剩下的数据被读取后，再次read
//会阻塞，直到管道中有数据可读了才读取数据并返回。
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
		const char *msg = "hello bit";
		int count = 5;
		while (1)
		{
			write(pipefd[1],msg,strlen(msg));  //往管道中写，所以是pipefd[1],
			count--;
			if (count == 0)//先写五条记录，睡5秒，再写，看读的状态
			{
				sleep(5);
				count--;
			}
			sleep(1);
		}

		close(pipefd[1]);  //写完关闭写端
		exit(0);
	}
	else
	{//father -> read

		close(pipefd[1]); //关闭写端

		int count = 5;
		char buf[128];
		while (1)
		{
			//读的快，写的慢，所以读要等待
			ssize_t _s = read(pipefd[0],buf,sizeof(buf)-1); //从管道中读。
			if(_s > 0)
			{			
				buf[_s] = '\0';
				printf("child->father: %s\n",buf);
			}
			else if (_s == 0) //读到文件末尾
			{
				printf("pipe write is close\n");
				break;
			}
			count--;
		}
		close(pipefd[0]);//读完，关闭读端
	}



	return 0;
}
//3.读端一直不读，写端一直写，当写满了，不会再写，阻塞，等待你读
