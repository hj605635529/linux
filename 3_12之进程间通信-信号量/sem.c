/*************************************************************************
	> File Name: sem.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 12 Mar 2017 12:21:53 AM PST
 ************************************************************************/

#include"sem.h"


static int comm_sem(int nsems, int flags)//函数只在这个文件中使用，
{

	key_t K = ftok(PATHNAME,PROJ_ID);//获取键值。
	if (K < 0)
	{
		perror("ftok");
		return -1;
	}
	int semid = semget(K,nsems,flags);//得到信号量集id.nsems表示信号量集中的个数，创建新集合的时候，必须指定nsems,引用现有的，则设定nsem为0.
	if (semid < 0)
	{
		perror("semget");
		return -2;
	}
	return semid;
}


int creat_sem(int nsems)  //创建几个信号量。
{
	return comm_sem(nsems,IPC_CREAT|IPC_EXCL|0666); //创建一个信号量。信号量的权限为666。但是不知道为啥监控检测到的是146
}


int init_sem(int semid) //对信号量初始化。
{
	union semun  //semctl的第四个参数是可以选择的，是共用体semun.
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
		struct seminfo *_buf;
	};
	union semun semun;
	semun.val = 1;
	int ret = semctl(semid,0,SETVAL,semun);//第二个参数表示信号量集数组上的下标，表示某一个信号量。第三个参数表示用联合体中val成员的值设置信号量集合中单个信号量的值。函数成功返回0.
	if (ret < 0)
	{
		perror("semctl");
		return -1;
	}
	return ret;

}


int get_sem()  //得到信号量。
{
	return comm_sem(0,IPC_CREAT); //获取现有的，nsems为0.
}


int destroy_sem(int semid) //销毁信号量。
{
	int ret = semctl(semid,0,IPC_RMID); //cmd: IPC_RMID表示从内核中删除信号量集合。
	if (ret < 0)
	{
		perror("destroy_sem");
		return -1;
	}
	return ret;
}

static int comm_op(int semid,int which,int op) //对信号量中的那个信号量进行哪一种操作。
{

	struct sembuf sembuf;  //这个结构不需要自己定义
	sembuf.sem_num = which;//sem_num表示某一个信号量下标。
	sembuf.sem_op = op;//sem_op表示操作方式。
	sembuf.sem_flg = 0;//sem_flag 可以为0，IPC_NOWAIT ,SEM_UNDO,一般用SEM_UNDO 可以防止死锁。
	int ret = semop(semid,&sembuf,1);//semop第三个参数为nsops:表示进行操作信号量的个数，即sops结构变量的个数，需大于或等于1，最常见的此值设置为1，只完成对一个信号两个的操作。
	if (ret < 0)
	{
		perror("semop");
		return -1;
	}
	return ret;
}

int p_sem(int semid,int which)//对信号量中某一个信号操作
{
	return(comm_op(semid,which,-1));  //p进行减1操作。
}

int v_sem(int semid,int which)//对信号量中某一个信号操作。
{
	return comm_op(semid,which,1);//v进行加1操作。
}
 
