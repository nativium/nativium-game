#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>

#include "SDL.h"
#include "SDL_image.h"

#include "context.hpp"
#include "controller.hpp"
#include "player.hpp"
#include "renderer.hpp"
#include "snake.hpp"

class Game
{
public:
    Game(int32_t grid_width, int32_t grid_height, int mode);
    ~Game();
    void Run(const std::shared_ptr<Renderer> &renderer, const std::shared_ptr<Controller> &controller, int32_t targetFrameDuration);
    void Loop();
    int GetScore() const;
    int GetSize() const;

    static void WebLoop(void *funcPtr);

private:
    std::shared_ptr<Context> context;
    std::shared_ptr<Player> player;
    Snake snake;
    SDL_Point food;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;

    int score{0};

    SDL_Texture *logo;

    void PlaceFood();
    void Update();
    void SetPlayer();
};

#endif
