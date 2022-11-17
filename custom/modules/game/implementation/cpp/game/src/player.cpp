#include "player.hpp"
#include <iostream>

Player::Player(const Snake *snake, const SDL_Point *food)
    : _snake(snake)
    , _food(food)
{
    std::cout << "Player's Constructor called.\n";
};

Player::~Player()
{
    std::cout << "Player was destroyed" << std::endl;
}

void Player::play()
{
    // get the location of the head of snake
    int cur_x = static_cast<int>(_snake->head_x);
    int cur_y = static_cast<int>(_snake->head_y);

    if (cur_x != _food->x && cur_y != _food->y)
    {
        return; // keep moving
    }

    if (cur_x == _food->x && cur_y == _food->y)
    {
        return; // get food then keep moving
    }

    SDL_Event sdlevent;
    sdlevent.type = SDL_KEYDOWN;

    if (cur_x == _food->x)
    {
        if (cur_y > _food->y)
        {
            sdlevent.key.keysym.sym = SDLK_UP;
        }
        else
        {
            sdlevent.key.keysym.sym = SDLK_DOWN;
        }
    }
    else // cur_y == _food.y
    {
        if (cur_x > _food->x)
        {
            sdlevent.key.keysym.sym = SDLK_LEFT;
        }
        else
        {
            sdlevent.key.keysym.sym = SDLK_RIGHT;
        }
    }

    SDL_PushEvent(&sdlevent);
}
