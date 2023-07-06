//классы и их методы

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

    FloatRect getRect() {
        return FloatRect(x, y, w, h);
    }
    //virtual void update();
};

class Player : public Entity { //класс персонажа
private:
    float CurrentFrame = 0;
    enum { left, right, up, down, jump, stay } state;
    int score;
    bool isCollision = false;
    SoundManager sound;
public:
    void operator =(const Player& temp) {
        this->image1 = temp.image1;
        texture.loadFromImage(image1);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }

    Player(Image& image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name) {
        score = 0;
        state = stay;
        if (name == "player2") {
            sprite.setTextureRect(IntRect(0, 135, w, h));
        }
    }
    void update(float);

    void checkCollisionWithMap(float, float);
    void control(float);
    void checkCollisionWithBonus();
    void clear();

    void interactionWithEnemy();

    std::vector<Bonus*> bonus;
    std::vector<Enemy*> enemy;
    int setScore() {
        return score;
    }
    int getScore(int score1) {
        score = score1;
        return score;
    }
};

class Bonus :public Entity { //класс бонусов
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

class Enemy : public Entity { //класс врагов
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

void Player::update(float time) {
    control(time);
    switch (state) {
    case right: dx = speed; break;
    case left: dx = -speed; break;
    case up: break;
    case down: break;
    case jump: break;
    case stay: break;
    }

    x += dx * time;
    checkCollisionWithMap(dx, 0);
    y += dy * time;
    checkCollisionWithMap(0, dy);
    speed = 0;
    //sprite.setPosition(x, y);
    sprite.setPosition(x + w / 2, y + h / 2);
    if (health <= 0) {
        life = false;
    }
    dy = dy + 0.0015 * time;
    checkCollisionWithMap(0, dy);
    checkCollisionWithBonus();
    interactionWithEnemy();
    if (life == true) {
        getCoordinatPlayerView(x, y);
    }

}

void Player::checkCollisionWithMap(float Dx, float Dy) { //взаимодействие персонажа с картой
    //столкновение с элементами карты и проверка на выход за пределы массива по х
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if (TileMap[i][j] == '0' || TileMap[i][j] == 's' || x < 32 || x > 2464)
            {
                if (Dy > 0) { y = i * 32 - h;  dy = 0; onGround = true; }
                if (Dy < 0) { y = i * 32 + 32;  dy = 0; }
                if (Dx > 0) { x = j * 32 - w; }
                if (Dx < 0) { x = j * 32 + 32; }
            }
        }
    //std::cout << "y: " << y << "Dx " << Dx << std::endl;
    if (y > 600) {
        health = 0;
        y = 550;
        x = 128;
    }
}

void Player::checkCollisionWithBonus() { //взаимодействие персонажа с бонусами
    for (auto it{ 0 }; it < bonus.size(); ++it)
    {
        if (sprite.getGlobalBounds().intersects(bonus[it]->sprite.getGlobalBounds())) {
            if (bonus[it]->name == "heart") {
                health += 10;
                sound.playHeartSound();
            }
            else if (bonus[it]->name == "coin") {
                score++;
                sound.playCoinSound();
            }
            bonus.erase(bonus.begin() + it);
        }
    }
}

void Player::interactionWithEnemy() {
    Clock collisionTimer;
    float distanceThreshold = 200;
    for (auto it{ 0 }; it < enemy.size(); ++it)
    {
        if (sprite.getGlobalBounds().intersects(enemy[it]->sprite.getGlobalBounds()))
        {
            //if (!isCollision)
            //{
            //    isCollision = true;
            //    sprite.setColor(sf::Color::Red);
            //    collisionTimer.restart();
            //}
            if (enemy[it]->name == "EasyEnemy") {
                if (!onGround) {
                    enemy[it]->dx = 0; dy = -0.4; enemy[it]->health = 0;
                    sound.playDiedSound();
                    enemy.erase(enemy.begin() + it);
                }
                else {
                    sound.playHitSound();
                    health -= 50;

                    if (enemy[it]->dx > 0)
                    {
                        enemy[it]->dx *= -1;
                        enemy[it]->x = -x - enemy[it]->w;

                    }
                    if (enemy[it]->dx < 0)
                    {
                        enemy[it]->x = x + w;
                        enemy[it]->dx *= -1;
                    }
                    if (dx < 0) {
                        x -= 40;
                    }
                    if (dx > 0) {
                        x -= 40;
                    }

                }
            }
            if (enemy[it]->name == "sven") {
                enemy[it]->sprite.setColor(sf::Color::Red);
                sf::Vector2f playerPosition = sprite.getPosition();
                sf::Vector2f enemyPosition = enemy[it]->sprite.getPosition();
            }
        }
        else
        {
            if (isCollision && collisionTimer.getElapsedTime().asSeconds() >= 1)
            {
                isCollision = false;
                sprite.setColor(sf::Color::White);
            }
        }
    }
}

void Player::clear() { //освобождение памяти 
    for (auto it = bonus.begin(); it != bonus.end(); ++it) {
        delete* it;
    }
    bonus.clear();
    for (auto it = enemy.begin(); it != enemy.end(); ++it) {
        delete* it;
    }
    enemy.clear();
}


void Player::control(float time) {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        state = left;
        speed = 0.2;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4) CurrentFrame = 0;
        sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 0, 65, 135));
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        state = right;
        speed = 0.2;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4) CurrentFrame = 0;
        sprite.setTextureRect(IntRect(63 * int(CurrentFrame), 263, 63, 135));
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && (onGround)) {
        state = jump;
        sound.playJumpSound();
        //sprite.setTextureRect(IntRect(65 * int(CurrentFrame), 160, 110, 145));
        dy = -0.55; onGround = false;
    }

    if (Keyboard::isKeyPressed(Keyboard::S)) {
        state = down;
        speed = 0.2;
    }
}

void Enemy::checkCollisionWithMap(float Dx, float Dy) //взаимодействие врагов с картой
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
        /*if (health <= 0) life = false;*/
    }
    if (name == "sven") {
        moveTimer += time;
        if (moveTimer > 1000) { dx *= -1; moveTimer = 0; }
        checkCollisionWithMap(dx, 650);
        x += dx * time;
        sprite.setPosition(x + w / 2, y + h / 2);
    }
}