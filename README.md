# C++ Native Mobile

<p align="center">This is a test project that connect C++, Swift, Java and Kotlin in a Full-Duplex communication.</p>

<p align="center">This is an alpha project. After it works i will delete it and put on correct repository.</p>

<p align="center">
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/cxx.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/cxx.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/swift.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/swift.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/kotlin.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/kotlin.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/java.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/java.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/wasm.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/wasm.yml/badge.svg"></a>
</p>

<p align="center">
    <a href="https://app.codiga.io/hub/project/34803/cpp-native-mobile"><img src="https://api.codiga.io/project/34803/score/svg"></a>
    <a href="https://app.codiga.io/hub/project/34803/cpp-native-mobile"><img src="https://api.codiga.io/project/34803/status/svg"></a>
</p>

## How to build for C++

Execute on terminal:

`make build-cxx`

## How to build for Swift

Execute on terminal:

`make build-swift`

## How to build for Kotlin

Execute on terminal:

`make build-kotlin`

## How to build for Java

Execute on terminal:

`make build-java`

## How to build for Web Assembly

Execute on terminal:

`make build-wasm`

## Tree

This is the project structure when run `make tree`:

```
.
├── CMakeLists.txt
├── CMakeLists.txt.user
├── Makefile
├── README.md
├── cmake
│   └── CPM.cmake
├── cxx
│   ├── include
│   │   ├── lib.hpp
│   │   └── type-wrapper.hpp
│   └── src
│       ├── lib.cpp
│       └── main.cpp
├── kotlin
│   │   ├── build.gradle
│   │   └── src
│   │       ├── main
│   │       │   └── kotlin
│   │       │       └── application
│   │       │           ├── App.kt
│   │       │           ├── MyClass.kt
│   │       │           └── Product.kt
│   │       └── test
│   │           └── kotlin
│   │               └── app
│   │                   └── AppTest.kt
│   ├── gradle
│   │   └── wrapper
│   │       ├── gradle-wrapper.jar
│   │       └── gradle-wrapper.properties
│   ├── gradlew
│   ├── gradlew.bat
│   └── settings.gradle
└── swift
    └── main.swift

19 directories, 20 files
```
