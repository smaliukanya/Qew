#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameManager.h"

using namespace std;

class Menu {
private:
	RenderWindow& window;
    SoundManager sound;
    Font font;
    Texture back_texture;
    Sprite background;
	Text newGame;
	Text settings;
	Text aboutGame;
	Text exit;
public:
	Menu(sf::RenderWindow& window) : window(window){
        back_texture.loadFromFile("images/back_menu.jpg");

        background.setTexture(back_texture);

        font.loadFromFile("beer-money12.ttf");
    }
    void drawMenu();
    void informationAboutGame();
};

void Menu::drawMenu() {
    sound.playMenuMusic();
    Text nameGame(" ", font, 100);
    nameGame.setOutlineColor(Color::Black);
    nameGame.setFillColor(Color::Black);
    nameGame.setString("Name Game");
    nameGame.setPosition(480, 80);

    Text newGame(" ", font, 60);
    newGame.setOutlineColor(Color::Black);
    newGame.setFillColor(Color::Black);
    newGame.setString("New Game");
    newGame.setPosition(540, 220);

    Text settings(" ", font, 60);
    settings.setOutlineColor(Color::Black);
    settings.setFillColor(Color::Black);
    settings.setString("Settings");
    settings.setPosition(540, 320);

    Text aboutGame(" ", font, 60);
    aboutGame.setOutlineColor(Color::Black);
    aboutGame.setFillColor(Color::Black);
    aboutGame.setString("About game");
    aboutGame.setPosition(540, 420);

    Text exit(" ", font, 60);
    exit.setOutlineColor(Color::Black);
    exit.setFillColor(Color::Black);
    exit.setString("Exit");
    exit.setPosition(540, 520);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                    sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);
                    sf::FloatRect text1Bounds = newGame.getGlobalBounds();
                    sf::FloatRect text2Bounds = settings.getGlobalBounds();
                    sf::FloatRect text3Bounds = aboutGame.getGlobalBounds();
                    sf::FloatRect text4Bounds = exit.getGlobalBounds();

                    if (text1Bounds.contains(worldPosition))
                    {
                        sound.endMenuMusic();
                        GameManager gameManager(window);
                        std::cout << "qwe";
                        gameManager.startGame();
                    }
                    else if (text2Bounds.contains(worldPosition))
                    {

                    }
                    else if (text3Bounds.contains(worldPosition))
                    {
                        informationAboutGame();
                    }
                    else if (text4Bounds.contains(worldPosition))
                    {
                        window.close();
                    }
                }
            }
            else if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                if (newGame.getGlobalBounds().contains(worldPosition))
                {
                    newGame.setCharacterSize(70);
                }
                if (settings.getGlobalBounds().contains(worldPosition))
                {
                    settings.setCharacterSize(70);
                }
                if (aboutGame.getGlobalBounds().contains(worldPosition))
                {
                    aboutGame.setCharacterSize(70);
                }
                if (exit.getGlobalBounds().contains(worldPosition))
                {
                    exit.setCharacterSize(70);
                }
                if (!newGame.getGlobalBounds().contains(worldPosition))
                {
                    newGame.setCharacterSize(60);
                }
                if (!settings.getGlobalBounds().contains(worldPosition))
                {
                    settings.setCharacterSize(60);
                }
                if (!aboutGame.getGlobalBounds().contains(worldPosition))
                {
                    aboutGame.setCharacterSize(60);
                }
                if (!exit.getGlobalBounds().contains(worldPosition))
                {
                    exit.setCharacterSize(60);
                }
            }
        }
        window.clear();
        window.draw(background);
        window.draw(nameGame);
        window.draw(newGame);
        window.draw(settings);
        window.draw(aboutGame);
        window.draw(exit);
        window.display();
    }
}

void Menu::informationAboutGame(){
    Image aboutImage;
    aboutImage.loadFromFile("images/about.png");

    Texture about;
    about.loadFromImage(aboutImage);

    Sprite about_s;
    about_s.setTexture(about);
    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }    
        window.clear();
        window.draw(about_s);
        window.display();
    }

}