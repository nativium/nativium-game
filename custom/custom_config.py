import os


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
            "path": "targets/android/config/target.py",
            "list": [
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
                },
                {
                    "old": '"main"',
                    "new": '"loader"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/ios/config/target.py",
            "list": [
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
                },
                {
                    "old": "has_tvos = True",
                    "new": "has_tvos = False",
                },
                {
                    "old": "has_watchos = True",
                    "new": "has_watchos = False",
                },
                {
                    "old": "has_mac_catalyst = True",
                    "new": "has_mac_catalyst = False",
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/linux/config/target.py",
            "list": [
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/macos/config/target.py",
            "list": [
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/windows/config/target.py",
            "list": [
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
                },
                {
                    "old": '"assets_dir": ""',
                    "new": '"assets_dir": "modules/game/resources"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/wasm/config/target.py",
            "list": [
                {
                    "old": '"product_name": "Nativium"',
                    "new": '"product_name": "Nativium - Game"',
                },
                {
                    "old": '["debug", "release"]',
                    "new": '["release"]',
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
            "path": "targets/android/cmake/target.cmake",
            "list": [
                {
                    "old": '"${NATIVIUM_LIBRARY_LINKS}"',
                    "new": '"${NATIVIUM_LIBRARY_LINKS}" "android" "log" "GLESv1_CM" "GLESv2" "OpenSLES"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/ios/cmake/target.cmake",
            "list": [
                {
                    "old": '${NATIVIUM_FRAMEWORK_LINKS} "-framework Foundation"',
                    "new": '${NATIVIUM_FRAMEWORK_LINKS} "-framework Foundation" "-framework ImageIO" "-framework MobileCoreServices"',
                },
            ],
        },
        {
            "type": "replace-text",
            "path": "targets/wasm/cmake/target.cmake",
            "list": [
                {
                    "old": '"--bind -s MALLOC=emmalloc -s WASM_BIGINT=1"',
                    "new": '"--bind -s MALLOC=emmalloc -s WASM_BIGINT=1 -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS=\'[\\"jpg\\",\\"png\\"]\' --preload-file ${NATIVIUM_MODULES_PATH}/game/resources/assets@assets --use-preload-plugins"',
                },
            ],
        },
    ]
