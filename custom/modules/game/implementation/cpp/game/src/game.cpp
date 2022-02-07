#include "game.hpp"

#include "SDL.h"
#include "SDL_image.h"

#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

Game::Game(int32_t grid_width, int32_t grid_height, int mode)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width) - 1),
      random_h(0, static_cast<int>(grid_height) - 1),
      context(std::make_shared<Context>())
{
    if (mode == 2)
    {
        SetPlayer();
    }

    PlaceFood();
}

Game::~Game()
{
    std::cout << "Game was destroyed" << std::endl;
    SDL_DestroyTexture(logo);
}

void Game::SetPlayer()
{
    player = std::make_shared<Player>(&snake, &food);
}

void Game::Run(const std::shared_ptr<Renderer> &renderer, const std::shared_ptr<Controller> &controller, int32_t targetFrameDuration)
{
    context->renderer = renderer;
    context->controller = controller;
    context->targetFrameDuration = targetFrameDuration;

    context->running = true;
    context->titleTimestamp = SDL_GetTicks();
    context->frameCount = 0;

    SDL_Surface *image = IMG_Load("assets/logo.png");
    logo = SDL_CreateTextureFromSurface(renderer->getSDLRenderer(), image);

#ifdef __EMSCRIPTEN__
    const int simulateInfiniteLoop = 1; // call the function repeatedly
    const int fps = -1;                 // call the function as fast as the browser wants to render (typically 60fps)

    emscripten_set_main_loop_arg(Game::WebLoop, this, fps, simulateInfiniteLoop);

    std::cout << "Main loop ended" << std::endl;
#else
    while (context->running)
    {
        Loop();
    }

    std::cout << "Main loop ended" << std::endl;
#endif
}

void Game::WebLoop(void *funcPtr)
{
    static_cast<Game *>(funcPtr)->Loop();
}

void Game::Loop()
{
    context->frameStart = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    if (player)
    {
        player->play();
    }

    context->controller->HandleInput(context, snake);
    Update();
    context->renderer->Render(snake, food, logo);

    context->frameEnd = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    context->frameCount++;
    context->frameDuration = context->frameEnd - context->frameStart;

    // After every second, update the window title.
    if (context->frameEnd - context->titleTimestamp >= 1000)
    {
        context->renderer->UpdateWindowTitle(score, context->frameCount);
        context->frameCount = 0;
        context->titleTimestamp = context->frameEnd;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (context->frameDuration < context->targetFrameDuration)
    {
        SDL_Delay(context->targetFrameDuration - context->frameDuration);
    }

    if (!context->running)
    {
#ifdef __EMSCRIPTEN__
        emscripten_cancel_main_loop();
#endif
    }
}

void Game::PlaceFood()
{
    int x, y;
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);

        // Check that the location is not occupied by a snake item before placing food.
        if (!snake.SnakeCell(x, y))
        {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

void Game::Update()
{
    if (!snake.alive)
    {
        return;
    }

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's food over here
    if (food.x == new_x && food.y == new_y)
    {
        score++;
        PlaceFood();

        // Grow snake and increase speed.
        snake.GrowBody();
        snake.speed += 0.02;
    }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }
