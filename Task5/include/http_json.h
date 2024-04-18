#ifndef HTTP_JSON_H
#define HTTP_JSON_H

#include<iostream>
#include<sbu2webapp/SBU2WebService.h>
#include<sbu2webapp/SBU2HTTPServer.h>
#include<jsonapp/json_app.h>
#include<jsonparser/JsonParser.h>

using namespace std;
using namespace SBU2;
using namespace UBACIPC;
class httpjson : public SBU2WebService
{
	public:
		httpjson(string& jsonpath,string& config);
		~httpjson();
		void onInvalidJSONRequest(HTTPServerRequest * request, HTTPConnection * connection, string & rawRequest);
		void onPostProcessRequest(MSFRequest *msfRequest, MSFResponse *msfResponse, HTTPConnection *connection);
	private:
		JsonApp *jsondata,*configdata;
		string jsonpath,configpath;
		JsonObject request,response,configObj;

};

#endif
