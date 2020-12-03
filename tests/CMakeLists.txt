
add_executable(tests
    tests.cpp
    test_zip.cpp
)

target_compile_options(tests 
PRIVATE
-std=c++20)

target_include_directories(tests
PRIVATE
    "${CMAKE_SOURCE_DIR}/src"
    CONAN_PKG::gtest    
)

target_link_libraries(tests
    CONAN_PKG::gtest    
)
