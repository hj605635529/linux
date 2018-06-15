/*************************************************************************
	> File Name: select_cgi.cpp
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Wed 19 Jul 2017 11:10:46 AM PDT
 ************************************************************************/

#include"sql.h"

void select_data(char *buf)
{

}

int main()
{
	
	cout << "hello..."<<endl;
	sql obj("root", "", "127.0.0.1", "http", 3306);
	obj.connect();
	obj.select();

	cout << "hello..."<<endl;
	return 0;
}

