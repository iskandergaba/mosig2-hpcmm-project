#include <stdio.h>
#include <stdlib.h>

typedef struct boid
{
  // position vector
  float pos_x;
  float pos_y;
  // velocity vector
  float vel_x;
  float vel_y;
  // type: 0 if obstacle and 1 if boid
  int type;
} boid_t;

typedef struct vector
{
  float x;
  float y;
} vector_t;

// Coordinate comparison functions
int cmpfunc_pos_x(const boid_t *a, const boid_t *b);
int cmpfunc_pos_y(const boid_t *a, const boid_t *b);

// Print the position of a boid
void print_boid_pos(boid_t *b);
// Print the grid of boids
void print_boid_grid(boid_t *b, int d);
// Normalize a vector
void normalize_vector(vector_t *v);
