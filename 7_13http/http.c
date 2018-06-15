#include"http.h"

int startup(const char *ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		return -2;
	}

	int opt = 1; //端口复用
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(port);
	local.sin_addr.s_addr = inet_addr(ip);

	if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0)
	{
		perror("bind");
		return -3;
	}
	if(listen(sock, 10) < 0)
	{
		perror("listen");
		return -4;
	}

	return sock;
}



static int get_line(int fd, char *buf, int len ) //返回一行中的字符个数
{
	//每次一个字符一个字符的读取
	char c = 0;
	int i = 0;

	while(c != '\n' && i < len-1) //留下一个位置放\0.
	{
		ssize_t s =recv(fd, &c, 1, 0);
		if(s > 0)
		{
			if (c == '\r')
			{
				recv(fd, &c, 1, MSG_PEEK); //窥探下后面的字符
				if(c == '\n')
				{
					recv(fd, &c, 1, 0); 
				}
				else
				{
					c = '\n'; //将\r这种形式的换行换成\n这种形式
				}
			}
			buf[i] = c;
			i++;
		}
	}
	buf[i] = '\0'; //一行读完，别忘了加上\0.
	return i;
}


void print_log(const char *msg, int level)
{
	const char *level_msg[] = {"NOTICE",
								"WARNING",
								"FATAL",
								};  //错误的等级。
	printf("[%s][%s]\n",msg, level_msg[level]);
}

//404的错误码
static void show_404(int fd)
{
	const char * echo_header = "HTTP/1.0 404 Not Found\r\n";
	send(fd, echo_header, strlen(echo_header), 0);
	const char *type = "Content-Type:text/html;charset=ISO-8859-1\r\n";
	send(fd, type, strlen(type), 0);
	const char *blank_line = "\r\n"; //空行
	send(fd, blank_line, strlen(blank_line), 0);

	const char *msg = "<html><h1>Page Not Found!</h1></html>\r\n";
	send(fd, msg, strlen(msg), 0);
}


int  echo_error(int fd, int error_num)
{
	switch(error_num)
	{
		case 400:
			break;
		case 401:
			break;
		case 403:
			break;
		case 404:
			show_404(fd);
			break;
		case 501:
			break;
		case  500:
			break;
		case 503:
			break;
		default:
			break;
	}

	return 0;	
}

int echo_www(int fd, const char *path, int size) //如果浏览器请求一个目录，则给它返回当前目录下的网页。
{
	int new_fd = open(path, O_RDONLY); //打开这个主页
	if(new_fd < 0)
	{
		print_log("open file error!",FATAL);
		return 404;
	}

	const char *echo_line = "HTTP/1.0 200 OK\r\n"; //响应行
	send(fd, echo_line, strlen(echo_line), 0);

	//忽略报头
	
	const char *blank_line = "\r\n";  //空白行
	send(fd, blank_line, strlen(blank_line), 0);

	//正文  如果我们用read 和write ，需要先将硬盘的文件写到用户空间，再用户空间写到内核空间，效率不高。
	//sendfile  new_fd中文件内容在内核空间拷贝到fd所指向的文件.效率高。
	if(sendfile(fd, new_fd, NULL, size) < 0) //
	{
		print_log("send file error!",FATAL);
		return  2000;
	}
	close(new_fd);
}

//丢弃请求行，报头，空行，只留下正文
void drop_header(int fd)
{
	char buff[SIZE];
	int ret = -1;
	do
	{
		ret = get_line( fd, buff, sizeof(buff) );
	}while(ret > 0 && strcmp(buff, "\n"));
}


int exe_cgi(int fd, const char * method, const char *path, const char *query_string)
{
	int content_len = -1;
	char METHOD[SIZE/10];
	char QUERY_STRING[SIZE];//存放的是参数。
	char CONTENT_LENGTH[SIZE]; //存放的是正文的长度。

	//第一步：先判断这个请求方法是GET还是POST，GET参数在url中，POST参数在正文中.
	if(strcasecmp(method, "GET") == 0) //当GET方法时，参数我们已经保存在path中了，已经拿到我们要的东西了，丢弃头部和请求行.
	{
		drop_header(fd);
	}
	else  //POST方法
	{
		char buff[SIZE];
		int ret =-1;
		do
		{
			ret = get_line(fd, buff, sizeof(buff));//报文头都是以行为单位的，其中有一个Content-Length字段描述正文的长度。 
			if(strncasecmp(buff, "Content-Length:", 16) == 0) //strncasecmp  n个字符不分大小的比较。
			{
				content_len = atoi(&buff[16]);
			}
		}while(ret > 0 && strcmp(buff,"\n")); //这里把正文长度读出来了，但是依然跳过请求行，报文头，空行。
		
		if(content_len == -1) //POST 方法一定是CGI，一定会有参数的，
		{
			echo_error(fd, 401);
			return -1;
		}
	}

	printf("cgi:path:%s\n",path);
	//第二步：父进程从网络中拿到需要加工的数据，子进程进行加工，加工完成后将数据写回给父进程，父进程写回给网络。需要创建两个管道，才能双向通信。
	int input[2];
	int output[2];
	if(pipe(input) < 0)
	{
		echo_error(fd, 401);
		return -2;
	}
	if(pipe(output) < 0)
	{
		echo_error(fd, 401);
		return -3;
	}

	const char *echo_line = "HTTP/1.0 200 OK\r\n"; //响应行
	send(fd, echo_line, strlen(echo_line), 0);
	const char *type = "Content-Type:text/html;charset=ISO-8859-1\r\n"; //格式
	send(fd, type, strlen(type), 0);

	//忽略响应报文头

	const char*blank_line = "\r\n"; //响应空白行.
	send(fd, blank_line, strlen(blank_line), 0);


	pid_t  id = fork();
	if(id < 0)
	{
		echo_error(fd, 501);
		return -2;
	}
	else if(id == 0) //child
	{
		close(input[1]);//子进程通过管道读要加工的数据。
		close(output[0]);//子进程将加工好的数据通过管道写回给父进程。

		sprintf(METHOD, "METHOD=%s", method);
		putenv(METHOD); //将METHOD导成环境变量

		if(strcasecmp(method, "GET") == 0)
		{
			sprintf(QUERY_STRING,"QUERY_STRING=%s",query_string);
			putenv(QUERY_STRING); //参数导成环境变量
		}
		else //post方法
		{
			sprintf(CONTENT_LENGTH, "CONTENT_LENTH=%d", content_len);
			putenv(CONTENT_LENGTH);
		}

		dup2(input[0], 0); //重定向，从标准输入中读也就是从input[0]中读
		dup2(output[1], 1);//写到标准输出中，也就是写入到input[1]中。
		execl(path, path, NULL); //带路径执行path,
		exit(1);
	}
	else //父进程
	{
		close(input[0]);
		close(output[1]);
		int i = 0;
		char c = '\0';
		for(; i < content_len; ++i) //将正文中的数据写给子进程。
		{
			recv(fd, &c, 1, 0);
			write(input[1], &c, 1);
		}

		while(1)
		{
			ssize_t s = read(output[0], &c, 1); //子进程将加工好的数据写回给父进程。
			if(s > 0)
			{
				send(fd, &c, 1, 0); //发送给浏览器。
			}
			else
			{
				break;
			}
		}

		waitpid(id, NULL, 0);
		close(input[1]); //父进程记得要关闭文件描述符，子进程退出自动关闭，父进程直到整个程序结束，才会关闭，浪费资源。
		close(output[0]);
	}
}

