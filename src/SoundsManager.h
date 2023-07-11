#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager {
private:
    Music music;
    Music menuMusic;
    SoundBuffer gameOver;
    SoundBuffer hitBuffer;
    SoundBuffer soundBuffer;
    SoundBuffer heartBuffer;
    SoundBuffer diedSoundBuffer;
    SoundBuffer jumpBuffer;
    Sound jumpSound;
    Sound diedSound;
    Sound endGameSound;
    Sound sound;
    Sound heart;
    Sound hit;
public:
    void loadingSounds() {
        soundBuffer.loadFromFile("sounds/coin.ogg");
        sound.setBuffer(soundBuffer);

        heartBuffer.loadFromFile("sounds/heart.ogg");
        heart.setBuffer(heartBuffer);

        hitBuffer.loadFromFile("sounds/hit.ogg");
        hit.setBuffer(hitBuffer);

        gameOver.loadFromFile("sounds/GameOver.ogg");
        endGameSound.setBuffer(gameOver);

        diedSoundBuffer.loadFromFile("sounds/died.ogg");
        diedSound.setBuffer(diedSoundBuffer);

        jumpBuffer.loadFromFile("sounds/jump.ogg");
        jumpSound.setBuffer(jumpBuffer);
    }
    void playMenuMusic(){
        menuMusic.openFromFile("sounds/empty-hallways.ogg");
        menuMusic.setVolume(20);
        menuMusic.setLoop(true);
        menuMusic.play();
    }
    void endMenuMusic() {
        menuMusic.stop();
    }
    void playBackgroundMusic() {
        music.openFromFile("sounds/music.ogg");
        music.setVolume(20);
        music.setLoop(true);
        music.play();
    }
    void endBackgroundMusic() {
        music.stop();
    }
    void playCoinSound() {
        sound.setVolume(100);
        sound.play();
    }
    void playJumpSound() {
        jumpSound.setVolume(30);
        jumpSound.play();
    }
    void playHitSound() {
        hit.setVolume(100);
        hit.play();
    }
    void playHeartSound() {
        heart.setVolume(100);
        heart.play();
    }
    void playDiedSound() {
        diedSound.setVolume(100);
        diedSound.play();
    }
    void playGameOverSound() {
        endGameSound.setLoop(false);
        endGameSound.setVolume(100);
        if (endGameSound.getStatus() == sf::Sound::Playing) {}
        else { endGameSound.play(); }
    }
    void stopGameOverSound() {
        endGameSound.stop();
    }
};