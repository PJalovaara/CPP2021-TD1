cmake_minimum_required(VERSION 3.1.0)

project(game VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON) # Should automatically scan header and source files and run moc accordingly
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

# including the hpp header files
include_directories(include)

# Set the prefix path for the cmake folder that includes configuration file Qt5Config.cmake (otherwise find_package might fail)
# For example on Antti's macbook it is /usr/local/Cellar/qt@5/5.15.2_1/lib/cmake
set(CMAKE_PREFIX_PATH /usr/local/Cellar/qt@5/5.15.2_1/lib/cmake) # CHANGE THIS LINE ONLY
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# We also need Qt5Multimedia for sound effects
find_package(Qt5Multimedia REQUIRED)

# file(GLOB...) allows for wildcard additions
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.hpp")

# remember to add the resources/res.qrc in the executable
# We also seem to need the headers for the AUTOMOC to run properly
add_executable(game ${SOURCES} resources/res.qrc ${HEADERS}) 

target_link_libraries(game Qt5::Widgets Qt5::Multimedia)