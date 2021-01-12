#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int cmpfunc_pos_x(const boid_t *a, const boid_t *b)
{
  return (int)(a->position->x - b->position->x);
}

int cmpfunc_pos_y(const boid_t *a, const boid_t *b)
{
  return (int)(a->position->y - b->position->y);
}

float distance(const boid_t *a, const boid_t *b)
{
  return sqrt(pow(a->position->x - b->position->x, 2) + pow(a->position->y - b->position->y, 2));
}

void print_boid_pos(boid_t *b)
{
  if (b->type == 0)
    printf("(%.2f\t %.2f)*", b->position->x, b->position->y);
  else
    printf("(%.2f\t %.2f)", b->position->x, b->position->y);
}

void print_boid_grid(boid_t *grid, int d)
{
  for (size_t i = 0; i < d; i++)
  {
    for (size_t j = 0; j < d; j++)
    {
      print_boid_pos(grid + j * d + i);
      printf("  \t");
    }
    printf("\n");
  }
}

void normalize_vector(vector_t *v)
{
  float mag = sqrt(pow(v->x, 2) + pow(v->y, 2));
  v->x = v->x / mag;
  v->y = v->y / mag;
}
