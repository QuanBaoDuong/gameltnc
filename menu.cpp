#include "menu.h"
#include <iostream>


Menu::Menu(SDL_Renderer* renderer,Graphics& p_graphics) : renderer(renderer), selectedItem(-1) {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
        exit(1);
    }

    graphics=p_graphics;


    menuItems = {"PLAY", "HOW TO PLAY", "EXIT"};

    int yOffset = 300;
    for (size_t i = 0; i < menuItems.size(); i++) {
        SDL_Rect rect = {200, yOffset + (int)i * 60, 200, 40};
        itemRects.push_back(rect);
    }
}

Menu::~Menu() {
    TTF_Quit();
}

void Menu::renderMenu() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);


    for (int i = 0; i < (int)menuItems.size(); i++) {
        SDL_Color color = (i == selectedItem) ? highlightColor : textColor;

        graphics.drawText(menuItems[i],itemRects[i].x,itemRects[i].y,color);

    }

    SDL_RenderPresent(renderer);
}

void Menu::handleEvent(SDL_Event& e, bool& running) {
    if (e.type == SDL_QUIT) {
        SDL_Quit();
    } else if (e.type == SDL_MOUSEMOTION) {
        int mouseX = e.motion.x;
        int mouseY = e.motion.y;

        selectedItem = -1;
        for (int i = 0; i < (int)menuItems.size(); i++) {
            if (mouseX >= itemRects[i].x && mouseX <= itemRects[i].x + itemRects[i].w &&
                mouseY >= itemRects[i].y && mouseY <= itemRects[i].y + itemRects[i].h) {
                selectedItem = i;
                break;
            }
        if (mouseX>=locationbuttonmusic.x&& mouseX<=locationbuttonmusic.x+locationbuttonmusic.w &&
            mouseY>=locationbuttonmusic.y&& mouseY<=locationbuttonmusic.y+locationbuttonmusic.h) {
                selectedItem = -2;
            }
        }
    }  else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
        if (selectedItem != -1) {
            running = false;
        }
    }
}

int Menu::showMenu() {
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            handleEvent(e, running);
        }
        renderMenu();


        SDL_Delay(16);
    }

    return selectedItem;
}
void Menu::runMenu() {
    Snake snake(graphics);
    bool running = true;
    Music music;
    SDL_Init(SDL_INIT_AUDIO);

        SDL_Texture* background = graphics.loadTexture("background_snake.jpg");
        SDL_Texture* logo=graphics.loadTexture("logosnake.png");
        SDL_Texture* HOWTOPLAY = graphics.loadTexture("HUONGDAN.png");
        SDL_Texture* backButton= graphics.loadTexture("back.jpg");
        SDL_Texture* buttonmusicOn=graphics.loadTexture("musicon.png");
        SDL_Texture* buttonmusicOff=graphics.loadTexture("musicoff.png");

        bool musicplaying=false;

    while (running) {
        graphics.prepareScene(background);
        graphics.renderTexture(logo,200,50);
        if (musicgame && !musicplaying) {
            graphics.renderTexture(buttonmusicOn,locationbuttonmusic.x,locationbuttonmusic.y);
            music.backgroundMusic();
        }
        else if (!musicgame&& musicplaying){
            graphics.renderTexture(buttonmusicOff,locationbuttonmusic.x,locationbuttonmusic.y);
            Mix_HaltMusic();

        }


        graphics.presentScene();


        int choice = this->showMenu();

        switch (choice) {
            case -2 :
                    musicgame=!musicgame;
                    musicplaying=!musicplaying;
                    break;
            case 0:{
                SDL_RenderClear(graphics.getRenderer());
                snake.resnake(graphics);
                SDL_Rect cut = {10,10,30,30};
                SDL_Rect backRect = {10, 10, 30, 30};
                graphics.blitRect(backButton,&cut,backRect.x,backRect.y);
                graphics.presentScene();

                SDL_Event e;
                bool Play = true;

                while (Play && SDL_WaitEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        SDL_Quit();
                }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;

                    if (mouseX >= backRect.x && mouseX <= backRect.x + backRect.w &&
                        mouseY >= backRect.y && mouseY <= backRect.y + backRect.h) {
                        Play = false;
                    }
                }
            }
                SDL_RenderClear(graphics.getRenderer());

                break;
            }



            case 1: {

                SDL_Rect cut = {10,10,30,30};
                SDL_Rect backRect = {10, 10, 30, 30};
                graphics.prepareScene(HOWTOPLAY);
                graphics.blitRect(backButton,&cut,backRect.x,backRect.y);
                graphics.presentScene();

                SDL_Event e;
                bool inHOWTOPLAY = true;

                while (inHOWTOPLAY && SDL_WaitEvent(&e)) {
                    if (e.type == SDL_QUIT) {
                        SDL_Quit();
                }
                    else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                        int mouseX = e.button.x;
                        int mouseY = e.button.y;

                    if (mouseX >= backRect.x && mouseX <= backRect.x + backRect.w &&
                        mouseY >= backRect.y && mouseY <= backRect.y + backRect.h) {
                        inHOWTOPLAY = false;
                    }
                }
            }
                SDL_RenderClear(graphics.getRenderer());

                break;
            }

            case 2:
                running = false;
                break;
            default:
                continue;
                break;
        }

    }
        SDL_DestroyTexture(background);
        SDL_DestroyTexture(logo);
        SDL_DestroyTexture(HOWTOPLAY);
        SDL_DestroyTexture(backButton);
        SDL_DestroyTexture(buttonmusicOn);
        SDL_DestroyTexture(buttonmusicOff);
}
