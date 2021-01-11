#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "utils.h"

int cmpfunc_pos_x(const boid_t *a, const boid_t *b)
{
  return (int)(a->pos_x - b->pos_x);
}

int cmpfunc_pos_y(const boid_t *a, const boid_t *b)
{
  return (int)(a->pos_y - b->pos_y);
}

float distance(const boid_t *a, const boid_t *b)
{
  return sqrt(pow(a->pos_x - b->pos_x, 2) + pow(a->pos_y - b->pos_y, 2));
}

void print_boid_pos(boid_t *b)
{
  if (b->type == 0)
    printf("(%.2f\t %.2f)*", b->pos_x, b->pos_y);
  else
    printf("(%.2f\t %.2f)", b->pos_x, b->pos_y);
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
