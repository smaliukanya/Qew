#include "SFML/Graphics.hpp"
#include <vector>
#include "iostream"
#include "view.h"
#include "SoundsManager.h"
#include "map.h"

using namespace sf;

class Player;
class Enemy;
class Bonus;

class Entity {
public:
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, onGround;
    String name;
    Texture texture;
    Sprite sprite;
    Image image1;
    Entity(Image& image, float X, float Y, float W, float H, String Name) {
        image1 = image;
        w = W; h = H; x = X; y = Y; health = 100; name = Name;
        life = true; onGround = true; moveTimer = 0; speed = 0;
        dx = 0; dy = 0;


        image.createMaskFromColor(Color(179, 179, 179));

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }
};