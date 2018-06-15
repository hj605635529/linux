#include"comm.h"


int comMsgQueue(int flag)
{
	key_t _k = ftok(PATHNAME,PROJ_ID);
	if (_k < 0)
	{
		perror("ftok");
		return -1;
	}

	int msg_id = msgget(_k, flag); //这个函数返回消息队列的标识符。
	if (msg_id < 0)
	{
		perror("msg");
		return -2;
	}

	return msg_id;

}

int createMsgQueue()
{
	return comMsgQueue(IPC_CREAT|IPC_EXCL|0666);
}

int getMsgQueue()
{
	return comMsgQueue(IPC_CREAT);
}
int sendMsg(int msgid, long type, const char*_info)
{
	struct msgbuf msg;
	msg.mtype = type;
	strcpy(msg.mtext,_info);
	if (msgsnd(msgid,&msg,sizeof(msg.mtext),0) < 0 ); //第二个参数是一个指向msgbuf的指针，最后一个参数为0表示是阻塞式等待。
	{
		perror("msgsnd");
		return -1;
	}
	return 0;
	
}
int recvMsg(int msgid, long type,char out[])//收到的数据存到out中。
{							//type表示要收谁的数据。
	struct msgbuf msg;
	if (msgrcv(msgid,&msg,sizeof(msg.mtext),type,0) < 0)
	{
		perror("msgrcv");
		return -1;
	}
	strcpy(out,msg.mtext);
	return 0;
}



int destroyMsgQueue(int msgid)
{
	if (msgctl(msgid,IPC_RMID,NULL) < 0) //如果只是销毁消息队列，我们不关心第三个参数，直接设置为空。
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
