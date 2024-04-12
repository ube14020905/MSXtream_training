#include "json_app.h"

JsonApp::JsonApp(const string& path) : path(path) {
    readJson();
}

JsonApp::~JsonApp() {}

void JsonApp::readJson() {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error: Unable to open JSON file." << endl;
        return;
    }

    ostringstream ss;
    ss << file.rdbuf();
    JsonParser parser(ss.str());
    object = parser.getJsonObject();

    file.close();
}
void JsonApp::searchId() {
    JsonObject info = object.getJsonObject("info");
    if (info.size() == 0) {
        cerr << "No info found in the JSON file." << endl;
        return;
    }
    cout << "Available info:" << endl;
    for (size_t i = 0; i < info.size(); ++i) {
        JsonObject infoObj = info[i];
        printById(infoObj);
    }
    cout << "Enter the key or 'all' for printing all ids: ";
    string key;
    cin >> key;
    if (key == "all" || key == "All" || key == "ALL") {
        for (size_t i = 0; i < info.size(); ++i) {
            JsonObject infoObj = info[i];
            printById(infoObj);
        }
    } else {
        bool keyFound = false;
        for (size_t i = 0; i < info.size(); ++i) {
            JsonObject infoObj = info[i];
            if (key == infoObj["key"].toString()) {
                printById(infoObj);
                keyFound = true;
                break;
            }
        }
        if (!keyFound) {
            cerr << "Key '" << key << "' not found in the JSON file." << endl;
        }
    }
}

void JsonApp::printById(JsonObject& infoObj) {
    cout << "Key: " << infoObj["key"].toString() << endl;
    cout << "Action: " << infoObj.getJsonObject("value").getJsonObject("action").toString() << endl;
    cout << "Message: " << infoObj.getJsonObject("value").getJsonObject("msg").toString() << endl;
}

void JsonApp::DisplayApps() {
    JsonObject app = object.getJsonObject("app");
    if (app.size() == 0) {
        cerr << "No apps found in the JSON file." << endl;
        return;
    }
    cout << "Available apps:" << endl;
    for (size_t i = 0; i < app.size(); ++i) {
        JsonObject appObj = app[i];
        printByApp(appObj);
    }
}

void JsonApp::printByApp(JsonObject& appObj) {
    cout << "Key: " << appObj["key"].toString() << endl;
    cout << "Value: " << appObj["value"].toString() << endl;
}
