/*************************************************************************
	> File Name: myproc.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 25 Apr 2017 04:58:08 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
#include<signal.h>

void handler(int sig) //自定义行为。
{
	printf("sig : %d\n",sig);
}

int main()
{
	//signal(8,handler);
	signal(3,handler);
	while(1)
	{
		printf("I am a proc\n");
		sleep(1);
		int a = 0;
		a = 1 / 0;  //除0错误，硬件异常。
	}
		signal(2,handler); //捕捉2号信号。这个语句放的位置没有关系，那都行。
	return 0;
}
