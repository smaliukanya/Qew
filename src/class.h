#include <SFML/Graphics.hpp>

using namespace sf;

class Player;
class Enemy;

class Entity {
public:
    float dx, dy, x, y, speed, moveTimer;
    int w, h, health;
    bool life, onGround;
    String name;
    Texture texture;
    Sprite sprite;
    Entity(Image &image, float X, float Y, float W, float H, String Name) {
        w = W; h = H; x = X; y = Y; health = 100; name = Name;
        life = true; onGround = false; moveTimer = 0; speed = 0;
        dx = 0; dy = 0;


        image.createMaskFromColor(Color(255, 255, 255));
        image.createMaskFromColor(Color(255, 201, 13));

        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setOrigin(w / 2, h / 2);
    }

    FloatRect getRect() {
        return FloatRect(x, y, w, h);
    }
    //virtual void update();
};

class Player: public Entity{
public:
    float CurrentFrame = 0;
    enum {left, right, up, down, jump, stay} state;
    int score;

    Player(Image &image, float X, float Y, float W, float H, String Name):Entity(image, X, Y, W, H, Name) {
        score = 0;
        state = stay;
        if (name == "player2") {
            sprite.setTextureRect(IntRect(0, 100, w, h));
        }
    }
    void update(float);

    void checkCollisionWithMap(float, float);
    void control(float);
};

class Enemy : public Entity {
public:
    Enemy(Image& image, float X, float Y, float W, float H, String Name) :Entity(image, X, Y, W, H, Name) {
        if (name == "EasyEnemy") {
            sprite.setTextureRect(IntRect(0, 0, w, h));
            dx = 0.1;
        }
    }
    void checkCollisionWithMap2(float, float);
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
    if (health <= 0) life = false;
    dy = dy + 0.0015 * time;
    checkCollisionWithMap(0, dy);
    //if (life == true) {
    //    getCoordinatView(x, y);
    //}

}

void Player::checkCollisionWithMap(float Dx, float Dy){
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (Dy > 0) { y = i * 32 - h;  dy = 0; onGround = true; }
                if (Dy < 0) { y = i * 32 + 32;  dy = 0; }
                if (Dx > 0) { x = j * 32 - w; }
                if (Dx < 0) { x = j * 32 + 32; }
            }
            //else { onGround = false; }//надо убрать т.к мы можем находиться и на другой поверхности или платформе которую разрушит враг
        }
}
 
void Player::control(float time) {
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        state = left;
        speed = 0.2;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4) CurrentFrame = 0;
        sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 300, 85, 75));
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        state = right;
        speed = 0.2;
        CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4) CurrentFrame = 0;
        sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 110, 85, 75));
    }
    if (Keyboard::isKeyPressed(Keyboard::W) && (onGround)) {
        state = jump;
        dy = -0.5; onGround = false;
       /* CurrentFrame += 0.005 * time;
        if (CurrentFrame > 3) CurrentFrame = 0;
        player2.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 200, 100, 90));*/
    }

    if (Keyboard::isKeyPressed(Keyboard::S)) {
        state = down;
        speed = 0.2;
        /*CurrentFrame += 0.005 * time;
        if (CurrentFrame > 4) CurrentFrame = 0;
        player2.sprite.setTextureRect(IntRect(100 * int(CurrentFrame), 0, 100, 90));*/
    }
}

void Enemy::checkCollisionWithMap2(float Dx, float Dy)
{
    for (int i = y / 32; i < (y + h) / 32; i++)
        for (int j = x / 32; j < (x + w) / 32; j++)
        {
            if (TileMap[i][j] == '0')
            {
                if (Dy > 0) { y = i * 32 - h; }
                if (Dy < 0) { y = i * 32 + 32; }
                if (Dx > 0) { x = j * 32 - w; dx = -0.1; sprite.scale(-1, 1); }
                if (Dx < 0) { x = j * 32 + 32; dx = 0.1; sprite.scale(-1, 1); }
            }
        }
}

void Enemy::update(float time) {
    if (name == "EasyEnemy") {
        moveTimer += time;
        if (moveTimer > 3000) { dx *= -1; moveTimer = 0; }
        checkCollisionWithMap2(dx, 650);
        x += dx * time;
        sprite.setPosition(x + w / 2, y + h / 2);
        if (health <= 0) life = false;
    }
}