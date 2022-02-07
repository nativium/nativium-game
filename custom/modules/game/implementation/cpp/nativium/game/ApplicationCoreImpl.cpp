#include "ApplicationCoreImpl.hpp"
#include "game.hpp"
#include "platforms.hpp"

#include <memory>
#include <string>

namespace nativium
{
namespace game
{

std::shared_ptr<ApplicationCoreImpl> ApplicationCoreImpl::instance = nullptr;

ApplicationCoreImpl::ApplicationCoreImpl()
{
    // ignore
}

std::shared_ptr<ApplicationCore> ApplicationCore::shared()
{
    return ApplicationCoreImpl::internalSharedInstance();
}

std::shared_ptr<ApplicationCoreImpl> ApplicationCoreImpl::internalSharedInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<ApplicationCoreImpl>();
    }

    return instance;
}

void ApplicationCoreImpl::initialize(int32_t width, int32_t height, int32_t mode)
{
#ifdef NATIVIUM_TARGET_MOBILE
    SDL_SetMainReady();
#endif

    constexpr int32_t gridWidth{32};
    constexpr int32_t gridHeight{32};

    constexpr int32_t framesPerSecond{60};
    constexpr int32_t msPerFrame{1000 / framesPerSecond};

    Game game(width / gridWidth, height / gridHeight, mode);
    game.Run(std::make_shared<Renderer>(width, height, width / gridWidth, height / gridHeight), std::make_shared<Controller>(), msPerFrame);
}

std::string ApplicationCoreImpl::getVersion()
{
#ifdef NATIVIUM_CONFIG_VERSION
#define NATIVIUM_CONFIG_VERSION_STR NATIVIUM_CONFIG_VERSION
#else
#define NATIVIUM_CONFIG_VERSION_STR "1.0.0"
#endif

#ifdef NATIVIUM_CONFIG_VERSION_CODE
#define NATIVIUM_CONFIG_VERSION_CODE_STR NATIVIUM_CONFIG_VERSION_CODE
#else
#define NATIVIUM_CONFIG_VERSION_CODE_STR "1"
#endif

    return std::string(NATIVIUM_CONFIG_VERSION_STR) + " (" + std::string(NATIVIUM_CONFIG_VERSION_CODE_STR) + ")";
}

} // namespace game
} // namespace nativium
