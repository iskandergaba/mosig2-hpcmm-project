#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "sorting.h"

/*
   merge sort -- sequential, parallel --
*/

void merge(boid_t *T, const size_t size, int (*cmp)(const boid_t *e1, const boid_t *e2))
{
  boid_t *X = (boid_t *)malloc(size * sizeof(boid_t));

  size_t mid_size = size / 2;
  size_t i = 0;
  size_t j = mid_size;
  size_t k = 0;

  while ((i < mid_size) && (j < size))
  {
    if (cmp(&T[i], &T[j]) < 0)
    {
      X[k] = T[i];
      i = i + 1;
    }
    else
    {
      X[k] = T[j];
      j = j + 1;
    }
    k = k + 1;
  }

  if (i < mid_size)
  {
    for (; i < mid_size; i++, k++)
    {
      X[k] = T[i];
    }
  }
  else
  {
    for (; j < size; j++, k++)
    {
      X[k] = T[j];
    }
  }

  memcpy(T, X, size * sizeof(boid_t));
  free(X);

  return;
}

void sequential_merge_sort(boid_t *T, const size_t size, int (*cmp)(const boid_t *e1, const boid_t *e2))
{
  if (size < 2)
  {
    return;
  }
  else
  {
    sequential_merge_sort(T, size / 2, cmp);
    sequential_merge_sort(T + size / 2, size - size / 2, cmp);
    merge(T, size, cmp);
  }
}

void parallel_merge_sort(boid_t *T, const size_t size, int (*cmp)(const boid_t *e1, const boid_t *e2))
{
  if (size <= 512)
  {
    sequential_merge_sort(T, size, cmp);
  }
  else
  {
#pragma omp task
    parallel_merge_sort(T, size / 2, cmp);
#pragma omp task
    parallel_merge_sort(T + size / 2, size - size / 2, cmp);
#pragma omp taskwait
    merge(T, size, cmp);
  }
}
