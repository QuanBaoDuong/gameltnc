#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH=800;
const int SCREEN_HEIGHT=600;
inline const char* WINDOW_TITLE="SnakeGame";

inline bool running = true;
inline bool musicgame=true;

const int FPS=60;
const int frameDelay=1000/60;

const int moveDelay=70;

const SDL_Color textColor = {255, 255, 255};
const SDL_Color highlightColor = {255, 0, 0};

#define GRID 20
#define Headsnake 20
#define Bodysnake 20
#define Tailsnake 20
#define Apple 20


#endif
