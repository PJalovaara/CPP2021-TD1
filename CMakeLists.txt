cmake_minimum_required(VERSION 3.1.0)

project(test VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# including the hpp header files
include_directories(include)

# Set the prefix path for the configuration file Qt5Config.cmake provided by Qt5 (otherwise find_package might fail)
set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt@5/5.15.2_1/lib/cmake/Qt5)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# file(GLOB...) allows for wildcard additions
file(GLOB SOURCES "src/*.cpp")

add_executable(test ${SOURCES})

target_link_libraries(test Qt5::Widgets)