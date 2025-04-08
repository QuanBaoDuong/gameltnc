#ifndef _MUSIC_H
#define _MUSIC_H

#include "graphics.h"
#include <SDL_mixer.h>
#include <iostream>

class Music {
public:
    Music();
    ~Music();
    void backgroundMusic();
    void snakeCollision();
    void snake_eating();
private:
    Mix_Music* bgMusic;
    Mix_Chunk* snakecollision;
    Mix_Chunk* snakeEating;
};

#endif // _MUSIC_H
