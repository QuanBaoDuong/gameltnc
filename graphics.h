#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include <SDL_ttf.h>
struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error);
	void init(); // Khởi tạo
	SDL_Renderer* getRenderer();//Trả renderer
	void prepareScene(SDL_Texture * background);//Xóa màn hình và vẽ hình nền mới.
    void presentScene();//Hiển thị nội dung đã vẽ lên màn hình.
    SDL_Texture *loadTexture(const char *filename); // load ảnh
    void renderTexture(SDL_Texture *texture, int x, int y); //Vẽ một texture lên màn hình tại vị trí (x, y).
    void blitRect(SDL_Texture *texture,SDL_Rect* src, int x, int y);//Cắt một phần của texture và vẽ lên màn hình tại vị trí (x, y).
    void blitRect1(SDL_Texture *texture,SDL_Rect* src, int x, int ,double angle,SDL_Point center);
    void drawText(const std::string& message, int x, int y, SDL_Color color);
    void quit();
};

#endif // _GRAPHICS__H
