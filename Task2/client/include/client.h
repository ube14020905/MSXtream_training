#ifndef CLIENT_H
#define CLIENT_H

#include<ubacipc/TCPClient.h>
#include<iostream>

class client : public UBACIPC::TCPClient
{
	public:
		client(std::string ip, int port);
		~client();
		void start();
};
#endif
