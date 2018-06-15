#!/bin/bash

str=http://blog.csdn.net/hj605635529/article/details/73556855
#str2=${str#*//}
#str2=${str%/*}
#str2=${str##*/}
#str2=${str%%/*}
#str2=${str:0:10}

echo $str|cut -c 3,7
echo $str|cut -c 8,15
echo $str|cut -c 4-9
echo $str|cut -c 1-3

#echo "$str2"
