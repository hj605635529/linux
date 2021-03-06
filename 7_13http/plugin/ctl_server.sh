#!/bin/bash

ROOT_PATH=$(pwd)
LIB=$ROOT_PATH/lib/lib
BIN=$ROOT_PATH/httpd
CONF=$ROOT_PATH/conf/server.conf

id=''
#得到脚本程序的名字
proc=$(basename $0)

function usage()
{
	printf "Usage: %s [ start(-s) | stop(-t) | restart(-rt) | status(-ss) ] \n" "$proc"
}

function server_status()
{
	server_bin=$(basename $BIN)
	id=$(pidof $server_bin)
	if [ ! -z "$id" ];then
		return 0
	else
		return 1
	fi
}

function server_start()
{
	echo "server_start"
	if ! server_status;then
		ip=$(awk -F: '/^IP/{print $NF}' $CONF)
		port=$(awk -F: '/^PORT/{print $NF}' $CONF)
		$BIN $ip $port
	else
		echo "server is already running: $id, please stop first!"
	fi
	echo "server_start end"
}

function server_stop()
{
	if server_status;then
		kill -9 $id
	else
		echo "server is not running, please start first!"
	fi

}

function server_restart()
{
	if server_status;then
		server_stop
	fi
	server_start
}

function service_status()
{
	if server_status;then
		echo "server is running : $id"
	else
		echo "server is not running : $id"
	fi


}

if [ $# -eq 0 ];then
	usage
	exit 1
fi
#
#if [ -z $LD_LIBRARY_PATH ];then
#	 LD_LIBRARY_PATH=$LIB
#	 echo "$LD_LIBRARY_PATH"
#fi

case $1 in
	start | -s )
		server_start
	;;
	stop | -t )
		server_stop
	;;
	restart | -rt )
		server_restart
	;;
	status | -ss )
		service_status
	;;
	* )
	usage;
	exit 1
	;;
esac




