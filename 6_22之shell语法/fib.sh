#########################################################################
# File Name: fib.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: 2017年06月28日 星期三 06时14分48秒
#########################################################################
#!/bin/bash -x

#第一种写法
#first=1
#second=1
#last=1
#
#if [ $1 -le 2 ];then
#	echo 1
#fi
#
#i=3
#while [ $i -le $1 ]
#do
#	let last=first+second
#	let first=second
#	let second=last
#	let i++
#done
#
#echo $last
#

#第二个版本 用数组
#array[0]=1
#array[1]=1
#
#read num
#i=2
#while [ $i -lt $num ]
#do
#	let array[$i]=array[$i-1]+array[$i-2]
#	let i++
#done
#
#echo ${array[$num-1]}

#第三种递归写法
function fib()
{

	temp=$1
	if [ $temp -le 2 ];then
		echo 1
		return 
	fi

	 res1=`fib $(( temp-1 ))`                 #将temp减1的值当做fib 的参数，求出这个函数的返回值给res1
	 res2=`fib $(( temp-2 ))`

	echo $((res1+res2)) #输出res1+rest2后的值。
}

read num
fib $num



