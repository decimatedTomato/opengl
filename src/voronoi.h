#pragma once

typedef struct Vector2 {
    float x, y;
} Vector2;
typedef struct Vector4 {
    float x, y, z, w;
} Vector4;

typedef struct Seed {
    Vector2 position;
    Vector2 velocity;
    Vector4 color;
} Seed;

void refresh_seeds();