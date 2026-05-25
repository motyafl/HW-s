#include <iostream>

class AudioPlayer {
public:
    virtual ~AudioPlayer() = default;
    virtual void play() const {
        std::cout << "Воспроизведение аудио" << std::endl;
    }
};

class VideoPlayer {
public:
    virtual ~VideoPlayer() = default;
    virtual void play() const {
        std::cout << "Воспроизведение видео" << std::endl;
    }
};

class MediaPlayer : public AudioPlayer, public VideoPlayer {
private:
    static int objectCount;

public:
    MediaPlayer() {
        ++(this->objectCount);
    }

    ~MediaPlayer() override {
        --(this->objectCount);
    }

    void play() const override {
        AudioPlayer::play();
        VideoPlayer::play();
    }

    friend void printMediaPlayerCount();
};

int MediaPlayer::objectCount = 0;

void printMediaPlayerCount() {
    std::cout << "Текущее количество медиаплееров: " << MediaPlayer::objectCount << std::endl;
}

int main() {
    MediaPlayer player1;
    MediaPlayer player2;

    printMediaPlayerCount();
    
    player1.play();

    return 0;
}

