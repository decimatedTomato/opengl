#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "handle_opengl.c"

#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480
#define SHADER_FILE_PATH "res/shaders/voronoi.shader"

typedef enum DisplayMode { // As of yet unused
    PAUSED, RENDERING
} DisplayMode;

DisplayMode Current_Mode = RENDERING;
int Window_Width = DEFAULT_WINDOW_WIDTH;
int Window_Height = DEFAULT_WINDOW_HEIGHT;
bool Is_Fullscreen = false;


//TODO take user input 
void take_user_input() {
    // if()
}

int main() {
    if(init_GLFW(Window_Width, Window_Height, "Voronoi") == -1) exit(1);
    init_Debug_Callback();
    init_Quad();

    init_Shader(SHADER_FILE_PATH);
    init_Uniforms(Window_Width, Window_Height);

    set_fullscreen(true, Window_Width, Window_Height);

    /* Loop until the user closes the window */
    bool keep_running = true;
    while (keep_running) {
        keep_running = render_frame(Window_Width, Window_Height);
    }
    clean_up();
    return 0;
}