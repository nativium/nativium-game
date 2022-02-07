#ifndef CONTEXT_H
#define CONTEXT_H

#include "SDL.h"

#include "controller.hpp"
#include "renderer.hpp"

#include <iostream>
#include <memory>

class Controller;
class Renderer;

class Context
{
public:
    std::shared_ptr<Renderer> renderer;
    std::shared_ptr<Controller> controller;
    int32_t targetFrameDuration;
    bool running;

    uint32_t titleTimestamp;
    uint32_t frameStart;
    uint32_t frameEnd;
    uint32_t frameDuration;
    int frameCount;

    Context()
    {
        std::cout << "Context was constructed" << std::endl;
    }

    ~Context()
    {
        std::cout << "Context was destroyed" << std::endl;
    }
};

#endif
