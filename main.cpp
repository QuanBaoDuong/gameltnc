#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "menu.h"
#include "music.h"
using namespace std;


int main (int argc, char* argv[]) {
    Graphics graphics;
    graphics.init();
    Menu menu(graphics.renderer, graphics);

    menu.runMenu();

    return 0;
}
