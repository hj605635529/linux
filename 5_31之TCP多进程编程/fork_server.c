/*************************************************************************
  > File Name: fork_server.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: Tue 30 May 2017 02:00:04 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<stdlib.h>

static int startup(const char *_ip,int _port)
{

	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(2);
	}
	int on = 1;
	int ret = setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret < 0)
	{

		perror("setsockopt");
		exit(5);
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(_port);
	serv_addr.sin_addr.s_addr = inet_addr(_ip);

	if(bind (sock,(struct sockaddr*)& serv_addr,sizeof(serv_addr) )  < 0     )
	{
		perror("bind");
		exit(3);
	}
	if(listen(sock,10) < 0)
	{
		perror("listen");
		exit(4);
	}

	return sock;
}

static void usage(const char *str)
{
	printf("Usage:%s [IP] [PORT]\n",str);
}

int main(int argc,char *argv[])
{

	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));

	struct sockaddr_in clie_addr;

	while(1)
	{
		socklen_t len = sizeof(clie_addr);
		int sock = accept(listen_sock ,(struct sockaddr*)&clie_addr,&len );
		if(sock > 0)
		{
			pid_t id = fork();

			if(id == 0) //child
			{
				close(listen_sock); //子进程关闭监听套接字。

				if(fork() > 0)//子进程退出，让孙子进程办事，孙子进程成为孤儿进程，被1号进程回收。
				exit(0); 

				char buf[BUFSIZ];

				while(1)
				{
					ssize_t s = read(sock,buf,sizeof(buf)-1);
					if(s > 0)
					{
						buf[s] = 0;
						printf("client say#:%s\n",buf);
						write(sock,buf,strlen(buf));
					}
					else if(s == 0)
					{
						printf("client quit!\n");
						close(sock);
						return 1;
					}
					else
					{
						close(sock);
						return 2;
					}
				}
			}
			else//father 
			{
				close(sock); //父进程关闭已连接套接字，留下监听套接字。
			//	if(fork() > 0)
			//		exit(0); //父进程退出，留下两个子进程（孤儿进程，1号进程回收资源，不会浪费资源），一个子进程负责监听，一个负责数据传输。
			}

		}
		else
		{
			perror("accept");
		}
	}

	close(listen_sock);

	return 0;
}
