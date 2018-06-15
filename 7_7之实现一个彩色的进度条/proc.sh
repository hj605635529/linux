#########################################################################
# File Name: proc.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 06 Jul 2017 11:08:27 PM PDT
#########################################################################
#!/bin/bash


index=('|' '/' '-' '\\') #定义一个字符数组
bar='#'

i=0
while [ $i -le 100 ]
do
	let colour=30+i%8
	echo -en "\e[1;"$colour"m"
	

	printf "[%-100s][%d][%c]\r" "$bar" "$i" "${index[i%4]}"

	let i++
	bar+='#'
	usleep 300000
done

#恢复颜色并且换行，使得shell命令提示在下一行
echo -e "\e[1;m"
