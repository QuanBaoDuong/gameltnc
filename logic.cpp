#include "logic.h"


Logic::Logic(Graphics& graphics) {
    lastMoveTime = SDL_GetTicks();

    loadHighScore();

    segments.push_back({400,260,Headsnake,Headsnake});
    segments.push_back({380,260,Bodysnake,Bodysnake});
    segments.push_back({360,260,Bodysnake,Bodysnake});
    directionX=20;
    directionY=0;



}

void Logic::movesnake() {
    SDL_Rect newhead=segments[0];
    newhead.x+=directionX;
    newhead.y+=directionY;
    segments.insert(segments.begin(),newhead);
    if(!randApple) {
    segments.pop_back();
    }

}
void Logic::handleInput(int& directionX, int& directionY,double &angle) {

    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if(e.type==SDL_QUIT) {
            running=false;
            SDL_Quit();
        }
        else if(e.type==SDL_KEYDOWN) {
            switch(e.key.keysym.sym) {
            case SDLK_UP :
                if (directionY==0) {
                    directionX=0;
                    directionY=-20;
                    angle=270;
                }
                break;
            case SDLK_DOWN :
                if (directionY==0) {
                    directionX=0;
                    directionY=20;
                    angle=90;
                }
                break;
            case SDLK_LEFT :
                if (directionX==0) {
                    directionX=-20;
                    directionY=0;
                    angle=180;
                }
                break;
            case SDLK_RIGHT :
                if (directionX==0) {
                    directionX=20;
                    directionY=0;
                    angle=0;
                }
                break;
            case SDLK_ESCAPE :
                running =false;
                break;
            default :
                break;
            }
        }
    }
}
bool Logic::impact(int x,int y) {
    border2.push_back({0,0,20,60});
    border2.push_back({0,0,60,20});
    SDL_Rect head=segments[0];
    if (x>=300&&x<300+border2[0].w&&(y>=180&&y<180+border2[0].h||y>=300&&y<300+border2[0].h)||
        x>=300&&x<300+border2[1].w&&(y>=180&&y<180+border2[1].h||y>=340&&y<340+border2[1].h)||
        x>=480&&x<480+border2[0].w&&(y>=300&&y<300+border2[0].h||y>=180&&y<180+border2[0].h)||
        x>=440&&x<440+border2[1].w&&(y>=340&&y<340+border2[1].h||y>=180&&y<180+border2[1].h)||
        x>=780||y>=520||x<20||y<20) {
        return true;
    }
    return false;
}
void Logic::generateApple(int *apple_location) {
    apple_location[0]=20+rand() % (760/20)*20;
    apple_location[1]=20+rand() % (500/20)*20;
    bool appleCoincidesWithTheWall=false;
    if (impact(apple_location[0],apple_location[1])) {
    appleCoincidesWithTheWall=true;
    }
    while(appleCoincidesWithTheWall) {
        apple_location[0]=20+rand() % (760/20)*20;
        apple_location[1]=20+rand() % (500/20)*20;
        if (!impact(apple_location[0],apple_location[1])) {
            appleCoincidesWithTheWall=false;
        }
    }
}
bool Logic::tailBite() {
    for (int i=1;i<(int)segments.size();i++) {
        if (segments[0].x==segments[i].x&&segments[0].y==segments[i].y) {
            return true;

        }
    }
    return false;
}
void Logic::saveHighScore() {
    std::ofstream out("highscore.txt");
    if (out.is_open()) {
        out << highScore;
        out.close();
    }
}

void Logic::loadHighScore() {
    std::ifstream in("highscore.txt");
    if (in.is_open()) {
        in >> highScore;
        in.close();
    }
}

double Logic::getAngle() const {
    return angle;
}
void Logic::runLogic (Graphics& graphics) {

    Uint32 currentTime = SDL_GetTicks();
    if (currentTime-lastMoveTime >= moveDelay) {
    handleInput(directionX,directionY,angle);
    movesnake();
    if (randApple) {
        generateApple(apple_location);
    }
    if(segments[0].x==apple_location[0]&&segments[0].y==apple_location[1]) {
        if (musicgame) {
            music.snake_eating();
        }
        score++;

        if (score > highScore) {
            highScore=score;
            saveHighScore();
        }
    }

    for (int i=0;i<(int)segments.size();i++){
        if(segments[i].x==apple_location[0]&&segments[i].y==apple_location[1]) {
            randApple=true;
            break;
        }
        else {
            randApple=false;
        }
    }
    lastMoveTime = currentTime;
  }

}
