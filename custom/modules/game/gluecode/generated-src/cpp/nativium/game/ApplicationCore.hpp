// AUTOGENERATED FILE - DO NOT MODIFY!
// This file was generated by Djinni from proj.djinni

#pragma once

#include <cstdint>
#include <memory>
#include <string>

namespace nativium { namespace game {

class ApplicationCore {
public:
    virtual ~ApplicationCore() = default;

    static /*not-null*/ std::shared_ptr<ApplicationCore> shared();

    virtual std::string getVersion() = 0;

    virtual void initialize(int32_t width, int32_t height, int32_t mode) = 0;
};

} }  // namespace nativium::game
