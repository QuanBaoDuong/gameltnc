#ifndef _GAME__H
#define _GAME__H

#include "graphics.h"
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "music.h"
#include <fstream>

class Logic {
public:
    Logic(Graphics& graphics);
    void movesnake();
    void moveerror();
    void handleInput(int& directionX, int& directionY,double& angle);
    void runLogic(Graphics& graphics);
    double getAngle() const ;
    bool tailBite();
    void generateApple (int *apple_location);
    void saveHighScore();
    void loadHighScore();
    bool impact(int x,int y);
    std:: vector <SDL_Rect>segments;
    std:: vector <SDL_Rect>border2;
    int apple_location[2];
    int score=0;
    int highScore=0;

private:
    int directionX,directionY;
    int amount_eaten=0;
    bool randApple=true;
    double angle=0;

    SDL_Point center;
    std::string currentDirection;


    std::vector <std::string>scoreItem;
    std::vector<SDL_Rect> itemRects;
    Music music;
    Uint32 lastMoveTime;
};

#endif // _GAME__H
