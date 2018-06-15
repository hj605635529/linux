/*************************************************************************
  > File Name: pthread_client.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: 2017年06月01日 星期四 08时33分02秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{

	char buf[BUFSIZ];
	struct sockaddr_in serv_addr;

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		return 1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("connect");
		return 2;
	}

	while(1)
	{

		printf("clinet say# ");
		fflush(stdout);

		ssize_t s = read(0,buf,sizeof(buf)-1);
		if(s  > 0)
		{
			buf[s-1] = 0;  //去掉换行符
			write(sock,buf,strlen(buf));


			ssize_t s2 = read(sock,buf,sizeof(buf)-1);
			if(s2 > 0)
			{
				buf[s2] = 0;
				printf("server echo #: %s\n",buf);
			}
		}

	}

	return 0;
}
