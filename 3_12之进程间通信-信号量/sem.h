/*************************************************************************
	> File Name: sem.h
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Sun 12 Mar 2017 12:16:26 AM PST
 ************************************************************************/

#ifndef _SEM_H_
#define _SEM_H_
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

#define PATHNAME "."
#define PROJ_ID 0x666


int creat_sem(int nsems);  //创建几个信号量。

int init_sem(int semid); //对信号量初始化。

int get_sem();  //得到信号量。

int destroy_sem(int semid);  //销毁信号量。

int p_sem(int semid,int which); //对信号量中某一个信号操作。

int v_sem(int semid,int which);//对信号量中某一个信号操作。






#endif
