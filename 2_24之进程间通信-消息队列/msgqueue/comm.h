#ifndef _COMM_H_
#define _COMM_H_

#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>

#define PATHNAME "."
#define PROJ_ID 0x6666



#define SIZE 128

#define SERVER_TYPE 1
#define CLIENT_TYPE 2

struct msgbuf
{
	long mtype;
	char mtext[SIZE];
};

int createMsgQueue();
int getMsgQueue();
int sendMsg(int msgid, long type,const char*_info);//type表示谁要发送数据
int recvMsg(int msgid,long type,char out[]); //接收一个消息队列。type表示接收谁的数据。
int destroyMsgQueue(int msgid);

#endif
