#include "SFML/Graphics.hpp"
#include "class.h"

using namespace sf;

class Bonus :public Entity {
private:
    int countBonuses = 0;
public:
    Bonus(Image& image, float X, float Y, float W, float H, String Name) : Entity(image, X, Y, W, H, Name) {

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);

        countBonuses++;

        if (name == "heart") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }
        if (name == "coin") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
        }
    }

    FloatRect getRect() {
        return FloatRect(x, y, w, h);
    }
    Sprite getSprite() {
        return sprite;
    }

    int getCountBonuses() {
        return countBonuses;
    }
    void update(float);

};

void Bonus::update(float time) {
    if (name == "heart") {
        sprite.setPosition(x + w / 2, y + h / 2);
    }
    if (name == "coin") {
        sprite.setPosition(x + w / 2, y + h / 2);
    }
}