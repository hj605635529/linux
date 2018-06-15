/*************************************************************************
	> File Name: select_client.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 05 Jun 2017 09:41:54 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/time.h>
#include<fcntl.h>
#include<sys/stat.h>

static void Usage(const char *str)
{
	printf("usage: %s [server_ip][server_port]\n",str);
}

int main(int argc, char*argv[] )
{

	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}


	int new_socket = socket(AF_INET,SOCK_STREAM,0);
	if(new_socket < 0)
	{
		perror("socket");
		exit(2);
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi (argv[2]) );
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]); 
	
	int ret = connect(new_socket,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret < 0)
	{
		perror("connect");
		exit(3);
	}

	char buf[BUFSIZ];

	while(1)
	{
		printf("please enter#:");
		fflush(stdout);

		ssize_t s = read(0,buf,sizeof(buf) - 1);
		if(s > 0)
		{
			int outfd = dup(1);  //outfd 指向标志输出（保存标准输出好恢复）。

			buf[s-1] = 0;  //去掉换行符。
		//	write(new_socket,buf,strlen(buf));
			dup2(new_socket, 1);  //1号文件描述符去指向new_socket指向的内容了。
			printf("%s",buf);  //本来是将buf中的东西写入到标准输出中，但是现在1号描述符已经重新定向了，指向套接字的缓冲区，所以现在就是讲buf中的东西写入到套接字缓冲区了。
			fflush(stdout);

			dup2(outfd, 1);  //让1重新指向标准输出。
		}
		else
			break;

//		ssize_t s2 = read(new_socket,buf,sizeof(buf) - 1);
//		buf[s2] = 0;

//		printf("sever echo # %s\n",buf);

	}

	close(new_socket);

	return 0;
}
