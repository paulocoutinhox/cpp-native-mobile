.PHONY: help
help:          ## Show The Help.
	@echo "Usage: make <target>"
	@echo ""
	@echo "Targets:"
	@fgrep "##" Makefile | fgrep -v fgrep

.PHONY: clear
clear:         ## Clear Temporary Files.
	rm -rf build
	rm -rf CMakeUserPresets.json

.PHONY: tree
tree:          ## List Files With Tree.
	tree

.PHONY: build-swift
build-swift:   ## Setup And Build For Swift.
	rm -rf build/swift
	mkdir -p build/swift

	cmake -S . -B build/swift -DNATIVE_TARGET=swift
	cmake --build build/swift

	swiftc swift/main.swift -o build/swift/main -v
	build/swift/main

.PHONY: build-kotlin
build-kotlin:  ## Setup And Build For Kotlin.
	rm -rf build/kotlin
	mkdir -p build/kotlin

	cmake -S . -B build/kotlin -DNATIVE_TARGET=kotlin
	cmake --build build/kotlin

	cd kotlin && ./gradlew clean build
	java -jar kotlin/app/build/libs/app.jar

.PHONY: build-wasm
build-wasm:    ## Setup And Build For WASM.
	rm -rf build/wasm
	mkdir -p build/wasm

	cmake -S . -B build/wasm -DNATIVE_TARGET=wasm
	cmake --build build/wasm

.PHONY: build-java
build-java:    ## Setup And Build For Java.
	rm -rf build/java
	mkdir -p build/java

	cmake -S . -B build/java -DNATIVE_TARGET=java
	cmake --build build/java

.PHONY: build-cxx
build-cxx:     ## Setup And Build For C++.
	rm -rf build/cxx
	mkdir -p build/cxx

	cmake -S . -B build/cxx -DNATIVE_TARGET=cxx
	cmake --build build/cxx

	./build/cxx/native-proj
