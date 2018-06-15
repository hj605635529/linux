#########################################################################
# File Name: case.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 02:07:47 AM PDT
#########################################################################
#!/bin/bash

#  最笨的写法
#
#read num
#
#case $num in
#	10)
#		echo "hello 10"
#		;;
#	20)
#		echo "hello 20"
#		;;
#	30)
#		echo "default"
#		;;
#	*)
#		echo "unknow"
#		;;
#esac

read num
case $num in
	10|20)
		echo "hello $num"
		;;
	30)
		echo "default"
		;;
	*)
		echo "unknow"
		;;
esac



