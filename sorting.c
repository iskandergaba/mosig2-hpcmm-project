#include <omp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <x86intrin.h>

#include "sorting.h"

/*
   merge sort -- sequential, parallel --
*/

// merge function copied from qsort.c
void merge(boid_t *T, const size_t size, int(*cmp) (const boid_t* e1, const boid_t* e2)) {
  boid_t *X = (boid_t *)malloc(2 * size * sizeof(boid_t));

  size_t i = 0;
  size_t j = size;
  size_t k = 0;

  while ((i < size) && (j < 2 * size)) {
    if (cmp(&T[i], &T[j])) {
      X[k] = T[i];
      //X[k].pos_x = T[i].pos_x;
      //X[k].pos_y = T[i].pos_y;
      //X[k].vel_x = T[i].vel_x;
      //X[k].vel_y = T[i].vel_y;
      //X[k].type  = T[i].type;
      i = i + 1;
    } else {
      X[k] = T[j];
      j = j + 1;
    }
    k = k + 1;
  }

  if (i < size) {
    for (; i < size; i++, k++) {
      X[k] = T[i];
      //X[k].pos_x = T[i].pos_x;
      //X[k].pos_y = T[i].pos_y;
      //X[k].vel_x = T[i].vel_x;
      //X[k].vel_y = T[i].vel_y;
      //X[k].type  = T[i].type;
    }
  } else {
    for (; j < 2 * size; j++, k++) {
      X[k] = T[j];
      //X[k].pos_x = T[j].pos_x;
      //X[k].pos_y = T[j].pos_y;
      //X[k].vel_x = T[j].vel_x;
      //X[k].vel_y = T[j].vel_y;
      //X[k].type  = T[j].type;
    }
  }

  memcpy(T, X, 2 * size * sizeof(boid_t));
  free(X);

  return;
}

void sequential_merge_sort(boid_t *T, const size_t size, int(*cmp) (const boid_t* e1, const boid_t* e2)) {
  /* TODO: sequential implementation of merge sort */
  if (size < 2)
    return;
  else {
    sequential_merge_sort(T, size/2, cmp);
    sequential_merge_sort(T + size/2, size/2, cmp);
    merge(T, size/2, cmp);
  }
}

void parallel_merge_sort(boid_t *T, const size_t size, int(*cmp) (const boid_t* e1, const boid_t* e2)) {
  /* TODO: parallel implementation of merge sort */

  // Toggle between commented code for improved performance

  if (size < 2)
    return;
 

/*   if (size <= 512)
    sequential_merge_sort(T, size, cmp); */


  else {
    #pragma omp task
    parallel_merge_sort(T, size/2, cmp);
    #pragma omp task
    parallel_merge_sort(T + size/2, size/2, cmp);
    #pragma omp taskwait
    merge(T, size/2, cmp);
  }
}