//新线程执行函数
void *handler_request(void *arg)
{
	int fd = (int)arg;
	int errno_num = 200;
	int cgi = 0;
	char *query_string = NULL; //这个指针指向参数。
#ifdef _DEBUG_
	printf("###############################################\n");
	char buff[SIZE];
	int ret = -1;
	do
	{
		ret = get_line(fd, buff, sizeof(buff));
		printf("%s",buff);
	}while(ret > 0 && strcmp(buff, "\n"));
	printf("###############################################\n");

#else
	//1 method, 2 url ->GET POST /url-exist->pri
	
	char method[SIZE/10];
	char url[SIZE];
	char path[SIZE];
	char buff[SIZE];

	int i,j;
	//解析请求行，将method,url,解析出来.
	if(get_line(fd, buff, sizeof(buff)) <= 0)
	{
		print_log("get request line error", FATAL);
		errno_num = 501;
		goto end;
	}

	printf("****************test**************************\n");
	printf("buff = %s\n",buff);
	printf("****************test**************************\n");
	i = 0, j = 0;
	//解析method
	while( i < sizeof(method)-1 && j < sizeof(buff) && !isspace(buff[j]))
	{
		method[i] = buff[j];
		i++;
		j++;
	}
	method[i] = 0;

	//跳过空白字符 
	while( isspace(buff[j]) && j < sizeof(buff)   )
	{
		j++;
	}

	//解析url
	i = 0;
	while(i < sizeof(url)-1  && j < sizeof(buff) && !isspace(buff[j])  )
	{
		url[i] = buff[j];
		i++;
		j++;
	}
	url[i] = 0;

	printf("method:%s,url:%s\n",method, url);

	if(strcasecmp(method, "GET") && strcasecmp(method,"POST") ) //如果不是POST方法也不是GET方法
	{
		print_log("method is not ok!",FATAL);
		errno_num = 501;
		goto end;
	}

	if(strcasecmp(method, "POST") == 0) //POST方法肯定是cgi。
	{
		cgi = 1;
	}

	//GET方法需要解析url才能判断是不是cgi 
	query_string = url;
	while(*query_string != 0)
	{
		if(*query_string == '?') //url？后面的都是参数,说明这是cgi
		{
			cgi = 1;
			*query_string = '\0';
			query_string++;
			break;
		}
		query_string++;
	} //while循环结束，query_string指向参数。

	printf("*****************test2******************************\n");
	printf("query_stirng:%s\n",query_string);
	printf("***************test2********************************\n");

	sprintf(path, "wwwroot%s", url); //url解析成路径+参数,   路径要拼接到wwwroot这个根目录后面
	if(path[strlen(path)-1 ] == '/') //路径是/结尾，说明请求的是一个目录，/a/b/这种形式 返回这个目录下的首页。
	{
		strcat(path, "index.html");
	}

	printf("path:%s\n",path);

	struct stat st;
	if(stat (path,&st) < 0) //参看这个路径是否存在，。
	{
		print_log("path not found!", FATAL);
		errno_num = 404;
		goto end;
	}
	else
	{
		if(S_ISDIR(st.st_mode))//请求的还是一个目录/a/b这种形式
		{
			strcat(path,"/index.html");
		}
		else //请求的不是目录
		{
			if((st.st_mode & S_IXUSR) || (st.st_mode&S_IXGRP) ||(st.st_mode&S_IXOTH) ) //有可执行权限，所以要计算，肯定是cgi 。
			{
				cgi = 1;
			}
		}
		//path ->cgi
		if(cgi) //请求的是cgi，则执行cgi
		{
			exe_cgi(fd, method, path, query_string);
		}
		else  //请求的是正常的网页，给浏览器一个网页.
		{
			drop_header(fd);
			printf("*********test3**********\n");
			errno_num = echo_www(fd, path, st.st_size); //显示网页
		}

	}

end:
	echo_error(fd, errno_num);
	close(fd);

#endif
}





