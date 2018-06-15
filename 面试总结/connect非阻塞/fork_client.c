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
#include<netinet/in.h>
#include<string.h>
#include <sys/select.h>
#include<fcntl.h>
/* According to earlier standards */
#include <sys/time.h>
#include <unistd.h>
#include<errno.h>


static void usage(const char *str)
{
	printf("Usage:%s,[IP],[PORT]\n",str);
}

int main(int argc ,char *argv[])
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("sock");
		return 1;
	}

	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(atoi(argv[2]));
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

	int old_flag;

	old_flag = fcntl(sock, F_GETFL, 0); //得到套接字的属性
	 fcntl(sock, F_SETFL, O_NONBLOCK ); //将连接套接字设置为非阻塞。

	int ret = connect(sock,(struct sockaddr*)& serv_addr,sizeof(serv_addr));
	if(ret != 0)
	{
		if(errno != EINPROGRESS) //connect返回错误。
		{
			printf("connect failed\n");
		}
		//连接正在建立但是尚未完成
		else
		{
			struct timeval tm;  //1.定时
			tm.tv_sec = 10;
			tm.tv_usec = 0;

			fd_set wset;
			FD_ZERO(&wset);
			FD_SET(sock,&wset); 
			printf("selcet start\n");
			int res = select(sock+1, NULL, &wset, NULL, &tm); //加入到select监听集合中
			printf("select end\n");
			if(res <= 0)
			{
				printf("res <= 0\n");
				close(sock);
				return 2;
			}
			
			if(FD_ISSET(sock,&wset)) //当连接建立好了，sock是可写的，当连接发生了错误，sock是可读和可写的。
			{
				printf("test \n");
				int err = -1;
				socklen_t len = sizeof(int);
				
				if(getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len ) < 0) //两种错误处理方式
				{
					printf("errno :%d %s\n",errno, strerror(errno));
					close(sock);
					return 3;
				}

				if(err) //第二种错误处理方式
				{
					printf("connect faile\n");
					errno = err;
					close(sock);
					return 4;
				}

				printf("connetct success\n");
			}

		}

	}

	fcntl(sock, F_SETFL, old_flag); //最后恢复sock的阻塞属性。

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
