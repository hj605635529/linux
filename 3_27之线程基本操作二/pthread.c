/*************************************************************************
	> File Name: pthread.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 27 Mar 2017 05:53:05 AM PDT
 ************************************************************************/


/*
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *thread1(void *_val1)
{
	printf("thread 1 returning....\n");
	sleep(5);
	return (void*)1;
}

void *thread2(void *_val2)
{
	printf("thread 2 exiting...\n");
	pthread_exit((void*)2);  //参数是返回的错误码。
}

void *thread3(void *_val3)
{
	while (1)
	{
		printf("pthread 3 is running ,wait for be cancal...\n");
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	void *tret;


	//thread 1 return;
	pthread_create(&tid,NULL,thread1,NULL);
	pthread_join(tid,&tret);  //阻塞式等待新线程完成。

	printf("thread,return,thread id is:%lu,return code is:%d\n",tid,(int)tret);


	//thread 2 exit
	pthread_create(&tid,NULL,thread2,NULL);
	pthread_join(tid,&tret);
	printf("thread exit,thread id is :%lu,return code is :%d\n",tid,(int)tret);

	//thread 3 cancel by other
	pthread_create(&tid,NULL,thread3,NULL);
	sleep(3);
	pthread_cancel(tid);//取消子线程thread3
	pthread_join(tid,&tret);
	printf("thread return,thread id is:%lu,return code is:%d\n",tid,(int)tret);//此时的返回值是常数PTHREAD_CANCELED也就是-1.


	return 0;
}
*/

/*

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//验证子线程的分离


void *thread_run(void *_val)
{
	pthread_t tid = pthread_self();  //获取新线程id.
//	pthread_detach(tid); //子线程中分离。
	printf("%s\n",(char*)_val);
	return NULL;
}


int main()
{
	pthread_t tid;
	int tret = pthread_create(&tid,NULL,thread_run,"thread1 run...");
	if (tret != 0)
	{
		printf("create thread error!,info is:%s\n",strerror(tret));
		return tret;
	}

	//wait
	int ret = 0;
	sleep(1);
	pthread_detach(tid); //在主线程中分离。
	if (0 == pthread_join(tid,NULL)) //不关心退出码，直接置NULL,如果新线程已经分离，此时等待会失败.
	{
		printf("pthread wait success!\n");
	}
	else
	{
		printf("pthread wait failed!\n");
		ret = 1;
	}
	return ret;

}

*/

/*

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


int count = 0;//全局变量。

void* pthread_run(void *arg)
{
	int val = 0;
	int i = 0;

	while (i < 5000)
	{
		//这里会出现问题，就是当两个线程进行操作的时候count的+是非原子的。
		i++;
		val = count;
		printf("pthread:%lu,count:%d\n",pthread_self(),count);
		count = val + 1;
	}

	return NULL;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1,NULL,pthread_run,NULL);
	pthread_create(&tid2,NULL,pthread_run,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	printf("count:%d\n",count);

	return 0;
}

*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>


//加上互斥锁

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//锁的初始化。
int count = 0;

void* pthread_run(void *arg)
{
	int val = 0;
	int i = 0;

	while (i < 5000)
	{
		//在临界区加上互斥锁，这样就可解决线程访问冲突的问题了。

		pthread_mutex_lock(&mutex);//加锁，保证操作的原子性。
		i++;
		val = count;
		printf("pthread:%lu,count:%d\n",pthread_self(),count);
		count = val + 1;
		pthread_mutex_unlock(&mutex);//解锁
	}
	//pthread_mutex_destroy(&mutex);不知道静态锁要不要释放
	return NULL;
}


int main()
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1,NULL,pthread_run,NULL);
	pthread_create(&tid2,NULL,pthread_run,NULL);

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	printf("count = %d\n",count);
	return 0;
}



