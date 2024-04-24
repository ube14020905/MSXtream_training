#include "http_json.h"
#include<iostream>

using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <JSON_file>" << endl;
        return 1;
    }
	string configpath=argv[1];

	JsonApp config(configpath);
	JsonObject obj=config.getObject();
	string jsonpath=obj["src"];

	httpjson *server=new httpjson(jsonpath,configpath);

	map<string, SBU2WebService *> * jWebService = new map<string, SBU2WebService *>;
	
	string end_url = obj["httpServer"]["endUrl"];
	int load = stoi(obj["httpServer"]["load"]);
	int port = stoi(obj["httpServer"]["port"]);
	cout << "end url: " << end_url << "\tLoad :" << load << "\tport: " << port << endl;
	(*jWebService)[end_url] = server;
	SBU2LoadBalancer *loadBalancer = new SBU2LoadBalancer(load,jWebService);
	SBU2HTTPServer *httpServer = new SBU2HTTPServer(port , loadBalancer);
	httpServer->run();
	while(1);
}