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

//4.读端都关闭了，有进程向管道中写，那么该进程会收到信号SIGPIPE，通常会导致进程异常
//终止
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
			{	printf("pipe write is close\n");
				break;
			}
			count--;
			if (count == 0)
			{
				close(pipefd[0]);  //关闭读端。
				break;
			}
		}
	

		int status = 0;
		pid_t ret = waitpid(id,&status,0); //等待子进程，0表示阻塞式等待。
		if (ret > 0) //等待成功
		{
			printf("exit code:%d, signal:%d\n",(status>>8)&0xff,status&0xff);
			printf("exit code:%d, signal:%d\n",WEXITSTATUS(status), WTERMSIG(status));
		}

	}


	return 0;
}

