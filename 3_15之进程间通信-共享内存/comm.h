#ifndef _COMM_H_
#define _COMM_H_


#include<stdio.h>
#include<sys/shm.h>
#include<errno.h>
#include<sys/types.h>
#include<unistd.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

int creat_shm(size_t size);
int get_shm();
int destroy_shm(int shmid);



#endif 
