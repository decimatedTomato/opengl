#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include "handle_opengl.c"
#include "voronoi.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DEFAULT_WINDOW_WIDTH 640
#define DEFAULT_WINDOW_HEIGHT 480

// USER DEFINITIONS
// #define SHADER_FILE_PATH "res/shaders/voronoi.shader"
#define SHADER_FILE_PATH "res/shaders/nearest_n.shader"
#define SEED_COUNT 10
#define MAX_VELOCITY 0.3

// DISPLAY
typedef enum DisplayMode { // As of yet unused
    PAUSED, RENDERING
} DisplayMode;

DisplayMode mode = RENDERING;
int window_width = DEFAULT_WINDOW_WIDTH;
int window_height = DEFAULT_WINDOW_HEIGHT;
bool is_fullscreen = false;

// GENERATION
float rand_float() { return (float)rand() / ((float)RAND_MAX); }

Seed seeds[SEED_COUNT];

void generate_seeds() {
    for (size_t i = 0; i < SEED_COUNT; i++) {
        seeds[i].position.x = rand_float();
        seeds[i].position.y = rand_float();
        seeds[i].velocity.x = rand_float() * MAX_VELOCITY * (2 * (rand() % 2) - 1);
        seeds[i].velocity.y = rand_float() * MAX_VELOCITY * (2 * (rand() % 2) - 1);
        seeds[i].color.x = rand_float();
        seeds[i].color.y = rand_float();
        seeds[i].color.z = rand_float();
        seeds[i].color.w = 1;
        // printf("seed:%llu x:%.3f y:%.3f dx:%.3f dy:%.3f r:%.3f g:%.3f b:%.3f a:%.3f\n", i, seeds[i].position.x, seeds[i].position.y, seeds[i].velocity.x, seeds[i].velocity.y, seeds[i].color.x, seeds[i].color.y, seeds[i].color.z, seeds[i].color.w);
    }
}

void refresh_seeds() {
    generate_seeds();
    update_seed_uniforms(SEED_COUNT, seeds);
}

int main() {
    long long unsigned int t = time(NULL);
    printf("Random seed %llu\n", t);
    srand(t);
    generate_seeds();

    if(init_GLFW(window_width, window_height, "Voronoi") == -1) exit(1);
    init_Debug_Callback();
    init_Quad();

    init_Shader(SHADER_FILE_PATH);
    init_Uniforms(SEED_COUNT);
    update_seed_uniforms(SEED_COUNT, seeds);

    /* Loop until the user closes the window */
    bool keep_running = true;
    while (keep_running) {
        keep_running = render_frame();
        // refresh_seeds();
        take_user_input();
    }
    clean_up();
    return 0;
}