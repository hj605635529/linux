#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/time.h>

static void Usage(const char *str)
{
	printf("usage: %s [server_ip][server_port]\n",str);
}

static int startup(const char *ip,int port)
{
	int new_socket = socket(AF_INET,SOCK_STREAM,0);
	if(new_socket < 0)
	{
		perror("socket");
		exit(2);
	}

	int op = 1;
	int ret = setsockopt(new_socket,SOL_SOCKET,SO_REUSEADDR,&op,sizeof(op));
	if(ret < 0)
	{
		perror("setsockopt");
		exit(3);
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	serv_addr.sin_addr.s_addr = inet_addr(ip);

	ret = bind(new_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret < 0)
	{
		perror("bind");
		exit(4);
	}
	ret = listen(new_socket,128);
	if(ret < 0)
	{
		perror("listen");
		exit(5);
	}

	return new_socket;

}

int array_fds[1024];  //定义一个全局数组。这个全局变量存放的是文件描述符。
int max_fd;   //最大的文件描述符。

int main(int argc ,char *argv[])
{

	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}

	int i = 0;
	for(; i < 1024; ++i)
		array_fds[i] = -1;   //将数组中每一个元素都置为-1.

	int listen_sock = startup(argv[1],atoi(argv[2]) );

	array_fds[0] = listen_sock;  //将监听套件字放在数组中0号位置。
	fd_set reads;  //创建只读集合。

	struct timeval timeout; 

	while(1) //服务器一直处于服务状态。
	{         //  int select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);后面四个参数都是输入输出参数。

		FD_ZERO(&reads);  //因为select是输入输出参数，当select返回时，已经改变了read这个集合了，下次还需要监听read这个集合中的可读事件的话就需要重新赋值。

		max_fd = -1;  //每次这个得重新初始化

		timeout.tv_sec = 10;  //定时10秒,这个参数也是输入输出参数
		timeout.tv_usec = 0;

		for(i = 0; i < 1024; ++i)//遍历第三方数组
		{
			if(array_fds[i] >= 0)
			{
				FD_SET(array_fds[i], &reads); //将监听套接字加入到可读事件中。
				if(array_fds[i] > max_fd)
					max_fd = array_fds[i];
			}
		}

		//准备工作做好后，开始真正的监听了。
		printf("*****************select start**********************************\n");
		int j  = 0;
		switch(select(max_fd+1 ,&reads,NULL,NULL,&timeout))
		{

			case 0:
				printf("time out....\n");
				break;
			case -1:
				perror("select");
				exit(6);
			default: //有可读事件发生，但是不知道是那一个可读事件，需要遍历数组，查看数组中存放的描述符那一个可读了。

				for(; j < 1024; ++j)
				{
					if(array_fds[j] < 0) //-1表示这个文件描述符没有可读事件发生。
						continue;

					char buf[BUFSIZ]; //接收数据缓冲区。

					if(j== 0 && FD_ISSET(array_fds[0],&reads)) //监听套接字有可读事件发生，表示有客户连接了。
					{
						struct sockaddr_in clie_addr;
						socklen_t  len = sizeof(clie_addr);
						int connect_fd = accept(array_fds[0],(struct sockaddr*)&(clie_addr),&len);
						if(connect_fd < 0)
						{
							perror("accept");
							continue;  //这次连接失败，让它下次连接。
						}
						printf("get a new client :(%s:%d)\n",inet_ntoa(clie_addr.sin_addr),ntohs(clie_addr.sin_port));
						//连接套接字后继续监听，看这个套接字是不是有数据发送。
						int k = 0;
						for(; k < 1024; ++k)
						{
							if(array_fds[k] == -1)
							{
								array_fds[k] = connect_fd;
								break;
							}
						}

					}  //if
					else if(j != 0 && FD_ISSET(array_fds[j],&reads))
					{
						printf("======================read start j = %d  ==========\n",j);
						ssize_t  s = read(array_fds[j],buf,sizeof(buf) - 1);
						if(s < 0)
						{
							perror("read");
							close(array_fds[j]);
							array_fds[j] = -1;  //数组重新利用
							break;
						}
						else if(s == 0)
						{
							printf("clinet quit\n");
							close(array_fds[j]);
							array_fds[j] = -1;  //数组重新利用
							break;
						}
						else
						{
							buf[s]  = 0;
							printf("clinet say:%s\n",buf);
						}	
					}
					
				}//for结束
		} //switch结束
	} //while(1)死循环

	return 0;

}
