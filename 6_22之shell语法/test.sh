#########################################################################
# File Name: test.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 02:00:21 AM PDT
#########################################################################
#!/bin/bash


var=10
str="this is a test"

#-a连两个表达式
test $var -eq 10 -a "$str" == "this is a test" #比较字符串最好加上双引号。“$str"
	echo $?


#  && 连两个命令
test $var -eq 10 && test "$str" == "this is a test"
	echo $?


[ $var -eq 10 -a "$str" != "this is a test" ]
	echo $?

[ $var -eq 10 ] && [ "$str" != "this is a test" ]
	echo $?
