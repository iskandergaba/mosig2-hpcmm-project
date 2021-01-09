#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "sorting.h"

typedef struct boid {
  float pos_x;
  float pos_y;
  float vel_x;
  float vel_y;
  int type;
} boid_t;

void print_boid_pos(boid_t* b) {
  printf("(%.2f, %.2f)", b->pos_x, b->pos_y);
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage:  ./main.run <sqrt(number_of_boids)>  <fraction of obstacles>\n");
    return -1;
  }

  int p = atoi(argv[1]);                // size of neighborhood grid
  int n = p * p;                        // number of boids
  float obs_fraction = atof(argv[2]);   // fraction of obstacles

  if (obs_fraction < 0 || obs_fraction >= 1) {
    fprintf(stderr, "The fraction of obstacles should lie in [0, 1).\n");
    return -1;
  }


  // our boids will be positioned in:
  // x \in [0, range_x)
  // y \in [0, range_y)
  int range_x = 250;
  int range_y = 200;

  // Allocate grid
  boid_t** grid = (boid_t**) malloc(p * sizeof(boid_t*));
  for (size_t i = 0; i < p; i++) {
    grid[i] = (boid_t*) malloc(p * sizeof(boid_t));
  }

  srand(time(NULL));
  // Initializing grid
  for (size_t i = 0; i < p; i++) {
    for(size_t j = 0; j < p; j++) {
      grid[i][j].pos_x = rand() % range_x;
      grid[i][j].pos_y = rand() % range_y;
      float is_obstacle = (float) rand() / (float) RAND_MAX;
      if (is_obstacle < obs_fraction) {
        grid[i][j].type = 0;
        grid[i][j].vel_x = 0;
        grid[i][j].vel_y = 0;
      } else {
        grid[i][j].type = 1;
        grid[i][j].vel_x = 5;
        grid[i][j].vel_y = 5;
      }

      // Print them
      // print_boid_pos(&grid[i][j]);
      // printf("\t\ttype %d\n", grid[i][j].type);
    }
  }



  return 0;
}
