#ifndef JSON_APP_H
#define JSON_APP_H

#include "jsonparser/JsonParser.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace UBACJSON;

class JsonApp {
private:
    JsonObject object;
    string path;

    void readJson();

    void printById(JsonObject& obj);

    void printByApp(JsonObject& obj);

public:
    JsonApp(const string& path);

    ~JsonApp();

    void searchId();

    void DisplayApps();
};

#endif
