/*************************************************************************
	> File Name: execl.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 26 Feb 2017 12:11:34 AM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main()
{

/*	printf("I am a process\n");
	sleep(3);
	execl("/bin/ls","ls","-l","-i","-n","-a",NULL);//第一个参数表示文件路径， 后面的表示要执行的命令。

	printf("haha ,you can't see me !\n'");

*/

	pid_t id = fork();
	if (id < 0)
	{
		printf("new process failed\n");
		return 1;
	}
	else if (id == 0)  //child
	{
		printf("I am a process\n");
		sleep(3);
	//	execl("/bin/ls","ls","-a","-i","-n","-l",NULL);
	//
//		execlp("ls","ls","-a","-i","-n","-l",NULL);

		execl("./listparams", "aaaaa", "bbbbb", NULL);

		char *myargv[]= {"ls","-l","-a",NULL};
	//	execv("/bin/ls",myargv);
	
	//	execvp("ls",myargv);
	
		exit(2); //子进程被替换后，不会执行这句语句。
	}
	else
	{//father
		int status = 0;
		pid_t ret = waitpid(id ,&status,0); //等待子进程，0表示阻塞式等待。 当程序替换后这个也能等待成功，退出码为0
		if(WIFEXITED(status) && ret > 0) //ret == id,表示等待成功  子进程正常退出。
		{
			printf("wait success,exit code = %d\n",WEXITSTATUS(status));
		}
		else
		{
			printf("wait failed\n");
			return 3;
		}
	}


	return 0;
	
}
