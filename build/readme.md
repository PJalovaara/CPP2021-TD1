# Directory for the build
This folder should contain only build files of our implementation.
The cpp and hpp files are in separate directories `src` and `include` respectively.

- Navigate to the `build` directory
- In terminal run command `cmake ..`, where `..` is the path to the `tower-defense-1` directory which includes the `CMakeLists.txt`
- *Note*: Change the prefix path (`CMAKE_PREFIX_PATH`) in the `CMakeLists.txt` to include the configuration file Qt5Config.cmake provided by Qt5. You need to only change the line 22 with the comment `CHANGE THIS LINE ONLY`.
- After that run the command `make` to create an excecutable `game`
- Run the excecutable in terminal with the command `./game`