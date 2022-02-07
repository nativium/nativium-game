#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "context.hpp"
#include "snake.hpp"

class Context;

class Controller
{
public:
    void HandleInput(const std::shared_ptr<Context> &context, Snake &snake) const;
    ~Controller();

private:
    void ChangeDirection(Snake &snake, Snake::Direction input, Snake::Direction opposite) const;
};

#endif
