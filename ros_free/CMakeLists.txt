cmake_minimum_required(VERSION 3.16)
project(better_fastlio2_ros_free LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(core
    src/odometry_pipeline.cpp
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(lio_runner
    src/main.cpp
)

target_link_libraries(lio_runner PRIVATE core)

