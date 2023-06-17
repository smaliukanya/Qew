#include <SFML/Graphics.hpp>
#include <sstream>
#include "map.h"
#include "class.h"
#include "view.h"
//#include "mission.h"

using namespace sf;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 640), "Qew");
    view.reset(sf::FloatRect(0, 0, 1280, 800));

    bool showMissionText = true;

    Font font;
    font.loadFromFile("CyrilicOld.TTF");
    Text text(" ", font, 20);
    text.setOutlineColor(Color::Black);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);

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

    Image Hero;
    Hero.loadFromFile("images/cat.png");

    Image EasyEnemyImage;
    EasyEnemyImage.loadFromFile("images/nebro.png");

    Player player2(Hero, 128, 650, 90, 85, "player2");
    Enemy easyEnemy(EasyEnemyImage, 850, 632, 110, 100, "EasyEnemy");


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
        easyEnemy.update(time);

        window.setView(view);
        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(IntRect(0, 0, 32, 32)); //���� ��������� ������ ������, �� ������ 1� ���������
                if (TileMap[i][j] == 's')  s_map.setTextureRect(IntRect(32, 0, 32, 32));//���� ��������� ������ s, �� ������ 2� ���������
                if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64, 0, 32, 32));//���� ��������� ������ 0, �� ������ 3� ���������


                s_map.setPosition(j * 32, i * 32);

                window.draw(s_map);
            }

        window.draw(player2.sprite);
        window.draw(easyEnemy.sprite);

        window.draw(text);

        if (player2.life == false) {

            window.draw(text2);
            text2.setString("GAME OVER");
            text2.setPosition(view.getCenter().x - 200, view.getCenter().y);
        }
        window.display();
    }

    return 0;
}