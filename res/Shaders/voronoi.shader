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

   int closest_seed_index = 0;
   float closest_distance = sqrt(u_resolution.x * u_resolution.y);
   for(int seed = 0; seed < u_seed_count; seed++)
   {
      float seed_coord_distance = distance(coord, u_seed_pos[seed]);
      if(seed_coord_distance < closest_distance) {
         closest_distance = seed_coord_distance;
         closest_seed_index = seed;
      }
   }

   // Output to screen
   fragColor = u_seed_col[closest_seed_index];
};