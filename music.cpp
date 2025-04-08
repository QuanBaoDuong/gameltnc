#include "music.h"

Music::Music() {
    if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0) {
        std::cout << "Khong the tai nhac ! LOi :" <<Mix_GetError() << std::endl;
        return ;
    }
    bgMusic=Mix_LoadMUS("music_snake.mp3");
    if (!bgMusic) {
        std::cout << "Khong the tai nhac ! LOi :" <<Mix_GetError() << std::endl;
    }
    snakeEating=Mix_LoadWAV("snake_eating.wav");
    if (!snakeEating) {
        std::cout << "Khong the tai nhac ! LOi :" <<Mix_GetError() << std::endl;
    }
    snakecollision=Mix_LoadWAV("snake_collision.mp3");
    if (!snakecollision) {
        std::cout << "Khong the tai nhac ! LOi :" <<Mix_GetError() << std::endl;
    }
}

void Music::backgroundMusic () {
    if (bgMusic) {
    Mix_PlayMusic(bgMusic,-1);
    }

}
void Music::snakeCollision() {
    if(snakecollision) {
        Mix_PlayChannel(-1,snakecollision,0);
    }
}
void Music::snake_eating() {
    if(snakeEating) {
    Mix_PlayChannel(-1,snakeEating,0);

    }
}
Music:: ~Music() {
    if (bgMusic) {
        Mix_FreeMusic(bgMusic);
        bgMusic=nullptr;
    }
    if (snakeEating) {
        Mix_FreeChunk(snakeEating);
        snakeEating=nullptr;
    }
    if (snakecollision) {
        Mix_FreeChunk(snakecollision);
        snakecollision=nullptr;
    }
    Mix_CloseAudio();
}
