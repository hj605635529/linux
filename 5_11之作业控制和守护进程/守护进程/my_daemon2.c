/*************************************************************************
	> File Name: my_daemon2.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 04 Jun 2017 01:47:51 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void mydaemon2()
{
	umask(0);

	pid_t pid = fork();
	if(pid > 0)
	{
		exit(0);  //父进程退出。
	}

	//子进程
	
	pid_t sid = setsid(); //子进程创建一个新的会话，脱离终端控制。
	if(sid < 0)
	{
		perror("setsid");
		exit(1);
	}

	if(fork() > 0) //子进程再次fork出孙子进程，因为子进程是新的会话的会首进程，可以去再次打开控制终端的，,如果再fork()一次，孙子进程id != sid,就无法打开新的控制终端了，
	{
		exit(0);
	}

	chdir("/");

	close(0);
	close(1);
	close(2);

	signal(SIGCHLD,SIG_IGN);


}


int main()
{
	mydaemon2();

	while(1);

	return 0;
}



