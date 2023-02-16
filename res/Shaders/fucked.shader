#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment // What if you used the dot product instead of the distance of the seed and the pixel
#version 330 core

#define SEED_COUNT 30
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

vec2 calculate_seed_position(int seed){
   vec2 new_seed_position = mod(u_seed_pos[seed] + u_time * u_seed_vel[seed], vec2(1,1));
   return new_seed_position;
}
void main()
{
   bool in_seed = false;
   // vec2 coord = gl_FragCoord.xy / u_resolution;
   
   int closest_seed_index = 0;
   float closest_distance = length(u_resolution);
   for(int seed = 0; seed < u_seed_count; seed++) {
      vec2 new_seed_position = calculate_seed_position(seed);
      float seed_coord_distance = dot(abs(gl_FragCoord.x - u_resolution.x * new_seed_position.x), abs(gl_FragCoord.y - u_resolution.y * new_seed_position.y));
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