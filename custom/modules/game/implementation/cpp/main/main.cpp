#include <iostream>

#include "SDL_main.h"
#include "nativium/game/ApplicationCore.hpp"

using namespace nativium::game;

int main(int argc, char *argv[])
{
    ApplicationCore::shared()->initialize(800, 600, 1);
    return EXIT_SUCCESS;
}
