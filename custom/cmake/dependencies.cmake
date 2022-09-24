# dependencies for tests
include(${NATIVIUM_ROOT_PATH}/cmake/dependencies-tests.cmake)

# sdl2
find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${NATIVIUM_PROJECT_NAME} PRIVATE SDL2::SDL2-static)

# sdl2 image
find_package(SDL2_image CONFIG REQUIRED)
target_link_libraries(${NATIVIUM_PROJECT_NAME} PRIVATE SDL2_image::SDL2_image-static)
