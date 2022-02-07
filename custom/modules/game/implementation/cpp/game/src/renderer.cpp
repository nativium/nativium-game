#include "renderer.hpp"
#include "platforms.hpp"

#include "SDL_image.h"

#include <iostream>
#include <string>

Renderer::Renderer(const int32_t screen_width, const int32_t screen_height, const int32_t grid_width, const int32_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create window
    int windowFlags = 0;
    bool useFullScreen = false;

#ifdef NATIVIUM_TARGET_MOBILE
    windowFlags |= SDL_WINDOW_FULLSCREEN;
#else
    windowFlags |= SDL_WINDOW_SHOWN;
#endif

    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, windowFlags);

    if (nullptr == sdl_window)
    {
        std::cerr << "Window could not be created.\n";
        std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (nullptr == sdl_renderer)
    {
        std::cerr << "Renderer could not be created.\n";
        std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Initialize image
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
}

Renderer::~Renderer()
{
    std::cout << "Renderer was destroyed" << std::endl;
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, SDL_Texture *logo)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    // Feature: Same width in all screens
    block.h = block.w;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x10, 0x15, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render food
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    // Render snake's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    for (SDL_Point const &point : snake.body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render snake's head
    block.x = static_cast<int>(snake.head_x) * block.w;
    block.y = static_cast<int>(snake.head_y) * block.h;

    if (snake.alive)
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    }
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
    }

    SDL_RenderFillRect(sdl_renderer, &block);

    // Render logo
    SDL_Rect dstrect = {static_cast<int>((screen_width / 2) - 64), static_cast<int>((screen_height / 2) - 64), 128, 128};
    SDL_RenderCopy(sdl_renderer, logo, nullptr, &dstrect);

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
    std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

SDL_Renderer *Renderer::getSDLRenderer()
{
    return sdl_renderer;
}

SDL_Window *Renderer::getSDLWindow()
{
    return sdl_window;
}

const int32_t Renderer::getScreenWidth()
{
    return screen_width;
}

const int32_t Renderer::getScreenHeight()
{
    return screen_height;
}
