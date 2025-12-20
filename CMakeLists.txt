cmake_minimum_required(VERSION 3.14)
project(Figures)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

add_executable(figures
    main.cpp
    src/Triangle.cpp
    src/Square.cpp
    src/Octagon.cpp
)

target_include_directories(figures PRIVATE include)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.1
)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

add_executable(test_figures test/test_figures.cpp
    src/Triangle.cpp
    src/Square.cpp
    src/Octagon.cpp
)
target_include_directories(test_figures PRIVATE include)
target_link_libraries(test_figures GTest::gtest_main)

enable_testing()
add_test(NAME FiguresTests COMMAND test_figures)
