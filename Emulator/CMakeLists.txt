cmake_minimum_required(VERSION 3.0.0)
project(MicroKime VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(MicroKime main.cpp mem.cpp cpu.cpp)
target_link_libraries(MicroKime SDL2::SDL2)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
