
#include"udp_server.h"
#include"log.h"

udp_server::udp_server(const string & _ip, const int & _port)
{
	ip = _ip;
	port = _port;
}

int  udp_server::init_server()
{
	sock = socket(AF_INET,SOCK_DGRAM, 0);
	if(sock < 0)
	{
		write_log("create sock error", FATAL);
		return -1;
	}

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr_s_addr = inet_addr(ip.c_str() );
	local.sin_port = htons(port);
	
	int ret = bind(sock, (struct sockaddr*)&local, sizeof(local) );
	if(ret < 0)
	{
		write_log("bind sock error",FATAL)
	}

	return 0;
}

int udp_server::add_online_user(struct sockaddr_in *client)
{
	online_user.insert(pair<int,struct sockaddr_in>(client.sin_addr.s_addr, *client));
}

int  udp_server::recv_msg( string & out ) //将收到的信息存入out中。
{
	char buf[1024];
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);

	int ret = recvfrom(sock, buf, sizeof(buf)-1, 0, (struct sockaddr*)&peer, &len);
	if(ret >  0)
	{
		buf[ret] = 0;
		out = buf;  
		add_online_user(&peer);
	}
}

int  udp_server::send_msg(const string & in, struct sockaddr_in &peer, const int &len) //将in中的消息发送给peer, len表示peer的大小。
{
	int ret = sendto(sock, in.c_str(), in.size(), 0, (struct sockaddr*)&peer, len);
	if (ret < 0)
	{
		write_log("send msg error", WARNING);
		return -2;
	}
}

int  udp_server::brocast_msg()
{
	string msg = data_pool.get_data();
	map<int, struct sockaddr_in>::iterator iter = online_user.begin();
	for(; iter != online_user.end(); iter++)
	{
		send_msg( msg, iter->second, sizeof(iter->second) );
	}
	
	return 0;
}
udp_server::~udp_server()
{
	close(sock);
}
