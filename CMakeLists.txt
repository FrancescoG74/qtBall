cmake_minimum_required(VERSION 3.16)
project(qtBall LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(qtBall
    source/main.cpp
    source/ball.cpp
    include/ball.h
    source/ballwindow.cpp
    include/ballwindow.h
)

target_include_directories(qtBall PRIVATE include)

target_link_libraries(qtBall PRIVATE Qt6::Widgets)

# Enable automatic MOC, UIC, and RCC for Qt
set_target_properties(qtBall PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)