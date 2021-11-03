# Directory for the build
This folder should contain only build files of our implementation.
The cpp and hpp files are in separate directories `src` and `include` respectively.

- Navigate into the `build` directory
- In terminal run command `cmake ..`, where `..` is the path to the `tower-defense-1` directory which includes the `CMakeLists.txt`
- *Note*: Change the prefix path in the `CMakeLists.txt` to include the configuration file Qt5Config.cmake provided by Qt5
- After that run the command `make` to create an excecutable `test`
- Run the excecutable in terminal with the command `./test`