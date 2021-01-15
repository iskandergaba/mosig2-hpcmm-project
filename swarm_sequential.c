#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "sorting.h"

void initialize_grid(boid_t *grid, size_t n, size_t range_x, size_t range_y, float obs_fraction)
{
  for (size_t i = 0; i < n; i++)
  {
    grid[i].position = malloc(sizeof(vector_t));
    grid[i].velocity = malloc(sizeof(vector_t));

    grid[i].position->x = rand() % range_x;
    grid[i].position->y = rand() % range_y;

    float is_obstacle = (float)rand() / (float)RAND_MAX;
    if (is_obstacle < obs_fraction)
    {
      grid[i].type = 0;
      grid[i].velocity->x = 0;
      grid[i].velocity->y = 0;
    }
    else
    {
      grid[i].type = 1;
      grid[i].velocity->x = 5;
      grid[i].velocity->y = 5;
    }

    vector_t *velocity = malloc(sizeof(vector_t));
    velocity->x, velocity->y = is_obstacle < obs_fraction ? 0, 0 : 5, 5;
    grid[i].velocity = velocity;
  }
}

int main(int argc, char *argv[])
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage:  ./main.run <sqrt(number_of_boids)> <fraction of obstacles> <verbose>\n");
    return -1;
  }

  int p = atoi(argv[1]); // log_2(number of boids)
  if (p % 2 == 1)
  {
    fprintf(stderr, "Please provide an even number.\n");
    return -1;
  }

  int n = pow(p, 2);                  // number of boids
  int d = p;                          // size of grid across one dimension
  float obs_fraction = atof(argv[2]); // fraction of obstacles

  if (obs_fraction < 0 || obs_fraction >= 1)
  {
    fprintf(stderr, "The fraction of obstacles should lie in [0, 1).\n");
    return -1;
  }

  bool verbose = argc >= 4 ? atoi(argv[3]) : false;

  // our boids will be positioned in:
  // x \in [0, range_x)
  // y \in [0, range_y)
  size_t range_x = 250;
  size_t range_y = 200;

  // Allocate grid as 1D array (easier for the sake of sorting)
  boid_t *grid = (boid_t *)malloc(n * sizeof(boid_t));

  // Initializing grid
  srand(time(NULL));
  initialize_grid(grid, n, range_x, range_y, obs_fraction);

  // Printing after sorting
  if (verbose)
  {
    printf("Before sorting:\n");
    print_boid_grid(grid, d);
    printf("\n");
  }

  /*  for(size_t i = 0; i < n; i++) {
    if (i % d == 0) {
      printf("---------------\n");
    }
    print_boid_pos(&grid[i]);
    printf("\n");
  } */

  // Grouping               Influence   aka   COHESION
  // Repulsion              Influence   aka   SEPARATION
  // Direction Following    Influence   aka   ALIGNMENT
  // Obstacles and Enemies  Influence

  // influence implementations were inspired by:
  // https://gamedevelopment.tutsplus.com/tutorials/3-simple-rules-of-flocking-behaviors-alignment-cohesion-and-separation--gamedev-3444
  // They match with the paper

  // Weights are index by species type - 1, since we do not need a field for
  // type 0 (obstacles
  // TODO: currently we only have obstacle or boid - may or may not add enemies
  float cohesion_weights[1] = {1};
  float separation_weights[1] = {1};
  float alignment_weights[1] = {1};
  // repulsion factor increases seaparation of species from enemies/obstacles
  // than their own type
  float repulsion_factor[2] = {3, 1};

  size_t n_iterations = 100;
  // Radius in Neighborhood cells
  int neighborhood = 2;
  // Visibility radius
  float r = 25;

  // Execution time tracking variables
  struct timeval start, end;
  // Start timer
  gettimeofday(&start, NULL);
  for (size_t k = 0; k < n_iterations; k++)
  {

    /****************
     * SORTING PASS *
     ****************/
    // Sort by position x
    sequential_merge_sort(grid, n, cmpfunc_pos_x);
    // Now sort each column of the equivalent 2D array by pos_y
    for (size_t i = 0; i < d; i++)
    {
      sequential_merge_sort(grid + i * d, d, cmpfunc_pos_y);
    }
    // Printing after sorting
    if (verbose && k == 0)
    {
      printf("\n\nAfter sorting:\n");
      print_boid_grid(grid, d);
    }

    /***********************
     * UPDATING VELOCITIES *
     ***********************/
    // loop over the boids
    for (size_t i = 0; i < n; i++)
    {
      // get current boid
      boid_t *curr_boid = grid + i;

      // if current element is an obstacle, do nothing
      if (curr_boid->type == 0)
        continue;

      // get indexX and indexY
      size_t indexX = i / d;
      size_t indexY = i % d;

      //    printf("\nNeighbors of: ");
      //    print_boid_pos(&grid[i]);
      //    printf(" at indX=%zu and indY=%zu\n", indexX, indexY);

      // Initialize vectors for each influence
      vector_t cohesion = {0, 0};
      vector_t alignment = {0, 0};
      vector_t separation = {0, 0};
      size_t n_neighbors = 0;
      size_t n_neighbors_type = 0;
      boid_t *neighbor;

      // loop over the neighbors of the boid
      for (int x = -neighborhood; x <= neighborhood; x++)
      {
        for (int y = -neighborhood; y <= neighborhood; y++)
        {
          // access grid[indexX+x][indexY+y]
          if (x != 0 || y != 0)
          {
            int indXNeigh = (indexX + x) % d;
            int indYNeigh = (indexY + y) % d;
            //          print_boid_pos(&grid[indXNeigh * d + indYNeigh]);
            //          printf(" at x=%d and y=%d",x,y);
            //          printf("\n");

            neighbor = grid + indXNeigh * d + indYNeigh;
            // Check if the neighbor is visible to the current boid
            if (distance(curr_boid, neighbor) <= r)
            {
              n_neighbors++;
            }
            else
            {
              continue;
            }

            // Cohesion and Alignment only with neighbors of the same type
            if (neighbor->type == curr_boid->type)
            {
              n_neighbors_type++;
              cohesion.x += neighbor->position->x;
              cohesion.y += neighbor->position->y;

              alignment.x += neighbor->velocity->x;
              alignment.y += neighbor->velocity->y;
            }

            // Separation with all neighbors
            separation.x += neighbor->position->x - (grid + i)->position->x;
            separation.y += neighbor->position->y - (grid + i)->position->y;
            // if neighbor is an obstacle OR enemy separate more
            if (neighbor->type != curr_boid->type)
            {
              separation.x *= repulsion_factor[neighbor->type];
              separation.y *= repulsion_factor[neighbor->type];
            }
          }
        }
      }

      // Finalizing vectors
      if (n_neighbors_type > 0)
      {
        cohesion.x = cohesion.x / n_neighbors_type;
        cohesion.y = cohesion.y / n_neighbors_type;
        normalize_vector(&cohesion);

        alignment.x = alignment.x / n_neighbors_type;
        alignment.y = alignment.y / n_neighbors_type;
        normalize_vector(&alignment);
      }
      // keep this if statement because later we will compute visual field
      if (n_neighbors > 0)
      {
        separation.x *= -1 / n_neighbors;
        separation.y *= -1 / n_neighbors;
        normalize_vector(&separation);
      }

      // update velocity of boid
      curr_boid->velocity->x += alignment_weights[curr_boid->type - 1] * alignment.x +
                                cohesion_weights[curr_boid->type - 1] * cohesion.x +
                                separation_weights[curr_boid->type - 1] * separation.x;

      curr_boid->velocity->y += alignment_weights[curr_boid->type - 1] * alignment.y +
                                cohesion_weights[curr_boid->type - 1] * cohesion.y +
                                separation_weights[curr_boid->type - 1] * separation.y;
      // update position of boid
      // TODO: this modulo thing is horrible, fix it
      curr_boid->position->x = (int)(curr_boid->position->x + curr_boid->velocity->x) % range_x;
      curr_boid->position->y = (int)(curr_boid->position->y + curr_boid->velocity->y) % range_y;
    }
  }

  /*********************
  * FINAL SORTING PASS *
  *   FOR AESTHETICS   *
  **********************/
  // Sort by position x
  sequential_merge_sort(grid, n, cmpfunc_pos_x);
  // Now sort each column of the equivalent 2D array by pos_y
  for (size_t i = 0; i < d; i++)
  {
    sequential_merge_sort(grid + i * d, d, cmpfunc_pos_y);
  }
  // Printing after the iterations
  if (verbose)
  {
    printf("\n\nAfter %zu iterations:\n", n_iterations);
    print_boid_grid(grid, d);
  }

  // Stop timer
  gettimeofday(&end, NULL);

  double time_taken = end.tv_sec + end.tv_usec / 1e6 -
                      start.tv_sec - start.tv_usec / 1e6; // in seconds

  printf("Execution time: %f seconds\n", time_taken);
  return 0;
}
