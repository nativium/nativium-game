import os
import textwrap


# -----------------------------------------------------------------------------
def run(params):
    return [
        {
            "type": "remove-dir",
            "path": os.path.join("modules", "tests"),
        },
        {
            "type": "remove-dir",
            "path": os.path.join("modules", "app-core"),
        },
        {
            "type": "remove-dir",
            "path": os.path.join("modules", "app-main"),
        },
        {
            "type": "remove-dir",
            "path": os.path.join("apps", "ios"),
        },
        {
            "type": "remove-dir",
            "path": os.path.join("apps", "android"),
        },
        {
            "type": "symlink",
            "source": os.path.join("modules", "game"),
            "target": os.path.join("modules", "game"),
        },
        {
            "type": "symlink",
            "source": os.path.join("apps", "ios"),
            "target": os.path.join("apps", "ios"),
        },
        {
            "type": "symlink",
            "source": os.path.join("apps", "android"),
            "target": os.path.join("apps", "android"),
        },
        {
            "type": "copy-file",
            "source": "cmake/dependencies.cmake",
            "target": "cmake/dependencies.cmake",
        },
        {
            "type": "replace-text",
            "path": "core/const.py",
            "list": [
                {
                    "old": 'BUCKET_NAME = "nativium"',
                    "new": 'BUCKET_NAME = "nativium-game"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/android/config/target_config.py",
            "list": [
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": '"main"',
                    "new": '"loader"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/ios/config/target_config.py",
            "list": [
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": "has_watchos_arm32 = True",
                    "new": "has_watchos_arm32 = False",
                },
                {
                    "old": "has_watchos_arm64 = True",
                    "new": "has_watchos_arm64 = False",
                },
                {
                    "old": "has_watchos_simulator_x64 = True",
                    "new": "has_watchos_simulator_x64 = False",
                },
                {
                    "old": "has_watchos_simulator_arm64 = True",
                    "new": "has_watchos_simulator_arm64 = False",
                },
                {
                    "old": "has_mac_catalyst_x64 = True",
                    "new": "has_mac_catalyst_x64 = False",
                },
                {
                    "old": "has_mac_catalyst_arm64 = True",
                    "new": "has_mac_catalyst_arm64 = False",
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/linux/config/target_config.py",
            "list": [
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/macos/config/target_config.py",
            "list": [
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/windows/config/target_config.py",
            "list": [
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/wasm/config/target_config.py",
            "list": [
                {
                    "old": '"product_name": "Nativium"',
                    "new": '"product_name": "Nativium - Game"',
                },
                {
                    "old": 'has_debug = True',
                    "new": 'has_debug = False',
                },
                {
                    "old": '"publish_bucket_name": "nativium"',
                    "new": '"publish_bucket_name": "nativium-game"',
                },
                {
                    "old": '"url": "https://nativium.',
                    "new": '"url": "https://nativium-game.',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/wasm/support/web/index.html",
            "list": [
                {
                    "old": 'let appType = "form"',
                    "new": 'let appType = "canvas"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "CMakeLists.txt",
            "list": [
                {
                    "old": 'set(NATIVIUM_LIBRARY_LINKS "" CACHE STRING "Library Links")',
                    "new": textwrap.dedent("""\
                    if(NATIVIUM_TARGET STREQUAL "android")
                        set(NATIVIUM_LIBRARY_LINKS "android" "log" "GLESv1_CM" "GLESv2" "OpenSLES" CACHE STRING "Library Links")
                    else()
                        set(NATIVIUM_LIBRARY_LINKS "" CACHE STRING "Library Links")
                    endif()
                    """)
                },
                {
                    "old": 'set(NATIVIUM_FRAMEWORK_LINKS "" CACHE STRING "Framework Links")',
                    "new": textwrap.dedent("""\
                    if(NATIVIUM_TARGET STREQUAL "ios")
                        set(NATIVIUM_FRAMEWORK_LINKS "-framework Foundation" "-framework ImageIO" "-framework MobileCoreServices" CACHE STRING "Framework Links")
                    else()
                        set(NATIVIUM_FRAMEWORK_LINKS "" CACHE STRING "Framework Links")
                    endif()
                    """)
                },
                {
                    "old": 'set(NATIVIUM_WASM_LINK_FLAGS "--bind -s MALLOC=emmalloc -s WASM_BIGINT=1")',
                    "new": textwrap.dedent("""\
                    set(NATIVIUM_WASM_LINK_FLAGS "--bind -s MALLOC=emmalloc -s WASM_BIGINT=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\'[\\"jpg\\",\\"png\\"]\' --preload-file ${NATIVIUM_MODULES_PATH}/game/resources/assets@assets --use-preload-plugins")"""),
                },
            ],
        },
    ]
