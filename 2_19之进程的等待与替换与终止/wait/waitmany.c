/*************************************************************************
  > File Name: waitmany.c
  > Author: huangjia
  > Mail: 605635529@qq.com 
  > Created Time: 2017年07月18日 星期二 03时05分32秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h> 


#define _PORC_NUM_ 10

#define _DEFAULT_PID_ -1 

int child_run()
{ 
	srand(time(NULL));
	int _time = rand()%30;
	printf("hello bit!, this child pid is : %d, sleep time long is :%d\n",getpid(), _time);
	sleep(_time);
	return 0;
}

//return 0, success, else return 1

int creat_proc(pid_t *_pid_l, int _num)
{
	if( _pid_l != NULL && _num > 0 )
	{
		int i=0;
		for(; i < _num; i++) // 创建10个子进程
		{
			pid_t id = fork();
			if( id < 0 )
			{
				printf("%s : creat %d proc failed\n",__FUNCTION__, i);
				return 1; 
			}
			else if( id == 0 )
			{ //child
				int child_ret = child_run();
				exit(1);
			}
			else
			{
				_pid_l[i] = id; 
			}
		}
	}
	return 0;
}

//return 0,success, else return 1
//
int wait_proc(pid_t *_pid_l, int _num)
{
	int _wait_ret = 0;
	if( _pid_l != NULL && _num > 0 )
	{
		int i = 0;
		for(; i<_num; i++)
		{

			if(_pid_l[i] == _DEFAULT_PID_)
			{
				continue;
			}

			int status = 0;
			int ret = waitpid( _pid_l[i], &status, 0);//阻塞等待 
			if( WIFEXITED(status) && ret == _pid_l[i] )
			{
				printf("wait child pid %d success,return code is : %d\n",_pid_l[i],
						WEXITSTATUS(status)); 
			}
			else
			{
				printf("wait child pid %d failed\n",_pid_l[i]);
				_wait_ret = 1;
			}
		}


	}

	return _wait_ret;

}


int main(int argc, char **argv)
{
	pid_t _pid_list[_PORC_NUM_];
	int i=0;
	for(; i<_PORC_NUM_; i++){
		_pid_list[i] = _DEFAULT_PID_;
	}
	if( creat_proc(_pid_list, sizeof(_pid_list)/sizeof(_pid_list[0])) == 0 ){ //watch out!!! sizeof*/
		//sizeof*[0] !!!!
			printf("%s :create all proc success!\n",__FUNCTION__);
	}else{
		printf("%s :not all proc create success!\n",__FUNCTION__);
	}
	if( wait_proc(_pid_list, sizeof(_pid_list)/sizeof(_pid_list[0])) == 0 ){
		printf("%s :wait all proc success!\n",__FUNCTION__);
	}else{
		printf("%s :not wait all proc success!\n",__FUNCTION__);
	}
	return 0;
}
