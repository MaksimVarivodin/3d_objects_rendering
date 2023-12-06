cmake_minimum_required(VERSION 3.27)
project(3d_graphics)

set(CMAKE_CXX_STANDARD 17)
set(SDL2_INCLUDE_DIR C:/Users/maksy/Documents/Projects/c++/3DGraphics/packages/sdl2.nuget.2.28.5/build/native/include)
set(SDL2_LIB_DIR_X64 C:/Users/maksy/Documents/Projects/c++/3DGraphics/packages/sdl2.nuget.2.28.5/build/native/lib/x64)
set(SDL2_LIB_DIR_X86 C:/Users/maksy/Documents/Projects/c++/3DGraphics/packages/sdl2.nuget.2.28.5/build/native/lib/Win32)
include_directories(
3DGraphics
${SDL2_INCLUDE_DIR}
)
link_directories(
        ${SDL2_LIB_DIR_X86}
        ${SDL2_LIB_DIR_X64}
)
add_executable(3d_graphics
        3DGraphics/Headers/Header.h
        3DGraphics/SourceFiles/Main.cpp
        3DGraphics/SourceFiles/Matrix.cpp
        3DGraphics/Headers/Matrix.h
        3DGraphics/SourceFiles/Object3D.cpp
        3DGraphics/Headers/Object3D.h
        3DGraphics/SourceFiles/Point.cpp
        3DGraphics/Headers/Point.h
        3DGraphics/SourceFiles/Render3D.cpp
        3DGraphics/Headers/Render3D.h
        3DGraphics/SourceFiles/RenderWindow.cpp
        3DGraphics/Headers/RenderWindow.h
)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)