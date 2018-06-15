#########################################################################
# File Name: main.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Sat 08 Jul 2017 06:03:05 AM PDT
#########################################################################
#!/bin/bash

. ap1.sh  #相当于函数的头文件的引入

function main
{

	fun

}
main

trap handler 2

while :
do
	echo "hehehheehhehhhehhehehhh"
	sleep 1
done
