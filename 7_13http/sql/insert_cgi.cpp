/*************************************************************************
  > File Name: main.cpp
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: Tue 18 Jul 2017 10:44:31 PM PDT
 ************************************************************************/

#include "sql.h"

using namespace std;


//测试用例，首先测试数据库安装好了没，再测试下插入数据是否成功
/*
int main()
{
	cout << "client vsersion:"<< mysql_get_client_info() <<endl;
	sql obj("root", "127.0.0.1", "","http", 3306); 
			//以root身份去连接数据库，主机号是本地，无密码，数据库是http
	obj.connect();
	obj.insert("LS", "WOMAN", "qinghua", "sleeping&eating");
	cout << "hello..."<<endl;
	return 0;
}
*/


void insert_data(char *buf)
{
	//name='' &sex=' '&scholl=' '&hobby=' '
	char *argv[5];
	char *start = buf;
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
	sql obj("root","127.0.0.1", "", "http", 3306);
	obj.connect();
	obj.insert(argv[0], argv[1], argv[2], argv[3]);
}

int main()
{
	
	char *method = NULL;
	char *arg_string = NULL;
	char *content_len = NULL;
	char buff[1024];
	method = getenv("METHOD");
	if(method == NULL)
	{
		cout <<"hello.."<<endl;
	}	
	if(method && strcasecmp(method, "GET") == 0)
	{
		arg_string = getenv("QUERY_STRING");
		if(!arg_string)
		{
			return 1;
		}
		strcpy(buff, arg_string);
	}
	else if(method && strcasecmp(method, "POST") == 0)
	{
		content_len = getenv("CONTENT_LENGTH");
		if(!content_len)
		{
			return 2;
		}
		int i = 0;
		char c = 0;
		int nums = atoi(content_len);
		for(; i < nums; i++)
		{
			read(0, &c, 1);
			buff[i] = c;
		}
		buff[i] = '\0';
	}
	else
	{
		return 1;
	}
	insert_data(buff);
	return 0;
}
