# CPP NATIVE MOBILE

This is a test project that connect C++, Swift and Kotlin in a full-duplex communication.

<p align="center">
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/swift.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/swift.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/kotlin.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/kotlin.yml/badge.svg"></a>
    <a href="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/wasm.yml"><img src="https://github.com/paulocoutinhox/cpp-native-mobile/actions/workflows/wasm.yml/badge.svg"></a>
</p>

## How to build for Swift

Execute on terminal:

`make swift`

## How to build for Kotlin

Execute on terminal:

`make kotlin`

## How to build for Java

Execute on terminal:

`make java`

## How to build for Web Assembly

Execute on terminal:

`make wasm`

## Tree

This is the project structure when run `make tree`:

```
.
├── CMakeLists.txt
├── Makefile
├── README.md
├── conan
│   ├── darwin-toolchain
│   │   ├── README.md
│   │   ├── build.py
│   │   ├── conanfile.py
│   │   └── test_package
│   │       ├── CMakeLists.txt
│   │       ├── conanfile.py
│   │       └── src
│   │           └── example.cpp
│   ├── profiles
│   │   ├── android_profile
│   │   ├── catalyst_profile
│   │   ├── ios_profile
│   │   ├── ios_sim_profile
│   │   └── wasm_profile
│   └── recipe
│       └── conanfile.py
├── include
│   ├── hello-objc.h
│   └── hello.h
├── requirements.txt
├── src
│   ├── hello-objc.m
│   └── hello.cpp
└── test_package
    ├── CMakeLists.txt
    ├── conanfile.py
    └── src
        └── example.cpp

10 directories, 23 files
```
