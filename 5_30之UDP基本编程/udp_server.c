/*************************************************************************
	> File Name: udp_server.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Mon 29 May 2017 11:59:37 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
//#include<netinet/in.h>
#include<string.h>

static void usage(const char * str)
{
	printf("Usage:%s [IP] [PORT]\n",str);
}


//  ./server 127.0.0.1 8080
int main(int argc,char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}

	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock < 0)
	{
		perror("sock");
		return 2;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons( atoi(argv[2]) );
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if( (bind(sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) ) < 0  )
	{
		perror("bind");
		return 3;
	}


	char buf[BUFSIZ]  ;
	struct sockaddr_in clie_addr;


	while(1)
	{
		socklen_t len = sizeof(clie_addr);
		ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&clie_addr,&len );//最后一个参数是输入输出参数，
		if(s > 0)
		{
			buf[s] = 0;  //最后加上一个\0
			printf("%s:%d say # %s\n",inet_ntoa(clie_addr.sin_addr),ntohs(clie_addr.sin_port),buf);
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&clie_addr,sizeof(clie_addr));
		}
	}

	close(sock);


	return 0;
}
