/*************************************************************************
	> File Name: main.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Wed 15 Mar 2017 12:01:52 AM PDT
 ************************************************************************/

#include"sem.h"
#include<unistd.h>

int main()
{
	int semid = creat_sem(1);
	int ret = init_sem(semid);//信号量这里要特别小心，需要自己去初始化。
	if (ret < 0)
	{
		return -1;
	}
	printf("semid:%d\n",semid);
	pid_t id = fork();
	if (id == 0)
	{//child
		while (1)
		{
			p_sem(semid,0);
			usleep(10002);
			printf("A");
			fflush(stdout);
			usleep(1080);
			printf("A");
			fflush(stdout);
			v_sem(semid,0);
		}
		exit(0);  //子进程退出。
	}
	else
	{
		while (1)
		{
			p_sem(semid,0);
			usleep(1002);
			printf("B");
			fflush(stdout);
			usleep(10080);
			printf("B");
			fflush(stdout);
			v_sem(semid,0);
		}
		wait(NULL);
	}
printf("semid = %d\n",semid);
sleep(5);
	destroy_sem(semid);

	return 0;
}
