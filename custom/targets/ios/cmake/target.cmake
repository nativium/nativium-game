# conan
nativium_add_conan_build_info()

# modules
nativium_add_modules()

# source
include(${NATIVIUM_TARGETS_PATH}/${NATIVIUM_TARGET}/cmake/source.cmake)

# platform settings
set(CMAKE_OSX_ARCHITECTURES "${NATIVIUM_PLATFORM_ARCH}")
set(CMAKE_OSX_DEPLOYMENT_TARGET "${NATIVIUM_DEPLOYMENT_TARGET}")

set(DEVELOPMENT_TEAM_ID
    ""
    CACHE STRING "Development Team ID"
)

set(CODE_SIGN_IDENTITY
    ""
    CACHE STRING "Sign Identity"
)

set(FRAMEWORK_NAME
    "${NATIVIUM_PROJECT_NAME}"
    CACHE STRING "Framework Name"
)

set(FRAMEWORK_BUNDLE_IDENTIFIER
    "com.nativium.library"
    CACHE STRING "Bundle Identifier"
)

if(NATIVIUM_GROUP STREQUAL "ios" OR "ios_simulator")
    set(DEVICE_FAMILY
        "1,2"
        CACHE STRING "Device Family"
    )
elseif(NATIVIUM_GROUP STREQUAL "tvos" OR "tvos_simulator")
    set(DEVICE_FAMILY
        "3"
        CACHE STRING "Device Family"
    )
elseif(NATIVIUM_GROUP STREQUAL "watchos")
    set(DEVICE_FAMILY
        "4"
        CACHE STRING "Device Family"
    )
    set(CMAKE_SYSTEM_VERSION "10.5")
elseif(NATIVIUM_GROUP STREQUAL "watchos_simulator")
    set(DEVICE_FAMILY
        "4"
        CACHE STRING "Device Family"
    )
    set(CMAKE_SYSTEM_VERSION "10.5")
endif()

# framework links
set(NATIVIUM_FRAMEWORK_LINKS
    ${NATIVIUM_FRAMEWORK_LINKS} "-framework Foundation -framework ImageIO -framework MobileCoreServices"
    CACHE INTERNAL ""
)

# c flags
set(NATIVIUM_C_FLAGS
    "${NATIVIUM_C_FLAGS} -fobjc-arc -fobjc-abi-version=2"
    CACHE INTERNAL ""
)

# cxx flags
set(NATIVIUM_CXX_FLAGS
    "${NATIVIUM_CXX_FLAGS} -fobjc-arc -fobjc-abi-version=2 -stdlib=libc++"
    CACHE INTERNAL ""
)

# flags
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} ${NATIVIUM_C_FLAGS}"
    CACHE INTERNAL ""
)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} ${NATIVIUM_CXX_FLAGS}"
    CACHE INTERNAL ""
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL} -Os")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O2 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O3")

# project
include_directories(${NATIVIUM_HEADER_SEARCH_PATHS})
link_directories(${NATIVIUM_LIBRARY_SEARCH_PATHS})

add_library(${NATIVIUM_PROJECT_NAME} SHARED ${NATIVIUM_SOURCE_FILES_MERGED})

target_link_libraries(${NATIVIUM_PROJECT_NAME} "${NATIVIUM_LIBRARY_LINKS}")
target_link_libraries(${NATIVIUM_PROJECT_NAME} "${NATIVIUM_FRAMEWORK_LINKS}")
target_link_libraries(${NATIVIUM_PROJECT_NAME} "${CONAN_LIBS}")

set_target_properties(
    ${NATIVIUM_PROJECT_NAME}
    PROPERTIES CXX_STANDARD "${NATIVIUM_CXX_STANDARD}"
               CXX_STANDARD_REQUIRED YES
               CXX_EXTENSIONS NO
               CXX_VISIBILITY_PRESET default
               FRAMEWORK TRUE
               FRAMEWORK_VERSION A
               MACOSX_FRAMEWORK_IDENTIFIER "${FRAMEWORK_BUNDLE_IDENTIFIER}"
               # machine readable
               MACOSX_FRAMEWORK_BUNDLE_VERSION "${NATIVIUM_VERSION}"
               # user visible
               MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${NATIVIUM_VERSION}"
               XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${FRAMEWORK_BUNDLE_IDENTIFIER}"
               XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "${CMAKE_OSX_DEPLOYMENT_TARGET}"
               XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${CODE_SIGN_IDENTITY}"
               XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO
               XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM_ID}"
               XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "${DEVICE_FAMILY}"
               XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES
               XCODE_ATTRIBUTE_SKIP_INSTALL YES
               VERSION "${NATIVIUM_VERSION}"
               SOVERSION "${NATIVIUM_VERSION_MAJOR}"
)

if(NATIVIUM_GROUP STREQUAL "ios_catalyst")
    set_target_properties(${NATIVIUM_PROJECT_NAME} PROPERTIES INSTALL_RPATH "@loader_path/../../..")
else()
    set_target_properties(${NATIVIUM_PROJECT_NAME} PROPERTIES XCODE_ATTRIBUTE_INSTALL_PATH "@loader_path/Frameworks")
endif()

target_compile_options(${NATIVIUM_PROJECT_NAME} PUBLIC "${NATIVIUM_COMPILE_OPTIONS}")

target_compile_definitions(${NATIVIUM_PROJECT_NAME} PRIVATE NATIVIUM_VERSION="${NATIVIUM_VERSION}" NATIVIUM_VERSION_CODE="${NATIVIUM_VERSION_CODE}")
target_compile_definitions(${NATIVIUM_PROJECT_NAME} PRIVATE HAS_UNCAUGHT_EXCEPTIONS=0)
