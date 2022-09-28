.PHONY: help
help:          ## Show The Help.
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@fgrep "##" Makefile | fgrep -v fgrep

.PHONY: clear
clear:         ## Clear Temporary Files.
	rm -rf build
	rm -rf conan/darwin-toolchain/test_package/build
	rm -rf CMakeUserPresets.json

.PHONY: tree
tree:          ## List Files With Tree.
	tree

.PHONY: build-swift
build-swift:   ## Setup And Build For Swift.
	rm -rf build/swift
	mkdir -p build/swift

	cmake -S . -B build/swift
	cmake --build build/swift

.PHONY: build-kotlin
build-kotlin:  ## Setup And Build For Kotlin.
	rm -rf build/kotlin
	mkdir -p build/kotlin

	cmake -S . -B build/kotlin
	cmake --build build/kotlin

.PHONY: build-wasm
build-wasm:    ## Setup And Build For WASM.
	rm -rf build/wasm
	mkdir -p build/wasm

	cmake -S . -B build/wasm
	cmake --build build/wasm
