#ifndef  _UDP_SERVER_H_
#define  _UDP_SERVER_H_


#include<iostream>
#include<string>
#include<map>
using namespace std;

class udp_server
{
public:
	udp_server(const string & _ip, const int & _port);
	int init_server();
	int udp_server::add_online_user(struct sockaddr_in *client);
	int recv_msg(string &out);
	int send_msg(const string &in, struct sockaddr_in & peer, const int &len);
	int brocast_msg();
	~udp_server();

private:
	udp_server(const udp_server & );  //拷贝构造私有的，
	string ip;
	int port;
	int sock;
	map<int, struct sockaddr_in> online_user; //在线人数，第一个参数表示ip, 第二个参数不用指针，直接用对象，因为当下线后，这个对象就不存在了，
	pool data_pool; //数据池
};


#endif
