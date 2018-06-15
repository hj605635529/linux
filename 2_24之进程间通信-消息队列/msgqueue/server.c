#include"comm.h"

//server 先收后发

int main()
{

	int msgid = createMsgQueue();
	printf("msgid:%d\n",msgid);

	char buf[SIZE];
	while (1)
	{
		recvMsg(msgid,CLIENT_TYPE,buf);
		printf("client# %s\n",buf);
		printf("please Enter$ ");
		fflush(stdout);
		ssize_t s = read(0,buf,sizeof(buf)-1);
		if (s > 0)
		{
			buf[s-1] = '\0'; //去除换行符
			sendMsg(msgid,SERVER_TYPE,buf);
		}
	}


	destroyMsgQueue(msgid);
	return 0;
}
