// ref: https://sourceforge.net/p/predef/wiki/OperatingSystems/

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define NATIVIUM_TARGET_WINDOWS

#ifdef _WIN64
#define NATIVIUM_TARGET_WINDOWS_64
#else
#define NATIVIUM_TARGET_WINDOWS_32
#endif
#elif __APPLE__
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#if TARGET_OS_OSX
#define NATIVIUM_TARGET_MACOS
#elif TARGET_OS_IPHONE
#define NATIVIUM_TARGET_IOS
#define NATIVIUM_TARGET_MOBILE
#elif TARGET_OS_SIMULATOR
#define NATIVIUM_TARGET_IOS
#define NATIVIUM_TARGET_MOBILE
#define NATIVIUM_TARGET_SIMULATOR
#endif
#endif
#elif __ANDROID__
#define NATIVIUM_TARGET_ANDROID
#define NATIVIUM_TARGET_MOBILE
#elif __linux__
#define NATIVIUM_TARGET_LINUX
#elif __unix__
// all unices not caught above
#define NATIVIUM_TARGET_UNIX
#elif defined(_POSIX_VERSION)
#define NATIVIUM_TARGET_POSIX
#else
#error "Unknown compiler"
#endif
