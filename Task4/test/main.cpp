#include<jsonapp/json_app.h>
using namespace std;
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <JSON_file>" << endl;
        return 1;
    }

    JsonApp app(argv[1]);

    while (true) {
        int choice;
        cout << "Enter '1' to display info or '2' to display app details 0 for exit: ";
        cin>>choice;
        switch (choice) {
            case 1:
                app.searchId();
                break;
            case 2:
                app.DisplayApps();
                break;
            case 0:
                return 0;
            default:
                cerr << "Error: invalid choice" << endl;
                break;
        }
    }

    return 0;
}  