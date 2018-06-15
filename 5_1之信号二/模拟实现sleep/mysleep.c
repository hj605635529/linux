/*************************************************************************
	> File Name: mysleep.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 30 Apr 2017 10:21:22 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void handler(int sig)//程序在睡眠区间什么也不做，这里自定义也不执行任何操作
{
	
}

/*

int mysleep(int timecount)
{
	struct sigaction act,oact;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	unsigned int unslept = 0;

	sigaction(SIGALRM,&act,&oact);//如果不捕捉，SIGALRM信号直接将进程终止，

	alarm(timecount);//timecount秒后发送一个SIGALRM信号。

	pause(); //将进程挂起，直到有信号递达。

	unslept = alarm(0); //参数为0表示清空闹钟。返回值表示上次闹钟剩下的时间。

	sigaction(SIGALRM,&oact,NULL); // 恢复默认信号处理动作

	return unslept;
}

*/


//版本一有问题：如果设置好闹钟，但是进程被切出去了，有可能当切回来的时候，闹钟已经响了。要保证闹钟在切回来之前不可能响。
//在切回来之前先屏蔽信号，切回来之后取消屏蔽。
int mysleep(int timecount)
{
	struct sigaction act,oact;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	unsigned int unslept = 0;
	sigaction(SIGALRM,&act,&oact); //注册信号捕捉函数。


	sigset_t newmask,oldmask,suspmask;  //定义信号集。
	sigemptyset(&newmask); //初始化。
	sigaddset(&newmask,SIGALRM); 
	sigprocmask(SIG_BLOCK,&newmask,&oldmask);//将这个信号加入到屏蔽字当中。

	alarm(timecount);//设置好闹钟，下一步就需要屏蔽闹钟信号了，防止当闹钟设置好就被切出去了，从这里可以看出屏蔽信号应该放在设置闹钟的前面，要不然闹钟已经响了，没有执行屏蔽信号代码，导致再切回来的时候等不到闹钟了。

	suspmask = oldmask;
	sigdelset(&suspmask,SIGALRM); //确保suspmask中没有屏蔽SIGALRM信号。
	sigsuspend(&suspmask);//用suspmask去替换block表，从而临时解除对SIGALRM信号的阻塞

	unslept = alarm(0);//取消闹钟。
	sigaction(SIGALRM,&oact,NULL);
	sigprocmask(SIG_SETMASK,&oldmask,NULL);  //恢复之前的系统默认信号和默认信号处理。

	return unslept;


}


int main()
{
	while(1)
	{
		unsigned int time = mysleep(5);
		printf("time = %d\n",time);
		printf("hello world\n");
	}
	return 0;
}
