/*************************************************************************
	> File Name: pool.h
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 07:48:13 AM PDT
 ************************************************************************/
#ifndef _POOL_H_
#define _POOL_H_

#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include <semaphore.h>


class pool
{
	public:
		pool(int size);
		int get_data(string &out);
		int put_data(const string &in);
		~pool();
	private:
		pool(const pool &p);
		sem_t c_sem;
		sem_t p_sem;  //相当于空白各格子。
		vector<string> data_pool; //用vector来模拟环形队列。
};



#endif
