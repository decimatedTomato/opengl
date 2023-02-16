#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
   gl_Position = position;
};

#shader fragment
#version 330 core

#define N 3
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

struct Neighbor {
   int seed_index;
   float distance_from_pixel;
};

vec2 calculate_seed_position(int seed) {
   vec2 new_seed_position = mod(u_seed_pos[seed] + u_time * u_seed_vel[seed], vec2(1,1));
   return new_seed_position;
}
void main()
{
   fragColor = SEED_MARKER_COLOR;
   bool in_seed = false;
   int nearest = min(N, u_seed_count);
   nearest = max(1, nearest);
   
   Neighbor neighbors[SEED_COUNT];
   for(int seed = 0; seed < u_seed_count; seed++) {
      float distance_from_pixel = distance(gl_FragCoord.xy, u_resolution * calculate_seed_position(seed));
      if(distance_from_pixel <= SEED_MARKER_RADIUS) {
         in_seed = true;
         break;
      }
      neighbors[seed] = Neighbor( seed, distance_from_pixel );
   }
   if(in_seed) {
      return;
   }

   // Sort
   int min_distance_index;
   for(int i = 0; i < SEED_COUNT - 1; i++) {
      min_distance_index = i;
      for(int j = i + 1; j < SEED_COUNT; j++)
         if(neighbors[j].distance_from_pixel < neighbors[min_distance_index].distance_from_pixel) {
            min_distance_index = j;
         }
      Neighbor temp = neighbors[i];
      neighbors[i] = neighbors[min_distance_index];
      neighbors[min_distance_index] = temp;
   }
   
   // Taking average pixel color
   vec4 sum = vec4(0, 0, 0, 0);
   for(int p = 0; p < nearest; p++) {
      sum += u_seed_col[neighbors[p].seed_index] / nearest;
   }
   fragColor = sum;
};