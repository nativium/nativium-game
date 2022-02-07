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
            "path": os.path.join("modules", "app-wasm"),
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
            "type": "copy-dir",
            "source": "targets",
            "target": "targets",
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
                    "old": '["Debug", "Release"]',
                    "new": '["Release"]',
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
    ]
