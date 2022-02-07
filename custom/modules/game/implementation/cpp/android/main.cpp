#include <cstdlib>
#include <iostream>

#include "SDL.h"
#include "SDL_main.h"

#include "nativium/game/ApplicationCore.hpp"

using namespace nativium::game;

int main(int argc, char *argv[])
{
    int width = atoi(argv[1]);
    int height = atoi(argv[2]);

    auto msg = std::string("Screen Size: ") + std::to_string(width) + std::string(", ") + std::to_string(height);
    SDL_Log("%s", msg.c_str());

    ApplicationCore::shared()->initialize(width, height, 1);

    return EXIT_SUCCESS;
}
