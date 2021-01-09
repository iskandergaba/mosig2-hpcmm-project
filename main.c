#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorting.h"


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

  return 0;
}
