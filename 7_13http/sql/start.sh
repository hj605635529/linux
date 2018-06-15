#########################################################################
# File Name: start.sh
# Author: huangjia
# mail: 605635529@qq.com
# Created Time: Wed 19 Jul 2017 11:35:10 AM PDT
#########################################################################
#!/bin/bash -x
#将动态库导入到所在的目录导入到环境变量中
export LD_LIBRARY_PATH=/home/huangjia/code/7_13http/sql/lib/lib

./insert_cgi
echo "$LD_LIBRARY_PATH"
