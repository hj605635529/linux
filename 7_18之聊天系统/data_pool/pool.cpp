/*************************************************************************
	> File Name: pool.cpp
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Tue 18 Jul 2017 07:51:31 AM PDT
 ************************************************************************/

#include"pool.h"

#include<iostream>
using namespace std;


pool::pool():data_pool(size)
{
	sem_init(&c_sem, 0, 0);
	sem_init(&p_sem, 0, size);
}


int pool::get_data(const string &in)
{
	sem_wait(&c_sem);
	sem_post(&p_sem);
}


int pool::put_data(const string &in)
{
	sem_wait(&p_sem);
	sem_post(&c_sem);
}

pool::~pool()
{
	sem_destroy(&c_sem);
	sem-destroy(&p_sem);
}
