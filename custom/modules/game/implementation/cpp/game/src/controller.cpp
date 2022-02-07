#include "controller.hpp"
#include "SDL.h"
#include "snake.hpp"
#include <iostream>

Controller::~Controller()
{
    std::cout << "Controller was destroyed" << std::endl;
}

void Controller::ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const
{
    if (snake.direction != opposite || snake.size == 1)
    {
        snake.direction = input;
    }

    return;
}

void Controller::HandleInput(const std::shared_ptr<Context> &context, Snake &snake) const
{
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            context->running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
            case SDL_SCANCODE_UP:
                ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
                break;

            case SDLK_DOWN:
            case SDL_SCANCODE_DOWN:
                ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
                break;

            case SDLK_LEFT:
            case SDL_SCANCODE_LEFT:
                ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
                break;

            case SDLK_RIGHT:
            case SDL_SCANCODE_RIGHT:
                ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
                break;
            case SDLK_ESCAPE:
            case SDL_SCANCODE_ESCAPE:
                context->running = false;
                break;
            }
        }
        else if (e.type == SDL_FINGERDOWN)
        {
            auto refX = ((e.tfinger.x * 100) / context->renderer->getScreenWidth());
            auto refY = ((e.tfinger.y * 100) / context->renderer->getScreenHeight());
            auto offset = 30;

            if (refX <= offset)
            {
                if (refY > offset && refY < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
                }
            }
            else if (refX >= (100 - offset))
            {
                if (refY > offset && refY < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
                }
            }
            else if (refY <= offset)
            {
                if (refX > offset && refX < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
                }
            }
            else if (refY >= (100 - offset))
            {
                if (refX > offset && refX < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
                }
            }
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            auto refX = ((e.motion.x * 100) / context->renderer->getScreenWidth());
            auto refY = ((e.motion.y * 100) / context->renderer->getScreenHeight());
            auto offset = 30;

            if (refX <= offset)
            {
                if (refY > offset && refY < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kLeft, Snake::Direction::kRight);
                }
            }
            else if (refX >= (100 - offset))
            {
                if (refY > offset && refY < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kRight, Snake::Direction::kLeft);
                }
            }
            else if (refY <= offset)
            {
                if (refX > offset && refX < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kUp, Snake::Direction::kDown);
                }
            }
            else if (refY >= (100 - offset))
            {
                if (refX > offset && refX < (100 - offset))
                {
                    ChangeDirection(snake, Snake::Direction::kDown, Snake::Direction::kUp);
                }
            }
        }
    }
}
