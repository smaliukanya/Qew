#include "SFML/Graphics.hpp"
#include <sstream>
#include <vector>
#include "GameManager.h"

using namespace sf;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Game");
    View view;
    GameManager gameManager(window);

    gameManager.startGame();

    return 0;
}
