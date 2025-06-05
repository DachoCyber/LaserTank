#include "include/game.h"
#include "include/mainMenu/mainMenu.h"

#include "include/mainMenu/resources.h"

#include <filesystem>
namespace fs = std::filesystem;

int countMapFiles(const std::string& folderPath) {
    int count = 0;

    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (filename.size() > 4 && filename.substr(filename.size() - 4) == ".tmx")
                count++;
        }
    }

    return count;
}


int main() {

    try {
        loadGlobalFont();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::string folder = "maps/";
    int levelCount = countMapFiles(folder);


    bool getIsClosed = false;
    MainMenu menu(levelCount);
    menu.run();

    bool enterAnotherLevel = false;
    int chosenLevel;
    do {
        std::cout << chosenLevel << std::endl;
        if (!enterAnotherLevel) {
            chosenLevel = menu.getChosenLevel();
        }
        std::cout << chosenLevel << std::endl;
        if (chosenLevel != -1) {
            MainGame game(512, 512, chosenLevel);
            game.run();
            getIsClosed = !game.getWindowClosedState();
            if (game.gameWon()) {
                std::cout << "game won" << std::endl;
                chosenLevel = (chosenLevel + 1) % levelCount;
                enterAnotherLevel = true;
            }
        }
        std::cout << getIsClosed << std::endl;
    } while (getIsClosed);
    return 0;
}
