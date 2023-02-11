#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

#define SEED_COUNT 3
#define PI 3.14159265

// My plan
// Take in all of the seed values, loop through them, select the closest one and copy its colors

in vec2 gl_FragCoord;
out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

// Voronoi specific inputs
uniform int u_seed_count;
uniform vec2[3] u_seed_pos;
uniform vec2[3] u_seed_vel;
uniform vec4[3] u_seed_col;

void main()
{
   // Normalized pixel coordinates (from 0 to 1)
   vec2 coord = gl_FragCoord.xy / u_resolution.xy;

   // Time varying pixel color
   vec3 col = 0.5 + 0.5*cos(u_time + coord.xyx + vec3(0,2,4));

   // Output to screen
   fragColor = vec4(col,1.0);
};