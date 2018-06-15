/*************************************************************************
  > File Name: epoll.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: 2017年06月11日 星期日 08时30分58秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/epoll.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

static void Usage(const char *str)
{
	printf("Usage:%s [serv_ip][serv_port]\n",str);
}

typedef struct fd_buf  //struct epoll_event ev  ev.data.ptr 指向这个结构体。
{
	int fd;
	char buf[10240]; //每一个套接字都有自己的缓冲区。
}fd_buf_t,*fd_buf_p;


static void* alloc_fd_buf(int fd)
{
	fd_buf_p tmp = (fd_buf_p)malloc(sizeof(fd_buf_t));
	if(tmp == NULL)
	{
		perror("malloc");
		return NULL;
	}
	tmp->fd = fd;
	return tmp;
}


static int startup(const char *ip,int port)
{
	int listen_socket = socket(AF_INET,SOCK_STREAM,0);
	if(listen_socket < 0)
	{
		perror("socket");
		exit(1);
	}
	int op = 1;
	setsockopt(listen_socket,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op)); //端口复用

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(ip);
	serv_addr.sin_port = htons(port);

	int ret = bind(listen_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr)  );
	if(ret < 0)
	{
		perror("bind");
		exit(2);
	}

	ret = listen(listen_socket,128);
	if(ret < 0)
	{
		perror("listen");
		exit(3);
	}
	return listen_socket;
}

int main(int argc,char *argv[])
{

	if(argc != 3)
	{
		Usage(argv[0]);
		return 1;
	}

	int listen_sock = startup(argv[1],atoi(argv[2]));

	int epollfd = epoll_create(256);//建议操作系统创建一个有256个节点的红黑树。
	if(epollfd < 0)
	{
		perror("epoll_create");
		close(listen_sock);
		return 5;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN; //监听listen_socket的可读事件。
	ev.data.ptr = alloc_fd_buf(listen_sock); //每一个fd都分配自己的空间。

	int ret = epoll_ctl(epollfd,EPOLL_CTL_ADD,listen_sock,&ev);//将listen_sock加入到红黑树中，并且监听它的可读事件。


	int nums = 0;
	struct epoll_event evs[64];
	int timeout = -1;

	while(1)
	{
		switch(  (nums = epoll_wait(epollfd,evs,64,timeout) )  )  //红黑树中就绪的节点放入循环队列中，把队列中的事件放入epoll_event数组中。它不会修改红黑树的节点和定时器，所以不需要每次都重新初始化。
		{
			case -1:
				perror("epoll_wait");
				break;
			case 0:
				printf("timeout....!\n");
				break;
			default:
				{
					int i = 0;
					for(; i < nums; ++i) //遍历数组，这个数组的元素都是就绪的。
					{
						fd_buf_p fp =  (fd_buf_p)evs[i].data.ptr; //ptr指向一个结构，这个结构中包含了一个文件描述符和一块空间。

						if(fp->fd == listen_sock &&(evs[i].events & EPOLLIN))
						{
							struct sockaddr_in clie_addr;
							socklen_t len = sizeof(clie_addr);

							int new_sock = accept(listen_sock, (struct sockaddr*)&clie_addr,&len);
							if(new_sock < 0)
							{
								perror("accept");
								continue;
							}
							printf("get a new client\n");

							struct epoll_event temp;
							temp.events = EPOLLIN;
							temp.data.ptr = alloc_fd_buf(new_sock); //将连接套接字加入到红黑树中
							epoll_ctl(epollfd,EPOLL_CTL_ADD,new_sock,&temp);
						}//if
						else if(fp->fd != listen_sock)
						{
							if(evs[i].events & EPOLLIN) //可读事件。
							{
								ssize_t s = read(fp->fd,fp->buf,sizeof(fp->buf)-1); //
								if(s > 0)
								{
									fp->buf[s] = 0; //从标准输入中读取s需要减一，其他情况下不需要。
									printf("client say:%s\n",fp->buf);
									//读完后让这个套接字成为写状态。
									struct epoll_event temp;
									temp.events = EPOLLOUT;
									temp.data.ptr = fp;

									epoll_ctl(epollfd,EPOLL_CTL_MOD,fp->fd,&temp);
								}
								else if (s <= 0)
								{
									close(fp->fd);
									epoll_ctl(epollfd,EPOLL_CTL_DEL,fp->fd,NULL);
									free(fp);
								}

							} //if 可读事件。
							else if(evs[i].events & EPOLLOUT) //可写事件。
							{
								const char *msg = "HTTP/1.0 200 OK\r\n\r\n<html><h1> hello epoll!</h1></html>";
								write(fp->fd,msg, strlen(msg));

								close(fp->fd);
								epoll_ctl(epollfd,EPOLL_CTL_DEL,fp->fd,NULL);
								free(fp);
							}
						} 
					} //for finish;
					break;
				} //default finish
		}
	}

	return 0;
}




