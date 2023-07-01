#include "SFML/Graphics.hpp"
#include "iostream"
#include <windows.h>
#include "class.h"

using namespace sf;

class GameManager {
public:
	RenderWindow& window;
    Clock clock;
	Texture backgroundTexture;
	Sprite background;
    Texture map;
    Sprite s_map;
    Font font;
    Player player2;
    Image Hero;
    Image hp_image;
    GameManager(sf::RenderWindow& window) : window(window), player2(Hero, 128, 600, 65, 135, "player2") {
        Hero.loadFromFile("images/hero.png");
        Player temp(Hero, 128, 600, 65, 135, "player2");
        player2 = temp;

        Image EasyEnemyImage;
        EasyEnemyImage.loadFromFile("images/nebro.png");

        Image hp_image;
        hp_image.loadFromFile("images/heart.png");

        Image coin_image;
        coin_image.loadFromFile("images/coin.png");

        player2.enemy.push_back(new Enemy(EasyEnemyImage, 600, 550, 60, 60, "EasyEnemy"));
        player2.enemy.push_back(new Enemy(EasyEnemyImage, 1500, 550, 60, 60, "EasyEnemy"));

        player2.bonus.push_back(new Bonus(hp_image, 420, 550, 32, 32, "heart"));
        player2.bonus.push_back(new Bonus(hp_image, 1520, 320, 32, 32, "heart"));

        int xcn = 800;

        for (int i = 0; xcn < 2200; i++) {
            xcn += 32;

            player2.bonus.push_back(new Bonus(coin_image, xcn, 550, 32, 32, "coin"));
        }

        backgroundTexture.loadFromFile("images/back.jpg");
        if (!backgroundTexture.loadFromFile("images/back.jpg")) {
            std::cout << "image not loaded";
        }

        background.setTexture(backgroundTexture);

        view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
        view.setCenter(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
        background.setScale(window.getSize().x / background.getLocalBounds().width, window.getSize().y / background.getLocalBounds().height);

        map.loadFromFile("images/map.png");
        s_map.setTexture(map);

        font.loadFromFile("CyrilicOld.TTF");
    }

    void update(float time) {
        player2.update(time);

        for (int i = 0; i < player2.enemy.size(); i++) {
            player2.enemy[i]->update(time);
        }

        for (int i = 0; i < player2.bonus.size(); i++) {
            player2.bonus[i]->update(time);
        }
    }

    void draw() {

        window.setView(view);
        

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
    }

    void information() {
        Text text(" ", font, 20);
        text.setOutlineColor(Color::Black);
        text.setFillColor(Color::Black);

        std::ostringstream playerScoreString;
        playerScoreString << player2.score;
        std::ostringstream playerHealthString;
        playerHealthString << player2.health;

        text.setString("LEVEL 1\nScore: " + playerScoreString.str() + "\nHealth: " + playerHealthString.str());
        text.setPosition(view.getCenter().x - 600, view.getCenter().y - 350);
        window.draw(text);
    }

    void endGame() {
        Texture Died;
        Died.loadFromFile("images/died.jpg");

        Sprite Died_sprite;
        Died_sprite.setTexture(Died);
        Died_sprite.setPosition(view.getCenter() - sf::Vector2f(1280 / 2, 720 / 2));
        window.draw(Died_sprite);

        Text text1(" ", font, 40);
        text1.setOutlineColor(Color(97, 43, 41));
        text1.setFillColor(Color(97, 43, 41));
        text1.setString("MENU");
        text1.setPosition(view.getCenter().x - 300, view.getCenter().y + 100);

        Text text2(" ", font, 40);
        text2.setOutlineColor(Color(97, 43, 41));
        text2.setFillColor(Color(97, 43, 41));
        text2.setString("RESTART");
        text2.setPosition(view.getCenter().x + 120, view.getCenter().y + 100);

        window.draw(text1);
        window.draw(text2);

        player2.clearBonus();
        endGameMenu(text1,text2);
    }

    void startGame() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }

            window.clear();

            float time = clock.getElapsedTime().asMicroseconds();
            clock.restart();
            time = time / 800;

            update(time);
            draw();
            if (player2.health <= 0) {
                endGame();
            }
            information();
            window.display();
        }
    }

    void endGameMenu(Text text1, Text text2) {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                else if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        sf::FloatRect text1Bounds = text1.getGlobalBounds();
                        sf::FloatRect text2Bounds = text2.getGlobalBounds();

                        if (text1Bounds.contains(static_cast<sf::Vector2f>(mousePosition)))
                        {


                        }
                        else if (text2Bounds.contains(static_cast<sf::Vector2f>(mousePosition)))
                        {
                            std::cout << "yeh";
                            player2.health = 100;
                            startGame();
                        }
                    }
                }
            }
        }
};