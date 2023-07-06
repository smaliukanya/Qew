#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager{
private:
    Music music;
    SoundBuffer gameOver;
    SoundBuffer soundBuffer;
    SoundBuffer heartBuffer;
    Sound endGame;
    Sound sound;
    Sound heart;
public:
    SoundManager(){
        soundBuffer.loadFromFile("sounds/coin.wav");
        sound.setBuffer(soundBuffer);
        
        heartBuffer.loadFromFile("sounds/heart.ogg");
        heart.setBuffer(heartBuffer);

        gameOver.loadFromFile("sounds/GameOver.ogg");
        endGame.setBuffer(gameOver);
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
    void playHeartSound() {
        heart.setVolume(100);
        heart.play();
    }
    void playGameOverSound() {
        endGame.setVolume(100);
        endGame.play();
    }
    int playingSound() {
        if (endGame.getStatus() == sf::Sound::Playing)
        {
            return 1;
        }
        else break;
    }
};