#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "SDL.h"
#include "SDL_image.h"

#include "snake.hpp"

class Renderer
{
public:
    Renderer(const int32_t screen_width, const int32_t screen_height, const int32_t grid_width, const int32_t grid_height);
    ~Renderer();

    void Render(Snake const snake, SDL_Point const &food, SDL_Texture *logo);
    void UpdateWindowTitle(int score, int fps);
    SDL_Renderer *getSDLRenderer();
    SDL_Window *getSDLWindow();
    const int32_t getScreenWidth();
    const int32_t getScreenHeight();

private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const int32_t screen_width;
    const int32_t screen_height;
    const int32_t grid_width;
    const int32_t grid_height;
};

#endif
