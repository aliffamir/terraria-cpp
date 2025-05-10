cmake_minimum_required(VERSION 4.0.1)
project(terraria-cpp)

# C++ standards
set(CMAKE_CXX_STANDARD           23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)

# Gather source files to compile - use wildcard *.cpp
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/game/src/*.cpp")
file(GLOB_RECURSE PLATFORM_SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/platform/src/*.cpp")

# Create executables
add_executable(${PROJECT_NAME} ${GAME_SOURCES} ${PLATFORM_SOURCES})

# Add include directories (SDL2, SDL2_image, and game/platform header files)
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/game/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/platform/include")

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/SDL2_image/libSDL2_image.dylib"
    "${CMAKE_SOURCE_DIR}/lib/SDL2/libSDL2.dylib"
)
