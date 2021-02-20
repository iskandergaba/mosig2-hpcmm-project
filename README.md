# High Performance Computing for Mathematical Models - Swarm Behavior Simulation Project
## Team Members
+ Iskander Gaba
+ Hadi Dayekh

## How to run
1. Compile the executable files using the following command
```
make
```

You should notice the appearance of two new executables: `swarm_parallel.run` and `swarm_sequential.run`.

2. Run the following command to execute **sequential** simulation of swarm behavior:

```
./swarm_sequential.run <sqrt(number_of_boids)> <fraction of obstacles> <verbose>
```
where:
- `<sqrt(number_of_boids)>`: is the square root of number of boids in the simulation.
- `<fraction of obstacles>`: is a number in the range [0, 1] describing the probability of having an obstacle instead of a boid in a given grid cell.
- `verbose`: is logging level flag. If it is set to 0 (or completely ignored), the simulation will only output the time execution time of simulation. Otherwise, the simulation will additionally output the initial and last positions of boids for debugging purposes.

4. Example command:
```
./swarm_sequential.run 128 0.3
```
**Output:** 
```
Average execution time: 1.833803 seconds
```

5. Run the following command to execute **parallel** simulation of swarm behavior:

```
./swarm_parallel.run <num_trheads> <sqrt(number_of_boids)> <fraction of obstacles> <verbose>
```
where:
- `<num_trheads>`: is the number of threads to be used by OpenMP.
- `<sqrt(number_of_boids)>`: is the square root of number of boids in the simulation.
- `<fraction of obstacles>`: is a number in the range [0, 1] describing the probability of having an obstacle instead of a boid in a given grid cell.
- `verbose`: is logging level flag. If it is set to 0 (or completely ignored), the simulation will only output the time execution time of simulation. Otherwise, the simulation will additionally output the initial and last positions of boids for debugging purposes.

6. Example command:
```
./swarm_parallel.run 4 128 0.3
```
**Output:** 
```
Average execution time: 1.227074 seconds
```

7. You can clean the executables using the following command
```
make clean
```
