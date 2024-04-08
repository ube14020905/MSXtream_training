#include "client.h"

client::client(std::string ip,int port){
	TCPClient(ip,port);
}
void client::start(){
	std::string msg;
	std::cout<<"Enter a message or(type 'exit' to exit) : ";
	while(true){
		std::cin>>msg;
		if(msg=="exit"){
			break;
		}
		int bytes=sendData(msg);
		if(bytes > 0){
			std::cout<<"msg sent"<<endl;
		}
		bytes=readLine(msg);
		if(bytes > 0)
		{
			std::cout<<"Received from server: "<<msg<<endl;
		}
	}
}

client::~client(){}
