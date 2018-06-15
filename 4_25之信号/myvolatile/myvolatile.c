/*************************************************************************
	> File Name: myvolatile.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Thu 27 Apr 2017 01:37:31 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>



int flag = 0;


void handler(int signum)
{
	printf("flag = 1\n");
	flag = 1;
	sleep(1);
	printf("handler finish\n");
}


int main()
{

	/*
	struct sigaction act,oact;
	act.sa_handler = handler;
	act.sa_flags = 0;
	oact.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigemptyset(&oact.sa_mask);
	
	sigaction(2,&atc,&oact);
*/
	signal(2,handler);


	while(!flag)
	{
		printf("hello world\n");
		sleep(1);
	}
	
	printf("main exit\n");

	return 0;
}


