#ifndef MENU_H
#define MENU_H

#include "graphics.h"
#include "snake.h"
#include "music.h"
class Menu {
public:
    Menu(SDL_Renderer* renderer,Graphics& graphics);
    ~Menu();
    void runMenu();
    int showMenu();
private:
    SDL_Renderer* renderer;

    std::vector<std::string> menuItems;
    int selectedItem;
    std::vector<SDL_Rect> itemRects;

    void renderMenu();
    void handleEvent(SDL_Event& e, bool& running);
    SDL_Rect locationbuttonmusic={30,30,40,40};

    Graphics graphics;
};

#endif
