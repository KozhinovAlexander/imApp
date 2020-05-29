# imApp
Sample Qt image processing app. The version of Qt used is [Qt v5.15.0](https://www.qt.io/offline-installers)

# HoTo Compile
For the compilation any C++14 supported compiler with Tools [Cmake](https://cmake.org) and [Ninja](https://ninja-build.org) can be used.

Following steps needed to be done for the comilation:

1. In project's root [CMakeLists.txt](https://github.com/Nukersson/imApp/blob/master/imApp/CMakeLists.txt):
  - Control the value of variable `BUILD_TOOLS_ROOT`. It should contain the path to installed g++/gcc
  - Control the value of variable `COMPILER_VER`. It is used as postfix for your compiler name like g++-9 in my case.
    It can be also leaved empty, if your compiler has other name.
  - Control the value of variable `CMAKE_MAKE_PROGRAM`. It is `BUILD_TOOLS_ROOT` dependent and should point to your ninja installation.
    
2. Run Cmake with project's root [CMakeLists.txt](https://github.com/Nukersson/imApp/blob/master/imApp/CMakeLists.txt). (Qt Creator which should be installed wit your Qt distribution is recommended IDE choise). 

3. Run/Debug from your IDE or Qt Creator (recommended).

# HoTo run

After application is started, the slideshow does not runs. You need first chhose the folder with [sample images](https://github.com/Nukersson/imApp/tree/master/images) and the press `Start/Stop` button.
 
