#ifndef _SNAKE__H
#define _SNAKE__H

#include "graphics.h"
#include <vector>
#include "defs.h"
#include "logic.h"
class Snake{
public:
    Snake(Graphics& graphics);
    ~Snake();
    void render (Graphics& graphics,std::vector<SDL_Rect>border, std::vector<SDL_Rect>& segments,double angle,int* apple_location,int score,int highscore);
    SDL_Texture* gameover;
    void resnake (Graphics& graphics);
private:
    SDL_Texture* headsnake;
    SDL_Texture* bodysnake;
    SDL_Texture* tailsnake;
    SDL_Texture* background;
    SDL_Texture* border;
    SDL_Texture* border1;
    SDL_Texture* apple;

    int directionX,directionY;
    SDL_Point center;
    Music music;

};

#endif
