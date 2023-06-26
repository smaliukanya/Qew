#include "SFML/Graphics.hpp"
#include <sstream>
//#include "menu.h"
#include <vector>
#include "class.h"
#include "GameManager.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Qew");
    view.reset(sf::FloatRect(0, 0, 1280, 720));

    //menu(window);

    Font font;
    font.loadFromFile("CyrilicOld.TTF");

    Text text(" ", font, 20);
    text.setOutlineColor(Color::Black);
    text.setFillColor(Color::Black);

    Text text2(" ", font, 70);
    text2.setOutlineColor(Color::Black);
    text2.setFillColor(Color::Black);
    text2.setStyle(Text::Bold);

    Image map_image;
    map_image.loadFromFile("images/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);

    Image back_image;
    back_image.loadFromFile("images/back.jpg");
    Texture back_texture;
    back_texture.loadFromImage(back_image);
    Sprite background;
    background.setTexture(back_texture);

    Image Hero;
    Hero.loadFromFile("images/hero.png");

    Image EasyEnemyImage;
    EasyEnemyImage.loadFromFile("images/nebro.png");

    //Image BossImage;
    //BossImage.loadFromFile("images/cat.png");

    Image hp_image;
    hp_image.loadFromFile("images/heart.png");

    Image coin_image;
    coin_image.loadFromFile("images/coin.png");


    Player player2(Hero, 128, 600, 65, 135, "player2");

    player2.enemy.push_back(new Enemy(EasyEnemyImage, 600, 550, 60, 60, "EasyEnemy"));
    player2.enemy.push_back(new Enemy(EasyEnemyImage, 1500, 550, 60, 60, "EasyEnemy"));

    player2.bonus.push_back(new Bonus(hp_image, 420, 550, 32, 32, "heart"));
    player2.bonus.push_back(new Bonus(hp_image, 1520, 320, 32, 32, "heart"));

    int xcn = 800;

    for (int i = 0; xcn < 2200; i++) {
        xcn += 32;

        player2.bonus.push_back(new Bonus(coin_image, xcn, 550, 32, 32, "coin"));
    }

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape)
                    window.close();
            }
        }

        player2.update(time);

        for (int i = 0; i < player2.enemy.size(); i++) {
            player2.enemy[i]->update(time);
        }

        for (int i = 0; i < player2.bonus.size(); i++) {
            player2.bonus[i]->update(time);
        }

        window.setView(view);

        window.clear();


        background.setPosition(view.getCenter() - sf::Vector2f(1280 / 2, 720 / 2));
        window.draw(background);

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == 's') {
                    s_map.setTextureRect(IntRect(32, 17, 32, 14));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                }
                if (TileMap[i][j] == '0') {
                    s_map.setTextureRect(IntRect(0, 0, 32, 32));
                    s_map.setPosition(j * 32, i * 32);
                    window.draw(s_map);
                };

            }


        window.draw(player2.sprite);

        for (int i = 0; i < player2.enemy.size(); i++) {
            window.draw(player2.enemy[i]->sprite);
        }

        for (int i = 0; i < player2.bonus.size(); i++) {
            window.draw(player2.bonus[i]->sprite);
        }

        std::ostringstream playerScoreString;
        playerScoreString << player2.score;
        std::ostringstream playerHealthString;
        playerHealthString << player2.health;

        text.setString("LEVEL 1\nScore: " + playerScoreString.str() + "\nHealth: " + playerHealthString.str());
        text.setPosition(view.getCenter().x - 600, view.getCenter().y - 350);
        window.draw(text);

        if (player2.life == false) {

            window.draw(text2);
            text2.setString("GAME OVER");
            text2.setPosition(view.getCenter().x - 200, view.getCenter().y);
            player2.clearBonus();
        }

        window.display();
    }


    return 0;
}