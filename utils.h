#include <stdio.h>
#include <stdlib.h>

typedef struct boid {
  float pos_x;
  float pos_y;
  float vel_x;
  float vel_y;
  int type;
} boid_t;

typedef struct vector {
  float x;
  float y;
} vector_t;


int cmpfunc_pos_x(const boid_t* a, const boid_t* b);
int cmpfunc_pos_y(const boid_t* a, const boid_t* b);
void print_boid_pos(boid_t* b);
void print_boid_grid(boid_t* b, int d);
void normalize_vector(vector_t* v);
