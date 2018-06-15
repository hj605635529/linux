#########################################################################
# File Name: array.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: 2017年06月28日 星期三 05时44分13秒
#########################################################################
#!/bin/bash

#myarray=(1 "hello" 'c' 3.14)
#
#echo ${myarray[0]} #打印数组中第一个元素的值 
#echo ${myarray[@]} #将数组中所有的元素都打印出来。
#echo ${#myarray[@]} #打印数组的长度
#
#for((i=0;i<${#myarray[@]};i++))
#do
#	echo   ${myarray[i]}
#done

array=(123 "345" "fjid" dd 12.3)

echo ${array[1]}
echo ${array[0]}
echo ${array[@]}
echo ${#array[@]}

echo "array bianli"

for ((i=0;i<${#array[@]};++i))
do
	echo ${array[i]}
done
