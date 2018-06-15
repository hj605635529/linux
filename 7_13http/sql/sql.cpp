/*************************************************************************
	> File Name: sql.cpp
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 09:40:26 AM PDT
 ************************************************************************/

#include<iostream>
using namespace std;
#include "sql.h"

sql::sql(const string &_user, const string &_ip, const string &_passwd, const string &_db, const int &_port):
																	user(_user),ip(_ip),passwd(_passwd),db(_db),port(_port)
{
	conn = mysql_init(NULL); //得到mysql的一个句柄
}

int sql::connect()
{
	if(mysql_real_connect(conn, ip.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, NULL, 0))
	{
		cout << "connect success!"<<endl;
		return 0;
	}
	else
	{
		return -1;
	}
}

int sql::insert(const string &name, const string &sex, const string& school, const string &hobby)
{
	string sql = "INSERT INTO students_info(name, sex, school, hobby) values('";
	sql+=name;
	sql+="','";
	sql+=sex;
	sql+="','";
	sql+=school;
	sql+="','";
	sql+=hobby;
	sql+="')";

	int ret = mysql_query(conn, sql.c_str() );
	cout << sql << " ret: "<< ret << endl;
}

int sql::select()
{
	string sql = "select *from students_info";
	int ret = mysql_query(conn, sql.c_str());
	if(ret == 0)
	{
		MYSQL_RES *res = mysql_store_result(conn);//利用malloc开辟一个空间，保存里面的东西，记得要free.
		if(res)
		{
			int lines = mysql_num_rows(res);
			int cols = mysql_num_fields(res);
			cout << "lines:"<<lines <<"cols:"<<cols<<endl;
			MYSQL_FIELD *fd = NULL;
			for(; fd = mysql_fetch_field(res); ) //得到每一列的名字
			{
				cout << fd->name<< " ";
			}
			cout <<endl;
			int i = 0;
			for(; i < lines; ++i)
			{
				MYSQL_ROW row = mysql_fetch_row(res); //得到每一行的信息。
				int j = 0;
				for(; j < cols; j++)
				{
					cout << row[j] <<" ";  //得到一行中每一列的信息。
				}
				cout <<endl;
			}
		}
		return 0;
	}
	return -1;
}


sql:: ~sql()
{
	mysql_close(conn);

}
