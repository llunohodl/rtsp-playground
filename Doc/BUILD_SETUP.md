# setup build enviroment for this project

>VScode setup based on [this manual](https://code.visualstudio.com/docs/cpp/cmake-linux)

1. Install dependencies
```
sudo apt-get install -y gcc g++ make cmake build-essential gdb
```

2. Install [VS code](https://code.visualstudio.com/download) and extensions:
- [C++ extension for VS Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
- [CMake Tools extension for VS Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) 

3. Select a kit

Open the Command Palette (`Ctrl+Shift+P`) and run `CMake: Select a Kit`. The extension will automatically scan for kits on your computer and create a list of compilers found on your system.

4. Select a variant

To select a variant, open the Command Palette (`Ctrl+Shift+P`) run the `CMake: Select Variant` command.

5. CMake: Configure

Now that you've selected a kit and a variant, open the Command Palette (`Ctrl+Shift+P`) and run the `CMake: Configure` command to configure your project. 

6. Build

**Press `F7`** or open the Command Palette (`Ctrl+Shift+P`) and run the `CMake: Build` command, or select the Build button from the Status bar.

7. Debug 

**Press `Ctrl + F5`**  or open the Command Palette (`Ctrl+Shift+P`) and run `CMake: Debug`.