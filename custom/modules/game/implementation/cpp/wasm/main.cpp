#include "nativium/game/ApplicationCore.hpp"

#include <emscripten/emscripten.h>
#include <iostream>

using namespace nativium::game;

EM_JS(int, canvasGetWidth, (), {
    return document.getElementById("canvas").width;
});

EM_JS(int, canvasGetHeight, (), {
    return document.getElementById("canvas").height;
});

#ifdef __cplusplus
extern "C"
{
#endif

    EMSCRIPTEN_KEEPALIVE const char *Nativium_Game_Version()
    {
        const char *result;
        result = ApplicationCore::shared()->getVersion().c_str();
        return result;
    }

    EMSCRIPTEN_KEEPALIVE void Nativium_Game_Initialize(const int32_t width, const int32_t height, const int32_t mode)
    {
        ApplicationCore::shared()->initialize(width, height, mode);
    }

#ifdef __cplusplus
}
#endif

int main(int argc, char **argv)
{
    // version
    {
        std::cout << "Game Version: " << ApplicationCore::shared()->getVersion() << std::endl;
    }

    // game
    ApplicationCore::shared()->initialize(800, 640, 1);

    return EXIT_SUCCESS;
}
