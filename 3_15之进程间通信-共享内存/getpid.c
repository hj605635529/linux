/*************************************************************************
  > File Name: getpid.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: Sat 22 Jul 2017 10:20:57 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//int shmctl(int shmid, int cmd, struct shmid_ds *buf);
int main()
{
	
	int shmid = 1998848;
	struct shmid_ds buf;
	int ret = shmctl(shmid, IPC_STAT, &buf);
	if(ret < 0)
	{
		perror("shmctl");
	}
	printf("cpid = %d, lpid = %d\n",buf.shm_cpid, buf.shm_lpid); //获取创建pid和最后使用pid.
	printf("hello...\n");
	return 0;
}

