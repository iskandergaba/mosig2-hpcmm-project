# High Performance Computing for Mathematical Models - Swarm Behavior Simulation Project
## Team Members
+ Iskander Gaba
+ Hadi Dayekh

## How to run
1. Compile the executable files using the following command
```
make
```

You should notice the appearance of two new executables: `swarm_parallel.run` and `swarm_sequential.run`. To clean the project’s directory from these executable files, simply run:
```
make clean
```

2. Run the following command to execute **sequential** simulation of swarm behavior:

```
./swarm_sequential.run <sqrt(number_of_boids)> <fraction_of_obstacles> <verbose>
```
The parameters in the command above are defined as follows:
- `<sqrt(number_of_boids)>`: The square root of number of boids in the simulation.
- `<fraction_of_obstacles>`: A number in the range [0, 1] describing the probability of havingan obstacle instead of a boid in a given grid cell.
- `<verbose>`: A logging level flag. If it is set to 0 (or completely ignored), the simulation willonly output the time execution time of simulation. Otherwise, the simulation will additionallyoutput the initial and last positions of boids for debugging purposes.

3. For example, if the user wants to conduct a sequential swarm behavior simulation on 128<sup>2</sup> boid swith a probability of 0.3 of each boid being just an obstacle, then this is the command they need to execute:
```
./swarm_sequential.run 128 0.3
```
**Sample Output:** 
```
Average execution time: 1.833803 seconds
```

4. Run the following command to execute **parallel** simulation of swarm behavior:

```
./swarm_parallel.run <num_trheads> <sqrt(number_of_boids)> <fraction of obstacles> <verbose>
```
The parameters in the command above are defined as follows:
- `<num_trheads>`: The number of threads to be used by OpenMP.
- `<sqrt(number_of_boids)>`: The square root of number of boids in the simulation.
- `<fraction_of_obstacles>`: A number in the range [0, 1] describing the probability of havingan obstacle instead of a boid in a given grid cell.
- `<verbose>`: A logging level flag. If it is set to 0 (or completely ignored), the simulation willonly output the time execution time of simulation. Otherwise, the simulation will additionallyoutput the initial and last positions of boids for debugging purposes.

5. For example, if the user wants to conduct a parallel swarm behavior simulation on 128<sup>2</sup> boids with a probability of 0.3 of each boid being just an obstacle and using 4 threads, then this is the command they need to execute:
```
./swarm_parallel.run 4 128 0.3
```
**Sample Output:** 
```
Average execution time: 1.227074 seconds
```
