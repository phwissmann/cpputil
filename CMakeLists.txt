cmake_minimum_required(VERSION 3.0.0)
project(CPPUTIL VERSION 0.1.0)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
                SETTINGS compiler.cppstd=17 compiler=clang compiler.version=8
                BASIC_SETUP
                CMAKE_TARGETS
                BUILD missing
                )

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

add_subdirectory(tests)
