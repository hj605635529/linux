#########################################################################
# File Name: until.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 08:38:16 AM PDT
#########################################################################
#!/bin/bash


i=0
sum=0
until [ $i -gt 100 ]  #直到i大于100就不进入循环
do
	let sum+=i
	let i++
done

echo $sum

#死循环
until ! :
do
	echo "######################"
done
