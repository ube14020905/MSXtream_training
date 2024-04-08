#include "client.h"

int main(){
	client clnt("localhost",8080);
	clnt.start();
	return 0;
}
