#pragma once

#include "nativium/game/ApplicationCore.hpp"

#include <memory>

namespace nativium
{
namespace game
{

class ApplicationCoreImpl : public ApplicationCore
{
public:
    ApplicationCoreImpl();
    virtual ~ApplicationCoreImpl() {}

    static std::shared_ptr<ApplicationCoreImpl> internalSharedInstance();

    std::string getVersion() override;

    void initialize(int32_t width, int32_t height, int32_t mode) override;

private:
    static std::shared_ptr<ApplicationCoreImpl> instance;
};

} // namespace game
} // namespace nativium
