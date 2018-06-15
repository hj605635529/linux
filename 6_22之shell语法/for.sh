#########################################################################
# File Name: for.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 02:15:57 AM PDT
#########################################################################
#!/bin/bash


#  for语句第一种写法
for i in {a..z}
do
	echo "printf val is :$i"
done

# for语句第二种写法

for((i = 0; i <= 100; ++i ))
do
	echo "printf val is :$i"
done

#0~100求和

#  第一种写法 
sum=0    #不加这句话每次执行后sum的初值就是上次的值
for((i = 0; i <= 100 ;++i))
do
	((sum += i ))
done
echo $sum

#第二种写法
sum2=0
for((i = 0; i <= 100; ++i))
do
	sum2=$((sum2+i))
done
echo $sum2

#第三种写法
sum3=0
for((i = 0; i <= 100 ;i++))
do
	sum3=$[sum3+i]
done
echo $sum3

#第四种写法
sum4=0
for((i = 0; i <= 100;))
do
	((sum4+=i))
	((i++))
done
echo $sum4

#第五种写法
sum5=0
for((i = 0; i <=100; ))
do
	let sum5+=i
	let i++
done
echo $sum5
