/*************************************************************************
	> File Name: shell.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Wed 22 Feb 2017 02:18:26 PM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

//步骤：1.从键盘中读取一个字符串，2.解析这个字符串，3.子进程替换，4.父进程等待


int main()
{

	char cmd[128];
	while (1)
	{
		printf("[test@localhost myshell]#   ");
		fflush(stdout);

		ssize_t _s = read(0,cmd,sizeof(cmd)-1);

		if (_s > 0)
		{
			cmd[_s-1] = '\0';//表示从键盘上读取字符，但是换行符不读取,所以是_s-1。
		}
		else
		{
			perror("read");
			return 1;
		}

		char *_argv[32];
		_argv[0] = cmd;
		int i = 1;

//将这个字符串以空格为解析符，解析成指针数组。
		char *start = cmd;
		while(*start)
		{
			if(isspace(*start))
			{
				*start = '\0';
				start++;
				_argv[i] = start;
				i++;

			//	printf("i = %d\n",i);
			}
			else
			{
				start++;
			}
		}
	//	printf("NULL:i = %d\n",i);
		_argv[i] = NULL; //最后一个指针置空。

		pid_t id = fork();//创建子进程。
		if (id < 0)
		{
			perror("fork");
		}
		else if (id == 0)
		{//child
			execvp(_argv[0],_argv);//子进程去做系统替换。
			exit(1);
			
		}
		else
		{//father  父进程等待
			int status = 0;
			pid_t ret = waitpid(id,&status,0);
			if (ret > 0 && WIFEXITED(status))
			{
				printf("exit code :%d\n",WEXITSTATUS(status));
			}
			else
			{
				perror("waitpid");
			}
		}


	}
	return 0;
}

