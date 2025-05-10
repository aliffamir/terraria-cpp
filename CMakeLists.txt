cmake_minimum_required(VERSION 4.0.1)
project(terraria-cpp)

# C++ standards
set(CMAKE_CXX_STANDARD           23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)


# Add include directories (so SDL2and SDL2_image headers are found)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Gather source files to compile - use wildcard *.cpp
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Create executables
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/lib/SDL2_image/libSDL2_image.dylib
    ${CMAKE_SOURCE_DIR}/lib/SDL2/libSDL2.dylib
)
