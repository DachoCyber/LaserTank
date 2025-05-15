#include "include/game.h"
#include "include/mainMenu/mainMenu.h"

#include "include/mainMenu/resources.h"

int main() {

    try {
        loadGlobalFont();
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    MainMenu menu(5);
    menu.run();

    int chosenLevel = menu.getChosenLevel();
    if (chosenLevel != -1) {
        MainGame game(512, 512, chosenLevel);
        game.run();
    }

    return 0;
}
