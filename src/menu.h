//меню в будущем, но пока еще так себе работает

#include "SFML/Graphics.hpp"
#include "view.h"
using namespace sf;

void menu(RenderWindow& window) {
    Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackgroud;

    menuTexture1.loadFromFile("images/111.png");
    menuTexture2.loadFromFile("images/222.png");
    menuTexture3.loadFromFile("images/333.png");
    aboutTexture.loadFromFile("images/about.png");

    menuBackgroud.loadFromFile("images/back.jpg");

    Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackgroud), about(aboutTexture);
    bool isMenu = 1;

    menuBg.setPosition(view.getCenter() - sf::Vector2f(1280 / 2, 720 / 2));

    int menuNum = 0;
    menu1.setPosition(550, 100);
    menu2.setPosition(550, 200);
    menu3.setPosition(550, 300);


    while (isMenu) {
        Event event;
        while (window.pollEvent(event)) { // обработка всех событий окна
            if (event.type == Event::Closed) {
                window.close();
                return;
            }
        }

        if (IntRect(500, 100, 300, 50).contains(Mouse::getPosition(window))) { menu1.setColor(Color::Blue); menuNum = 1; }
        if (IntRect(500, 200, 300, 50).contains(Mouse::getPosition(window))) { menu2.setColor(Color::Blue); menuNum = 2; }
        if (IntRect(500, 300, 300, 50).contains(Mouse::getPosition(window))) { menu3.setColor(Color::Blue); menuNum = 3; }

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            if (menuNum == 1) isMenu = false;
            if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
            if (menuNum == 3) { window.close(); isMenu = false; }

        }
        window.setView(view);
        window.clear();

        window.draw(menuBg);
        window.draw(menu1);
        window.draw(menu2);
        window.draw(menu3);

        window.display();
    }
}