/*************************************************************************
  > File Name: pthread_server.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: 2017年06月01日 星期四 08时07分50秒
 ************************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

static void usage(const char *str)
{
	printf("Usage:%s [IP][PORT]\n",str);
}


static int startup(const char *ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	int op = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op)); //端口复用  

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(ip);


	if(bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("bind");
		exit(3);
	}

	if(listen(sock,20) < 0)
	{
		perror("listen");
		exit(2);
	}

	return sock;
}

void* new_pthread(void *arg)
{
	int sock = (int )arg;
	char buf[BUFSIZ];
//	const char* msg = "HTTP/1.1 200 OK\r\n\r\n<html><h1> huang jia </h1></html>\r\n";
	while(1)
	{
		ssize_t s = read(sock,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s] = 0;
			printf("client say:%s\n",buf);
			write(sock,buf,strlen(buf));
		//	write(sock,msg,strlen(msg));
		}
		else if(s == 0)
		{
			printf("client quit !\n");
			break;
		}
		else
		{
			break;
		}
		
	}
	pthread_exit(NULL);
}

int main(int argc,char *argv[])
{

	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}


	int listen_sock = startup(argv[1],atoi(argv[2]));

	int cfd;
	struct sockaddr_in clie_addr;
	while(1)
	{

		socklen_t len = sizeof(clie_addr);
		cfd = accept(listen_sock, (struct sockaddr*)&clie_addr,&len);
		if(cfd < 0)
		{
			perror("accept");
			return 2;
		}
		printf("client ip:%s,port:%d\n",inet_ntoa(clie_addr.sin_addr),ntohs(clie_addr.sin_port)   );

		pthread_t tid;
		pthread_create(&tid,NULL,new_pthread,(void*)cfd);
		pthread_detach(tid);
	}

	return 0;
}
