#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct vector
{
  float x;
  float y;
} vector_t;

typedef struct boid
{
  // Position vector
  vector_t *position;
  // Velocity vector
  vector_t *velocity;
  // Type: 0 if obstacle and 1 if boid
  int type;
} boid_t;

// Coordinate comparison functions
int cmpfunc_pos_x(const boid_t *a, const boid_t *b);
int cmpfunc_pos_y(const boid_t *a, const boid_t *b);

// Inner product between two vectors
float _inner_prod(vector_t *a, vector_t *b);

// Norm of a vector
float _norm(vector_t *a);

// Angle between two vectors
float _angle(vector_t *a, vector_t *b);

// Is boid b visible to boid a
bool is_visible(const boid_t *a, const boid_t *b, float r, float theta);

// Print the position of a boid
void print_boid_pos(boid_t *b);

// Print the grid of boids
void print_boid_grid(boid_t *b, int d);

// Normalize a vector
void normalize_vector(vector_t *v);
