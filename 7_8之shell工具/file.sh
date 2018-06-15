#########################################################################
# File Name: file.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Fri 07 Jul 2017 09:21:31 AM PDT
#########################################################################
#!/bin/bash

ROOT_PATH=$(pwd)
MYFILE=$ROOT_PATH/file
MYDEST=$ROOT_PATH/dest

while read line #从file文件中读取每一行
do

	part1=$(echo "$line" | cut -c 1-3)
	part2=$(echo "$line"| cut -c 4-6|tr '[a-z]' '[A-Z]') #将字符串中第4个到第六个字符剪切下来，并且用tr实现小写转大写功能
	part3=$(echo "$line"| cut -c 7-9)
	
	echo ${part3}${part2}${part1}

done<$MYFILE >$MYDEST #输入输出重定向
