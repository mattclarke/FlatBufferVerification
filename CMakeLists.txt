cmake_minimum_required(VERSION 3.14)
project(fb_verify)

# CONAN
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.13/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include(${CMAKE_BINARY_DIR}/conan.cmake)

message("RUNNING CONAN")

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)
message("DONE RUNNING CONAN")

set(CMAKE_CXX_STANDARD 14)

add_executable(fb_verify
        main.cpp
        schemas/f142.h
        schemas/f142.cpp
        schemas/hs00.h
        schemas/hs00.cpp
        schemas/x5f2.h
        schemas/x5f2.cpp
        )

set_property(TARGET fb_verify
        PROPERTY COMPILE_DEFINITIONS FLATBUFFERS_TRACK_VERIFIER_BUFFER_SIZE
        FLATBUFFERS_DEBUG_VERIFICATION_FAILURE=1)

target_link_libraries(fb_verify PRIVATE CONAN_PKG::streaming-data-types)