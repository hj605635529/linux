#########################################################################
# File Name: if.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Thu 22 Jun 2017 01:18:28 AM PDT
#########################################################################
#!/bin/bash

echo "please your score:"

read score

if [ $score -gt 90 ];then
	echo "优秀"
elif [ $score -gt 80 -a $score -le 90 ];then
	echo "良好"
elif [ $score -gt 70 -a $score -le 80 ];then
	echo "中等"
elif [ $score -gt 60 -a $score -le 70 ];then
	echo "及格"
else
	echo "不及格"
fi


[ $score -le 100 ] && { 
	echo "hello shell"
}   #最后这个}一定要写在下一行，表示如果条件满足就执行后面的语句。


if [ -d /bin ];then
	echo "bin is dir"
fi

if [ -d /dev ];then
	echo "dev is dir too"
fi

if :;then
	echo "alway is true"
fi


if [ $score -ge 60 ];then echo "及格"; echo "不用补考";else echo "不及格";fi

