/*************************************************************************
	> File Name: log.h
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 06:55:58 AM PDT
 ************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_


#include<iostream>
using namespace std;
#include<string>

string err_list[] = {
	"SUCCESS",
	"NOTICE",
	"WARNING",
	"ERROR",
	"FATAL",
};

void write_log(const string & msg, int level)
{
#ifdef _STDOUT_
	cerr<< "[" << msg << "]" << "[" << err_list[level] << " ]" <<endl;
#endif
}




#endif
