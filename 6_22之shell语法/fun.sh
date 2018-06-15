#########################################################################
# File Name: fun.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: 2017年06月28日 星期三 04时33分20秒
#########################################################################
#!/bin/bash

function myfun()
{	
	echo $0
	min=$1
	max=$1
	for i in $@
	do
		if [ $max -lt $i ];then
			max=$i
		fi

		if [ $min -gt $i ];then 
			min=$i
		fi
	done 
		
}	
myfun $@  #将命令行参数传给函数。

echo "max = $max"
echo "min = $min"


