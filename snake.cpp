#include "snake.h"

#include <iostream>
Snake::Snake(Graphics& graphics) {
    headsnake=graphics.loadTexture("snake2.png");
    bodysnake=graphics.loadTexture("body2.png");
    tailsnake=bodysnake;

    border=graphics.loadTexture("border.png");
    border1=graphics.loadTexture("border1.png");

    background=graphics.loadTexture("grey2.png");

    apple=graphics.loadTexture("apple.png");

    gameover=graphics.loadTexture("game_over.png");

    center={Headsnake/2,Headsnake/2};
}
Snake::~Snake() {
    SDL_DestroyTexture(headsnake);
    SDL_DestroyTexture(bodysnake);
    SDL_DestroyTexture(tailsnake);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(border);
    SDL_DestroyTexture(border1);
    SDL_DestroyTexture(apple);
    SDL_DestroyTexture(gameover);
}

void Snake::render(Graphics& graphics,std::vector<SDL_Rect>border2, std::vector<SDL_Rect>& segments,double angle,int *apple_location,int score,int highscore) {

    graphics.prepareScene(background);

    graphics.renderTexture(border,0,0);
    graphics.renderTexture(border,0,520);
    graphics.renderTexture(border1,0,0);
    graphics.renderTexture(border1,780,0);

    graphics.blitRect(border1,&border2[0],300,180);
    graphics.blitRect(border,&border2[1],300,180);
    graphics.blitRect(border1,&border2[0],300,300);
    graphics.blitRect(border,&border2[1],300,340);
    graphics.blitRect(border1,&border2[0],480,300);
    graphics.blitRect(border,&border2[1],440,340);
    graphics.blitRect(border1,&border2[0],480,180);
    graphics.blitRect(border,&border2[1],440,180);

    SDL_Rect apple1={0,0,20,20};
    graphics.blitRect(apple,&apple1,apple_location[0],apple_location[1]);


    for (int i=1;i<(int)segments.size()-1;i++) {
    graphics.blitRect1(bodysnake,&segments[i],segments[i].x,segments[i].y,angle,center);
    }
    graphics.blitRect1(tailsnake,&segments[2],segments[2].x,segments[2].y,angle,center);

    graphics.blitRect1(headsnake,&segments[0],segments[0].x,segments[0].y,angle,center);

    std::string scoreText = "Score: " + std::to_string(score);
    std::string highScoreText = "High Score: " + std::to_string(highscore);

    graphics.drawText(scoreText,100, 550, textColor);
    graphics.drawText(highScoreText, 500, 550,highlightColor);      // vàng


    graphics.presentScene();


}


void Snake::resnake(Graphics& graphics) {

    Logic logic(graphics);

    running = true;

    Uint32 startTime = SDL_GetTicks();

    while(running) {

            Uint32 frameStart = SDL_GetTicks();

            if (!logic.impact(logic.segments[0].x,logic.segments[0].y)||!logic.tailBite()) {
                running=false;
                break;
            }
            logic.runLogic(graphics);

            double angle=logic.getAngle();
            render(graphics,logic.border2,logic.segments,angle,logic.apple_location,logic.score,logic.highScore);

            Uint32 frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay-frameTime);
            }
    }
    if (!running) {
        if (musicgame) {
            music.snakeCollision();
        }
        graphics.renderTexture(gameover,300,200);
        graphics.presentScene();
    }

}

