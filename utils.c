#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "utils.h"

int cmpfunc_pos_x(const boid_t *a, const boid_t *b)
{
  return (int)(a->position->x - b->position->x);
}

int cmpfunc_pos_y(const boid_t *a, const boid_t *b)
{
  return (int)(a->position->y - b->position->y);
}

float _inner_prod(vector_t *a, vector_t *b)
{
  return a->x * b->x + a->y + b->y;
}

float _norm(vector_t *a)
{
  return sqrt(_inner_prod(a, a));
}

float _angle(vector_t *a, vector_t *b)
{
  return acos(_inner_prod(a, b) / (_norm(a) * _norm(b)));
}

bool is_visible(const boid_t *a, const boid_t *b, float r, float theta)
{
  vector_t vec = {b->position->x - a->position->x, a->position->y - b->position->y};
  float distance = _norm(&vec);
  float beta = _angle(a->velocity, &vec);
  return distance <= r && beta <= theta / 2;
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
