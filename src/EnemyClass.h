#include "SFML/Graphics.hpp"
#include "BonusClass.h"

using namespace sf;

class Enemy : public Entity {
public:
    Enemy(Image& image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name) {
        if (name == "EasyEnemy") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
            dx = 0.1;
        }
        if (name == "sven") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
            dx = 0.2;
        }
    }

    void checkCollisionWithMap(float, float);
    void update(float);
};

void Enemy::checkCollisionWithMap(float Dx, float Dy)
{
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if (TileMap[i][j] == '0' || TileMap[i][j] == 's')
            {
                if (Dy > 0) { y = i * 32 - h; }
                if (Dy < 0) { y = i * 32 + 32; }
                if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }
                if (Dx < 0) { x = j * 32 + 32; dx = -0.1; sprite.scale(-1, 1); }
            }
        }
}

void Enemy::update(float time) {
    if (name == "EasyEnemy") {
        moveTimer += time;
        if (moveTimer > 3000) { dx *= -1; moveTimer = 0; }
        checkCollisionWithMap(dx, 650);
        x += dx * time;
        sprite.setPosition(x + w / 2, y + h / 2);
    }
    if (name == "sven") {
        moveTimer += time;
        if (moveTimer > 1000) { dx *= -1; moveTimer = 0; }
        checkCollisionWithMap(dx, 650);
        x += dx * time;
        sprite.setPosition(x + w / 2, y + h / 2);
    }
}