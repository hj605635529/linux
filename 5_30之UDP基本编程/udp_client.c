/*************************************************************************
	> File Name: udp_client.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 30 May 2017 01:04:00 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
//#include<netinet/in.h>
#include<string.h>


static void usage(const char *str)
{
	printf("Usage:%s [IP] [PORT]\n",str);
}

int main(int argc ,char* argv[])
{

	if(argc != 3)
	{
		usage(argv[0]);
		return 1;
	}


	int sock = socket(AF_INET,SOCK_DGRAM,0); //udp使用报文  SOCK_DGRAM
	if(sock < 0)
	{
		perror("sock");
		return 2;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);


	char buf[BUFSIZ] = { 0 };
	socklen_t len = sizeof(serv_addr);

	while(1)
	{
		printf("Please Enter# ");
		fflush(stdout);

		ssize_t s =  read(0,buf,sizeof(buf)-1);
		if(s > 0)
		{
			buf[s - 1] = 0;  //去掉换行符。
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
			ssize_t s2 = recvfrom(sock,buf,sizeof(buf)-1,0,NULL,NULL); //收到的肯定是服务器的，这里就不需要表示出来了。
			buf[s2] = 0;
			printf("server echo# %s\n",buf);

		}
	}

	close(sock);
	return 0;
}
