# cgns24-renderer
This repository contains the source files for the 3D Renderer implemented under the Summer 2024 Offering of the Computer Graphics and Shaders Project under Game Development Club, SnT Council, IIT Kanpur.

### Instructions

The project directory contains a `CMakeLists.txt` that contains the build configuration for our project. It is recommended to use Visual Studio 2019 or later (the above project is maintained on Visual Studio 2022).
After cloning the repo, please run the following commands (replace `17 2022` with `16 2019` for VS 2019)

```
mkdir out
cd out
cmake ../ -G"Visual Studio 17 2022" ${COMMON_CMAKE_CONFIG_PARAMS}
```

This would generate the build files for our project with the executable in `/out/Debug` folder. You can open the `.sln` file in Visual Studio and directly build after the initial `cmake` run. (Visual Studio itself runs the `cmake` on its own)
