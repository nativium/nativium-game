ROOT_DIR=${PWD}

.DEFAULT_GOAL := help
.PHONY: build nativium

# tasks
help:
	@echo "Type: make [rule]. Available options are:"
	@echo ""
	@echo "- help"
	@echo "- clean"
	@echo "- nativium"
	@echo "- custom-install"
	@echo "- format"
	@echo "- gluecode"
	@echo ""
	@echo "- build-macos"
	@echo "- build-linux"
	@echo "- build-windows"
	@echo "- build-wasm"
	@echo "- build-ios"
	@echo "- build-android"
	@echo ""
	@echo "- run-macos"
	@echo "- run-linux"
	@echo "- run-windows"

clean:
	@echo "Cleaning..."
	@rm -rf nativium
	@rm -rf .DS_Store
	@rm -rf *.pyc
	@rm -rf Thumbs.db
	@echo "OK"

nativium:
	@rm -rf nativium
	@git clone https://github.com/nativium/nativium.git nativium

custom-install:
	@cd nativium && python nativium.py custom install --path=${ROOT_DIR}/custom

build-macos:
	@make custom-install
	@cd nativium && python nativium.py target macos prepare
	@cd nativium && python nativium.py target macos build
	@cd nativium && python nativium.py target macos package

build-linux:
	@make custom-install
	@cd nativium && python nativium.py target linux prepare
	@cd nativium && python nativium.py target linux build
	@cd nativium && python nativium.py target linux package

build-windows:
	@make custom-install
	@cd nativium && python nativium.py target windows prepare
	@cd nativium && python nativium.py target windows build
	@cd nativium && python nativium.py target windows package

build-wasm:
	@make custom-install
	@cd nativium && python nativium.py target wasm prepare
	@cd nativium && python nativium.py target wasm build
	@cd nativium && python nativium.py target wasm package

build-ios:
	@make custom-install
	@cd nativium && python nativium.py target ios prepare
	@cd nativium && python nativium.py target ios build
	@cd nativium && python nativium.py target ios package --no-framework
	@cd nativium && python nativium.py app ios pods
	@cd nativium && python nativium.py app ios build

build-android:
	@make custom-install
	@cd nativium && python nativium.py target android prepare
	@cd nativium && python nativium.py target android build
	@cd nativium && python nativium.py target android package
	@cd nativium && python nativium.py app android build

run-macos:
	@cd nativium && python nativium.py target macos run

run-linux:
	@cd nativium && python nativium.py target linux run

run-windows:
	@cd nativium && python nativium.py target windows run

format:
	@cd nativium && python nativium.py code format --path=../custom

gluecode:
	@make custom-install
	@cd nativium && python nativium.py gluecode setup
	@cd nativium && python nativium.py gluecode generate
