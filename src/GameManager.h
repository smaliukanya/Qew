#include "SFML/Graphics.hpp"
#include <sstream>
#include "iostream"
#include "class.h"

using namespace sf;

class GameManager {
private:
    RenderWindow& window;
    SoundManager sounds;
    Clock clock;
    Texture backgroundTexture;
    Sprite background;
    Texture map;
    Sprite s_map;
    Font font;
    Player player2;
    Image Hero;
    Image hp_image;
    int level = 1;
public:
    GameManager(sf::RenderWindow& window) : window(window), player2(Hero, 128, 600, 65, 135, "player2") {
        Hero.loadFromFile("images/hero.png");
        Player temp(Hero, 128, 600, 65, 135, "player2");
        player2 = temp;

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

    void addEntity(); //добавление элементов на карту
    void update(float time); //обновление
    void draw(); //выведение элементов на экран
    void information(); //информация в игре (здоровье, счет, уровень)
    void endGame(); //конец игры
    void startGame(); //старт игры
    void endGameMenu(Text text1, Text text2); //меню при смерти персонажа 
    void restartGame(); //перезагрузка игры
};

void GameManager::addEntity() {
    Image EasyEnemyImage;
    EasyEnemyImage.loadFromFile("images/nebro.png");

    Image hp_image;
    hp_image.loadFromFile("images/heart.png");

    Image coin_image;
    coin_image.loadFromFile("images/coin.png");

    Image boss_image;
    boss_image.loadFromFile("images/sven.png");

    if (level = 1) {
        player2.enemy.push_back(new Enemy(EasyEnemyImage, 600, 550, 60, 60, "EasyEnemy"));
        player2.enemy.push_back(new Enemy(EasyEnemyImage, 1500, 550, 60, 60, "EasyEnemy"));
        player2.enemy.push_back(new Enemy(boss_image, 2400, 500, 130, 130, "sven"));

        player2.bonus.push_back(new Bonus(hp_image, 1520, 320, 32, 32, "heart"));
        player2.bonus.push_back(new Bonus(hp_image, 1952, 260, 32, 32, "heart"));

        int xcn = 630;
        int ycn = 550;
        for (int i = 0; xcn < 2200; i++) {
            xcn += 32;
            if (xcn == 662) ycn = 450;
            if (xcn == 758) { ycn = 350; xcn += 10; }
            if (xcn <= 1152 && xcn >= 896) ycn = 0;
            if (xcn == 1152) ycn = 415;
            if (xcn == 1280) ycn = 320;
            if (xcn <= 1664 && xcn >= 1504) ycn = 0;
            if (xcn == 1728) ycn = 290;
            if (xcn <= 2000 && xcn >= 1856) ycn = 0;
            if (xcn == 2112) ycn = 260;
            if (ycn > 1) {
                player2.bonus.push_back(new Bonus(coin_image, xcn, ycn, 32, 32, "coin"));
            }
        }
    }
}

void GameManager::update(float time) {
    player2.update(time);

    for (int i = 0; i < player2.enemy.size(); i++) {
        player2.enemy[i]->update(time);
    }

    for (int i = 0; i < player2.bonus.size(); i++) {
        player2.bonus[i]->update(time);
    }
}

void GameManager::draw() {

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

void GameManager::information() {
    Text text(" ", font, 20);
    text.setOutlineColor(Color::Black);
    text.setFillColor(Color::Black);

    std::ostringstream playerScoreString;
    playerScoreString << player2.setScore();
    std::ostringstream playerHealthString;
    playerHealthString << player2.health;

    text.setString("LEVEL 1\nScore: " + playerScoreString.str() + "\nHealth: " + playerHealthString.str());
    text.setPosition(view.getCenter().x - 600, view.getCenter().y - 350);
    window.draw(text);
}

void GameManager::startGame() {
    sounds.playBackgroundMusic();
    addEntity();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.setView(view);
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

void GameManager::endGame() {
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
    player2.getScore(0);
    player2.clear();
    endGameMenu(text1, text2);
}

void GameManager::endGameMenu(Text text1, Text text2) {
    sf::Event event;
    bool isHovered = false;

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
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition); 
                sf::FloatRect text1Bounds = text1.getGlobalBounds();
                sf::FloatRect text2Bounds = text2.getGlobalBounds();


                if (text1Bounds.contains(worldPosition))
                {
                    std::cout << "qwe";

                }
                else if (text2Bounds.contains(worldPosition))
                {
                    restartGame();
                }
            }
        }
        else if (event.type == sf::Event::MouseMoved)
        {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

            if (text1.getGlobalBounds().contains(worldPosition))
            {
                text1.setCharacterSize(50); 
            }
            else
            {
                text1.setCharacterSize(40); 
            }
            if (text2.getGlobalBounds().contains(worldPosition))
            {
                text2.setCharacterSize(50);
            }
            else
            {
                text2.setCharacterSize(40);
            }
        }
    }
    window.draw(text1);
    window.draw(text2);
}

void GameManager::restartGame() {
    std::cout << "yeh";
    player2.life = true;
    player2.health = 100;
    if (level = 1) {
        player2.x = 128;
        player2.y = 550;
    }
    startGame();
}