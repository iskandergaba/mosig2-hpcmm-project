#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "sorting.h"


void initialize_grid(boid_t* grid, size_t n, size_t range_x, size_t range_y, float obs_fraction) {
  for(size_t i = 0; i < n; i++) {
    grid[i].pos_x = rand() % range_x;
    grid[i].pos_y = rand() % range_y;
    float is_obstacle = (float) rand() / (float) RAND_MAX;
    if (is_obstacle < obs_fraction) {
      grid[i].type = 0;
      grid[i].vel_x = 0;
      grid[i].vel_y = 0;
    } else {
      grid[i].type = 1;
      grid[i].vel_x = 5;
      grid[i].vel_y = 5;
    }

    // Print them
    print_boid_pos(&grid[i]);
    printf("\t\ttype %d\n", grid[i].type);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage:  ./main.run <sqrt(number_of_boids)>  <fraction of obstacles>\n");
    return -1;
  }

  int p = atoi(argv[1]);                // log_2(number of boids)
  if (p % 2 == 1) {
    fprintf(stderr, "Please provide an even number.\n");
    return -1;
  }
  int n = pow(2, p);                    // number of boids
  int d = pow(2, p/2);                  // size of grid across one dimension
  float obs_fraction = atof(argv[2]);   // fraction of obstacles

  if (obs_fraction < 0 || obs_fraction >= 1) {
    fprintf(stderr, "The fraction of obstacles should lie in [0, 1).\n");
    return -1;
  }


  // our boids will be positioned in:
  // x \in [0, range_x)
  // y \in [0, range_y)
  size_t range_x = 250;
  size_t range_y = 200;

  // Allocate grid as 1D array (easier for the sake of sorting)
  boid_t* grid = (boid_t*) malloc(n * sizeof(boid_t));

  srand(time(NULL));
  // Initializing grid
  initialize_grid(grid, n, range_x, range_y, obs_fraction);

  // Sort by position x4.00
  sequential_merge_sort(grid, n, cmpfunc_pos_x);

  // Now sort each column of the equivalent 2D array by pos_y
  for (size_t i = 0; i < d; i++) {
    sequential_merge_sort(grid + i*d, d, cmpfunc_pos_y);
  }

  // Printing after sorting
  printf("\n\nAfter sorting:\n");

  print_boid_grid(grid, d);
//  for(size_t i = 0; i < n; i++) {
//    if (i % d == 0) {
//      printf("---------------\n");
//    }
//    print_boid_pos(&grid[i]);
//    printf("\n");
//  }
  return 0;
}
