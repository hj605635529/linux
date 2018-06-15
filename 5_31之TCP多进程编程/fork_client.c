/*************************************************************************
	> File Name: fork_client.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 30 May 2017 02:30:41 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<string.h>
#include<netinet/in.h>
#include<string.h>


static void usage(const char *str)
{
	printf("Usage:%s,[IP],[PORT]\n",str);
}

int main(int argc ,char *argv[])
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock < 0)
	{
		perror("sock");
		return 1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sock,(struct sockaddr*)& serv_addr,sizeof(serv_addr)) < 0)
	{
		perror("connect");
		return 3;
	}

	char buf[BUFSIZ];
	while(1)
	{

		printf("client say# ");
		fflush(stdout);

		ssize_t s = read(0,buf,sizeof(buf) - 1);
		if(s > 0)
		{
			buf[s - 1] = 0;
			write(sock,buf,strlen(buf));
			ssize_t s2 = read(sock,buf,sizeof(buf) -1 );
			if(s2 > 0)
			{
				buf[s2] = 0;
				printf("server echo # %s\n",buf);

			}
			
		}

	}

	return 0;
}
