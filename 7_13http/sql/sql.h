/*************************************************************************
	> File Name: sql.h
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 09:35:14 AM PDT
 ************************************************************************/

#ifndef  _SQL_H_
#define  _SQL_H_

#include<iostream>
using namespace std;
#include <string>
#include <string.h>
#include <stdlib.h>
#include "mysql.h"

class sql
{
	public:
		sql(const string & _user, const string & _ip, const string &_passwd, const string &_db, const int &_port);
		int connect();
		int insert(const string &name, const string &sex, const string&school, const string &hobby);
		int select();
		~sql();

	private:
		MYSQL *conn;
		string user;
		string ip;
		string passwd;
		string db;
		int port;
};



#endif
