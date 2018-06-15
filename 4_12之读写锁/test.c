/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 11 Apr 2017 07:23:46 PM PDT
 ************************************************************************/
//互斥锁和二元信号量都是挂起等待锁。而读写锁是自旋锁，一直轮询，每个线程访问临界资源的时间都不能太久。try_lock是申请一次申请不到直接返回。不会自旋
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


int buf = 0;  //buf全局变量就是临界资源。
pthread_rwlock_t rwlock;  //读写锁

void *myread(void *arg)
{
	while (1)
	{
		if(	pthread_rwlock_tryrdlock(&rwlock) != 0) //申请锁失败
		{
			printf("writer is working!\n");
			printf("reader do othrer thing!\n");
			continue;  //继续申请锁

		}
		else
		{
			printf("read:%d\n",buf);
			pthread_rwlock_unlock(&rwlock); //释放锁
		}
	//	sleep(1);  
	}
}


void *mywrite(void *arg)
{
	while(1)
	{
		if(pthread_rwlock_trywrlock(&rwlock) != 0)
		{
			printf("reader is working!\n");
			printf("writer do other thing!\n");
			continue;
		}
		else
		{
			buf++;
			pthread_rwlock_unlock(&rwlock);
		}
	
	sleep(1);//写者隔1秒竞争一次锁资源
	}
}



int main()
{
	pthread_rwlock_init(&rwlock,NULL); //第二个参数是属性

	pthread_t id1,id2;
	pthread_create(&id1,NULL,myread,NULL);
	pthread_create(&id2,NULL,mywrite,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);

	pthread_rwlock_destroy(&rwlock);



	return 0;
}




