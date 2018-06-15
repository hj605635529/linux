/*************************************************************************
	> File Name: my_daemon.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Fri 12 May 2017 09:20:45 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>



void mydaemon()
{
	umask(0);  //1.重设文件权限，守护进程创建最高的文件权限。

	pid_t pid = fork();
	if(pid < 0)
	{

		perror("fork");
		exit(1);
	}
	if(pid > 0)
	{
		exit(0);  //2.父进程退出，子进程成为一个孤儿进程，（1）让出shell执行其他的命令。（2）保证子进程不是组长进程。（因为此时组长进程是1号进程）
	}

	pid_t sid = setsid();  //3.子进程创建一个新的会话。脱离终端控制。
	if(sid < 0)
	{
		perror("setsid");
		exit(2);
	}

	chdir("/");  //4.改变根目录

	close(0);
	close(1);
	close(2);  //5.关闭文件描述符，因为已经脱离终端了，文件描述符就没用了，关闭它节省资源。

	signal(SIGCHLD,SIG_IGN); //6.捕捉SIGCHLD信号，这是因为如果在守护进程中创建子进程，子进程退出需要回收子进程的资源。


}



int main()
{
	mydaemon();

	while(1);  //这个while循环是为了方便查看这个程序确实运行了，也就是守护进程确实被创建了。

	return 0;
}
