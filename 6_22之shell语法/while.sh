#########################################################################
# File Name: while.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 08:09:10 AM PDT
#########################################################################
#!/bin/bash -x

echo "please enter your passwd!"

read ps

while [ ! $ps == "yes" ]
do
	echo "try again"
	read ps
done

echo "done!"


count=0

while [ $count -le 10 ]
do
	echo "this is the $count times"
#	let count++  第一种写法
#	((count++)) 第二种写法
#   ((count = count+1)) 第三种写法
#   count=$((count+1))  第四种写法
	count=$[count+1]   # 第五种写法
done

echo "done!"

count=0
sum=0
while [ $count -le 100 ]
do
	let sum+=count
	let count++
done
echo $sum

#死循环
while :
do
	echo "######################"
	sleep 1
done

