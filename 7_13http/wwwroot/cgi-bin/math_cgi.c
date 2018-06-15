/*************************************************************************
	> File Name: math.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 09:11:50 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void math_cal(char buff[])
{
	// 参数的形式：采用&连接     f=8&rsv_bp=1&rsv_idx=1
	char *argv[3];
	char *start = buff;
	int i = 0;

	while(*start)
	{
		if(*start == '=')
		{
			start++;
			argv[i++] = start;
			continue;
		}
		if(*start == '&')
		{
			*start = '\0';
		}
		start++;
	}
	argv[i] = NULL;

	int data1 = atoi(argv[0]);
	int data2 = atoi(argv[1]);

	printf("<html>\n");
	printf("<body>");

	printf("<h1>");
	printf("%d + %d = %d\n",data1, data2, data1+data2);
	printf("</h1");
	
	printf("<h1>");
	printf("%d - %d = %d\n",data1, data2, data1-data2);
	printf("</h1");

	printf("<h1>");
	printf("%d * %d = %d\n",data1, data2, data1*data2);
	printf("</h1");

	printf("<h1>");
	printf("%d / %d = %d\n",data1, data2, data2==0?0:data1/data2);
	printf("</h1");

	printf("<h1>");
	printf("%d %% %d = %d\n",data1, data2, data2==0?0:data1%data2);
	printf("</h1");

	printf("</body>");
	printf("</html>\n");
}

int main()
{
	char *method = NULL;
	char *arg_string = NULL;
	char *content_len = NULL;
	char buff[1024]; //buff用来存放参数
	method = getenv("METHOD"); //拿到METHOD环境变量所指向的值
	if(method && strcasecmp(method, "GET") == 0)
	{
		arg_string = getenv("QUERY_STRING");
		if(!arg_string)
		{
			printf("get method GET arg error!\n");
			return 1;
		}
		strcpy(buff, arg_string);
	}
	else if(method && strcasecmp(method, "POST") ==0)
	{
		content_len = getenv("CONTNT_LENGTH");
		if(!content_len)
		{
			printf("get method POST content_length error!\n");
			return 2;
		}
		int i = 0;
		char c = 0;
		int nums = atoi(content_len);
		for(; i < nums; ++i)
		{
			read(0, &c, 1); //从管道里读数据
			buff[i] = c;
		}
		buff[i] = '\0';
	}
	else
	{
		printf("get method error!\n");
		return 1;
	}

	math_cal(buff);
	return 0;
}
