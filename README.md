## PURPOSE
The purpose of this repository is to act as a basic setup for a project that will use OpenGL to render shaders in c.

### Makes use of
- GLEW x64 - dll should be in bin folder
- GLFW x64

### Requirements for compilation
- MinGW-W64 compiler
- GCC should be up to date
- Libraries are .dll (MAYBE .A) for MinGW AND NOT .lib (MSVC)

### Main issues with current version
- User input is handled awkwardly in the handle_opengl file
- User input is handled awkwardly in general (many variables)
- SEED_COUNT constant should be defined similarly in voronoi and shader code
- The way that shaders are parsed prevents me from using a linter
- Not sure if values are being read into the shader correctly but it doesn't really matter

### TODO
- Fix issues if possible
- Make seeds move according to their velocity
- Make seeds either bounce off of screen edges or wrap around