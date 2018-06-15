/*************************************************************************
	> File Name: test.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: 2017年04月05日 星期三 00时37分25秒
 ************************************************************************/

#include<stdio.h>
#include<assert.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct Node
{
	struct Node *next;
	int val;
}Node;

void list_init(Node **phead)
{
	assert(phead);

	Node *temp = (Node*)malloc(sizeof(Node));
	temp->next = NULL;
	temp->val = 0;
	*phead = temp;
}

void list_push(Node *phead,int _data)  //头插
{
	assert(phead);

	Node *pM = (Node*)malloc(sizeof(Node));
	if (pM)
	{
		pM->val = _data;
		pM->next = phead->next;
		phead->next = pM;
	}
}

int empty(Node *phead)
{
	return (phead->next == NULL ? 1: 0);
}

void list_print(Node *phead)
{
	assert(phead);

	if (empty(phead))
		return ;

	Node *pCur = phead->next;
	while (pCur)
	{
		printf("%d->",pCur->val);
		pCur = pCur->next;
	}
	printf("%s\n","NULL");
}

void list_pop(Node *phead,int *data)  //头删
{
	assert(phead);
	
	if (empty(phead))
		return ;

	Node *ptemp = phead->next;

	phead->next = ptemp->next;

	*data = ptemp->val;
	free(ptemp);

	ptemp = NULL;
}

void list_destroy(Node *phead)
{
	assert(phead);

	while (!empty(phead))
	{
		int data;
		list_pop(phead,&data);
	}
}
//生产者线程
void* producer(void *arg)
{
	Node *phead = (Node *)arg;
	while (1)
	{
		pthread_mutex_lock(&mutex);  //申请互斥锁
		int data = rand()%100;
		list_push(phead,data);
		pthread_mutex_unlock(&mutex);//释放互斥锁
		printf("prodecer sucess %d\n",data);
		pthread_cond_signal(&cond); //以单播的方式通知拥有条件变量的另外一个线程，告诉消费者，生产者生产好了，可以消费了。
		sleep(1);
	}

	return NULL;
}

//消费者线程
void* consumer(void *arg)
{
	Node *phead = (Node *)arg;
	while (1)
	{
		int data;

		pthread_mutex_lock(&mutex);
		
		if (empty(phead)) //如果没有资源可以消费了，则等待  这里用if可能有问题，应该用while，假设有多个消费者
		{
			pthread_cond_wait(&cond,&mutex); //这个函数调用一定是在拥有互斥锁的前提下.这个函数做三件事，第一：释放互斥锁，二，阻塞等待，三，唤醒的时候重新获得互斥锁。
		}
		list_pop(phead,&data);//有资源就消费
		pthread_mutex_unlock(&mutex);
		printf("consumer sucess %d\n",data);
		sleep(2);
	}
	return NULL;
}

int main()
{
	Node *phead;
	list_init(&phead);

	pthread_t id1;
	pthread_t id2;


	pthread_create(&id1,NULL,producer,(void*)phead);
	pthread_create(&id2,NULL,consumer,(void*)phead);


	pthread_join(id1,NULL);
	pthread_join(id2,NULL);


	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	
	return 0;
}



