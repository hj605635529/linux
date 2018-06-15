/*************************************************************************
	> File Name: clie.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Wed 24 May 2017 12:01:48 AM PDT
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
	printf("%s [IP][PORT] \n",str);

}

//  ./clie 127.0.0.1 8000
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		usage(argv[0]);
		exit(1);
	}

	struct sockaddr_in serv_addr;
	int sockfd;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0)
	{
		perror("socket");
		exit(1);
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);


	int ret = 0;
	ret = connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(ret < 0)
	{
		perror("connect");
		exit(2);
	}

	int n = 0;
	char buf[1024] = { 0 };
	while(1)
	{
		printf("client# ");
		fflush(stdout);
		int n = read(0,buf,sizeof(buf)-1);
		buf[n-1] = '\0'; //换行符不读。
		write(sockfd,buf,strlen(buf));

		n = read(sockfd,buf,sizeof(buf)-1);
		buf[n] = 0;
		printf("server echo#：%s\n",buf);
	}

	return 0;
}
