#include "json_app.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <JSON_file>" << std::endl;
        return 1;
    }

    JsonApp app(argv[1]);

    while (true) {
        std::string choice;
        std::cout << "Enter 'id' to display info or 'app' to display app details ('exit' to quit): ";
        std::getline(std::cin, choice);

        switch (hash(choice.c_str())) {
            case hash("id"):
                app.searchId();
                break;
            case hash("app"):
                app.searchApp();
                break;
            case hash("exit"):
                return 0;
            default:
                std::cerr << "Error: invalid choice" << std::endl;
                break;
        }
    }

    return 0;
}
#include "json_app.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <JSON_file>" << std::endl;
        return 1;
    }

    JsonApp app(argv[1]);

    while (true) {
        std::string choice;
        std::cout << "Enter 'id' to display info or 'app' to display app details ('exit' to quit): ";
        std::getline(std::cin, choice);

        switch (hash(choice.c_str())) {
            case hash("id"):
                app.searchId();
                break;
            case hash("app"):
                app.searchApp();
                break;
            case hash("exit"):
                return 0;
            default:
                std::cerr << "Error: invalid choice" << std::endl;
                break;
        }
    }

    return 0;
}

