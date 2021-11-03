# The VSCode workspace stuff

- CAUTION: The json file `c_cpp_properties.json` will work only on iOS. Windows and Linux users might have to make some changes
- Read this if you want VSCode to find the include files (and the Qt library) when writing your code
- You can change the `includePath` and the `MacFrameworkPath` to match the paths on your computer
- By using "**" in the end of the path, VSCode expands the search to include the subdirectories
- In the future we might add the `.json` files in the `.gitignore`