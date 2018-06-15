/*************************************************************************
	> File Name: work.c
	> Author: huangjia
	> Mail: 605635529@qq.com 
	> Created Time: Thu 16 Feb 2017 02:55:37 AM PST
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>
dint main()
{
	char buf[102] = { 0 };//因为0~100就101个数，再加上‘\0'就102个数了。
	char *label = "-\\|/";
	int i = 0;

	for (;i <= 100; ++i)
	{
		printf("[%-100s],[%d%%],[%c]\r",buf,i,label[i%4]);

		fflush(stdout);

		usleep(1000000);
		buf[i] = '#';
	}
	printf("\n");

	return 0;
}

