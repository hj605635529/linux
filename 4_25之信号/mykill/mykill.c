/*************************************************************************
	> File Name: mykill.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 25 Apr 2017 06:39:19 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
/*
void handler(int sig)
{
	printf("get a sig:%d\n",sig);
}

int main(int argc, char *argv[])
{

	signal(2,handler);  //
	sleep(5);
	raise(2);  //自己给自己发送2号信号。

	while(1)
	{
		sleep(1);
	}


	//mykill 1234 9

//	int proc = atoi(argv[1]);
//	int sig = atoi(argv[2]);
//	kill(proc,sig);//向proc这个进程发送sig信号。
	return 0;
}

*/
/*
int count = 0; //用一个全局变量。
void handler(int sig)
{
	printf("count = %d\n",count);
	abort();
}
int main()
{
//	int count = 0;
	alarm(1);  //1秒钟闹钟，进程结束。
	signal(SIGALRM,handler);
	while(1)
	{
		count++;
	//	printf("count = %d\n",count);
	}
	return 0;
}

*/

void show_pending(sigset_t *pending)
{
	int i = 1;
	for(; i < 32;i++)  //1到31号信号，看这31个信号是否在pending表中。
	{
		if (sigismember(pending,i) )
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	printf("\n");
}

void handler(int sig)
{
	printf("diver %d begin execu handler\n",sig);
}


int main()
{

	signal(2,handler);
	
	sigset_t block,oblock;  //新的阻塞表和老的阻塞表。
	sigset_t pending; //未决表。

	sigemptyset(&block);    //初始化。
	sigemptyset(&oblock);
	sigemptyset(&pending);
	sigaddset(&block,2);  //将2号信号加入阻塞表中。

	sigprocmask(SIG_SETMASK,&block,&oblock);//设置当前的阻塞表为block。将老的阻塞表赋给oblock.

	int count = 0;
	while(1)
	{
		sigpending(&pending);	//拿到未决表。
		show_pending(&pending); //显示出来。
		sleep(1);

		if(count == 10)
		{
			sigprocmask(SIG_SETMASK,&oblock,NULL);  //设置当前的阻塞表为oblock,oblock表中没有阻塞信号，也就是说解除2号阻塞，并且丢弃原来的阻塞表。
		}
		count++;
	}

	return 0;
}
