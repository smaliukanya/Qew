#include "SFML/Graphics.hpp"
#include <vector>
#include "menu.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1280, 720), "Game");
    View view;
    Menu menu(window);

    menu.drawMenu();

    return 0;
}
