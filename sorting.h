#include <stdio.h>
#include <stdlib.h>

typedef struct boid {
  float pos_x;
  float pos_y;
  float vel_x;
  float vel_y;
  int type;
} boid_t;


void sequential_merge_sort(boid_t *T, const size_t size, int(*cmp) (const boid_t* e1, const boid_t* e2));
void parallel_merge_sort(boid_t *T, const size_t size, int(*cmp) (const boid_t* e1, const boid_t* e2));
