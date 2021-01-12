#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

// Sort boids sequentially
void sequential_merge_sort(boid_t *T, const size_t size, int (*cmp)(const boid_t *e1, const boid_t *e2));

// Sort boids in parallel
void parallel_merge_sort(boid_t *T, const size_t size, int (*cmp)(const boid_t *e1, const boid_t *e2));
