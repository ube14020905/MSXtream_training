#include "http_json.h"

httpjson::httpjson(string &jsonpath,string &config):SBU2WebService(){
	jsondata =new JsonApp(jsonpath);
	configdata = new JsonApp(config);
	configObj = configdata->getObject();
}

httpjson::~httpjson(){
    delete jsondata;
    delete configdata;
}
void httpjson::onInvalidJSONRequest(HTTPServerRequest *request, HTTPConnection *connection, string &rawRequest){
	cerr << "Request Received: " << rawRequest << endl;
	string infoid,infomsg;
	infoid = configObj["Response_onInvaidJson"]["infoid"];
	infomsg = configObj["Response_onInvalidJson"]["infomsg"];
	MSFRequest* msfreq = new MSFRequest(rawRequest);
	MSFResponse* err = new MSFResponse(msfreq);
	string errmsg = "Invalid JSON request: " + rawRequest;
	err->addToData("error", errmsg);
	err->setInfoID(infoid);
	err->setInfoMsg(infomsg);
	err->setSvcName(configObj["httpServer"]["svcName"]);
	err->setSvcGroup(configObj["httpServer"]["svcGroup"]);
    err->setSvcVersion(configObj["httpServer"]["svcVersion"]);
	sendResponse(err, connection);
	connection->release();
}

void httpjson::onPostProcessRequest(MSFRequest *msfRequest, MSFResponse *msfResponse, HTTPConnection *connection){
	cout << "Request received" << endl;
    string request = msfRequest->toString();
    JsonParser parser(request);
    JsonObject requestObject = parser.getJsonObject();

    if (requestObject.hasKey(configObj["Response_onPostProcessRequest"]["key"])) {
        string contentValue = requestObject[configObj["Response_onPostProcessRequest"]["key"]];

        if(contentValue == configObj["Response_onPostProcessRequest"]["value1"]){
            requestObject = jsondata->getObject();
            msfResponse->addToData("all", requestObject);
            cout << "Applications: "<< requestObject.toString() << endl;
        } else if (contentValue == configObj["Response_onPostProcessRequest"]["value2"]) {
            requestObject = jsondata->getObject();
            msfResponse->addToData("app", requestObject["app"]);
            cout << requestObject.toString() << endl;
        } else if (contentValue == configObj["Response_onPostProcessRequest"]["value3"]) {
            requestObject = jsondata->getObject();
            msfResponse->addToData("info", requestObject["info"]);
            cout << requestObject.toString() << endl;
        }
        else {
        cerr << "Invalid content value." << endl;
	    string infoid = configObj["Response_onPostProcessRequest"]["infoid"];
	    string infomsg = configObj["Response_onPostProcessRequest"]["infomsg"];

            msfResponse->setInfoID(infoid);
            msfResponse->setInfoMsg(infomsg);
        }
    } 
    msfResponse->setSvcName(configObj["httpServer"]["svcName"]);
    msfResponse->setSvcGroup(configObj["httpServer"]["svcGroup"]);
    msfResponse->setSvcVersion(configObj["httpServer"]["svcVersion"]);

    cout << msfResponse->toString() << endl;
    sendResponse(msfResponse, connection);
    connection->release();

}