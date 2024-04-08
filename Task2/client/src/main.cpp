#include "client.h"

int main(){
	client clnt("127.0.0.1",8080);
	while (true)
	{
	clnt.start();
	}
	return 0;
}
