#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

#define SEED_COUNT 6
#define PI 3.14159265

// My plan
// Take in all of the seed values, loop through them, select the closest one and copy its colors

in vec4 gl_FragCoord;
out vec4 fragColor;

uniform vec2 u_resolution;
uniform float u_time;

// Voronoi specific inputs
uniform int u_seed_count;
uniform vec2[SEED_COUNT] u_seed_pos;
uniform vec2[SEED_COUNT] u_seed_vel;
uniform vec4[SEED_COUNT] u_seed_col;


void main()
{
   vec2 coord = gl_FragCoord.xy / u_resolution;
   
   int closest_seed_index = 0;
   float maximum_distance = sqrt(u_resolution.x * u_resolution.y);
   float closest_distance = maximum_distance;
   for(int seed = 0; seed < u_seed_count; seed++)
   {
      float seed_coord_distance = distance(coord, u_seed_pos[seed] / maximum_distance);
      if(seed_coord_distance < closest_distance) {
         closest_distance = seed_coord_distance;
         closest_seed_index = seed;
      }
   }

   fragColor = u_seed_col[closest_seed_index];
};