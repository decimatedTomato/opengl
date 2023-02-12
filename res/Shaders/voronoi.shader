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
#define SEED_MARKER_RADIUS 6
#define SEED_MARKER_COLOR vec4(0.1, 0.1, 0.1, 1.0)

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
   bool in_seed = false;
   // vec2 coord = gl_FragCoord.xy / u_resolution;
   
   int closest_seed_index = 0;
   float closest_distance = length(u_resolution);
   for(int seed = 0; seed < u_seed_count; seed++) {
      float seed_coord_distance = distance(gl_FragCoord.xy, u_seed_pos[seed] * u_resolution);
      if(seed_coord_distance <= SEED_MARKER_RADIUS) {
         in_seed = true;
         break;
      }
      if(seed_coord_distance < closest_distance) {
         closest_distance = seed_coord_distance;
         closest_seed_index = seed;
      }
   }

   (in_seed) ? fragColor = SEED_MARKER_COLOR : fragColor = u_seed_col[closest_seed_index];
};