#!/bin/sh

mkdir -p bin
cp lib/glew32.dll bin/glew32.dll
gcc src/hello.c -o bin/hello -Iinclude -Llib -lmingw32 -lglfw3 -lopengl32 -lgdi32 -luser32 -lglew32

# USING MINGW-W64
# USING GLEW x64 - DLL MUST BE IN SAME FOLDER AS CC OUTPUT
# USIGN GLFW x64
# MAKE SURE LIBS ARE .DLL (MAYBE .A) FOR MINGW AND NOT .LIB (MSVC)
# MAKE SURE GCC IS UP TO DATE