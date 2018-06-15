/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: 2017年04月11日 星期二 08时14分34秒
 ************************************************************************/

#include<stdio.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

//二个规则，（1）消费者一定要等到生产才能消费，（2）生产者如果生产的快的话，不能套消费者一个圈

#define SIZE 64

sem_t blanks; //二个信号量
sem_t datas;
int buf[SIZE]; //用数组模拟一个环形队列。


void *productor(void *arg)
{
	int i = 0; //i = 0表示生产的起始位置。
		while (1)
		{
			sem_wait (&blanks);//生产者在生产之前要有格子资源。
			int data = rand()%1234;
			buf[i] = data;
			printf("productor done...data:%d\n",data);
			i++;
			i%=SIZE;//i++总有超过数组的长度的时候，为了模拟环形队列，所以求模。
			sleep(1); //生产的慢点
			sem_post(&datas);//生产者生产完了，数据资源就多了一个。
		}
		return NULL;
}
	
void *consummer(void *arg)
{
	int i = 0;
	while (1)
	{																			
		sem_wait(&datas); //消费者在消费之前要有消费资源。
		int data = buf[i];
		printf("consummer done...data:%d\n",data);
		i++;
		i%= SIZE;
		sem_post(&blanks);//消费者消费完了格子资源就多了一个。
	}
	return NULL;
}

	
int main()
{
	sem_init(&blanks,0,SIZE);
	sem_init(&datas,0,0);   //信号量的初始化要在多线程之前

	pthread_t id1,id2;
	pthread_create(&id1,NULL,productor,NULL);	
	pthread_create(&id2,NULL,consummer,NULL);

	pthread_join(id1,NULL);
	pthread_join(id2,NULL);


	sem_destroy(&blanks);
	sem_destroy(&datas);

	return 0;																					
}
