/*************************************************************************
	> File Name: serv.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 23 May 2017 11:15:35 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<strings.h>
#include<netinet/in.h>
#include<string.h>



void usage(const char *str)
{
	printf("%s [IP][PORT]\n",str);
}

//./serv 127.0.0.1 8000
int main(int argc ,char *argv[])
{

	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	struct sockaddr_in serv_addr,clie_addr;
	int listenfd,connectfd;
	int ret ;
	socklen_t clie_addr_len;

	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd < 0)
	{
		perror("socket");
		exit(2);
	}
	bzero(&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( atoi( argv[2] ) );
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	ret = bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret < 0)
	{
		perror("bind");
		exit(3);
	}
	
	ret = listen(listenfd,20);
	if(ret < 0)
	{
		perror("listen");
		exit(4);
	}

	while(1)      //服务器一直处于工作状态，但是一次只能针对一个客户服务。
	{
		clie_addr_len = sizeof(clie_addr);
		connectfd = accept(listenfd,(struct sockaddr*)&clie_addr,&clie_addr_len);
		if(connectfd < 0)
		{
			perror("accept");
			exit(5);
		}
	
		printf("clie ip %s,clie port %d\n",inet_ntoa(clie_addr.sin_addr),ntohs(clie_addr.sin_port));

		int n = 0;
		char buf[1024] = { 0 } ;
		while(1)
		{
			n = read(connectfd,buf,sizeof(buf)-1);  //最多读sizeof(buf)-1,留下一个空间放\0	
			if(n ==0 )
			{
			 	printf("clie quit!\n");
				break;
			}	
			else if(n < 0)
			{
				break;
			}	
			else
			{
				buf[n] = 0;
				printf("client say:%s\n",buf);
				write(connectfd,buf,strlen(buf));
			}
		}
	}

	close(listenfd);
	close(connectfd);

	return 0;
}
