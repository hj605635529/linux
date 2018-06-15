/*************************************************************************
  > File Name: poll.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: Sun 11 Jun 2017 11:43:19 PM PDT
 ************************************************************************/

#include<stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<poll.h>
#include<string.h>


static void usage(const char *str)
{
	printf("Usage:%s [serv_ip] [serv_port]\n",str);
}

static int startup(const char *ip,int port)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}

	int opt = 1;
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	int ret  = bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret < 0)
	{
		perror("bind");
		exit(2);
	}

	ret = listen(sock,128);
	if(ret < 0)
	{
		perror("listen");
		exit(3);
	}
	return sock;
}

//       poll函数第一个参数类型。
//struct pollfd {
//	int   fd;         /* file descriptor */
//	short events;     /* requested events */
//	short revents;    /* returned events */
//};
//
 //  int poll(struct pollfd *fds, nfds_t nfds, int timeout);


int main(int argc ,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int sock = startup(argv[1],atoi(argv[2]) );

	struct pollfd peerfd[1024]; //当有就绪事件发生的话会写到这个数组里面。

	peerfd[0].fd = sock;  //首先监听连接套接字。监听它的读事件。
	peerfd[0].events = POLLIN;

	int timeout = -1;  //表示阻塞式等待。
	int i = 1;

	for(; i < 1024; ++i)
	{
		peerfd[i].fd = -1;    //表示这个位置么有被占用。
	}

	while(1)
	{				//int poll(struct pollfd *fds, nfds_t nfds, int timeout); //timeout是一个值传递，不用每次都初始化了。
		int ret = 0;
		switch(ret = poll(peerfd,1024,timeout))
		{
			case 0:
				printf("timeout...\n");
				break;
			case -1:
				perror("poll");
				break;
			default:
				{
					int i = 0;
					for(i = 0; i < 1024; ++i)//遍历数组查看有哪些就绪事件发生了。
					{
						if(i == 0 && (peerfd[i].revents & POLLIN)  )//有新的连接请求。
						{
							struct sockaddr_in client;
							socklen_t len = sizeof(client);
							int new_sock = accept(sock,(struct sockaddr*)&client,&len);
							if(new_sock < 0)
							{
								perror("accept");
								continue;
							}
							printf("get a new client\n");
							int j = 1;
							for(; j < 1024; ++j)
							{
								if(peerfd[j].fd < 0)  //找最小的未被使用的位置。
								{
									peerfd[j].fd = new_sock;
									peerfd[j].events = POLLIN;
									break;
								}
							}

							if(j == 1024 )
							{
								printf("too many client...\n");
								close(new_sock);
							}
						} //if
						else if(i != 0)
						{
							if(peerfd[i].revents & POLLIN) //客户端有读事件发生。
							{
								char buf[1024];
								ssize_t s =  read(peerfd[i].fd,buf,sizeof(buf) - 1);
								if(s > 0)
								{
									buf[s] = 0;
									printf("clinet say:%s\n",buf);
									peerfd[i].events = POLLOUT; //读完后监听写事件。
								}
								else if(s <= 0)
								{
									close(peerfd[i].fd);
									peerfd[i].fd = -1;
								}
							}
						//	else if(peerfd[i].revents & POLLOUT)//写事件就绪。写就绪代码错误。
						//	{
								/* 客户端写事件发生 */
								/* 使用浏览器测试，写回到客户端，浏览器会解析字符串，显示 Hellp Epoll! */
						//		const char* msg = "HTTP/1.1 200 OK\r\n\r\n<html><br/><h1>Hello poll!</h1></html>";
						//		write(peerfd[i].fd, msg, strlen(msg));
								
								//写完后关闭套接字。
						//			close(peerfd[i].fd);
						//			peerfd[i].fd = -1;
						//	}

						} //else if

					} //for

				} //default

		} //switch()
	} //while(1)

	return 0;
}
