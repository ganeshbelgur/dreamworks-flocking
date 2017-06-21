# ABAI Hackathon 2016 - DreamWorks Dedicated Unit

## Flocking Simulation
### Problem Statement
This is a sample stub, to help you get started with the problem. You do not need to use this but make sure you send the data required in the right format for Blender. We are using Blender as our viewport. A server listens on localhost:8010 from Blender, expecting a vector of 'Boid' objects.

### Send data to Blender
It is mandatory to use the function 'Simulation.ToBlender()' for visualization.
Mandatory fields to populate
- vector<Boid> boids
- boids.loc
- boids.orient
- boids.reachedDestination

### Levels
##### Level 0
Make the sheeps travel from the source to the destination. Make sure they follow the rules of flocking! Populate the vector of 'Boid'.

##### Level 1
The sheep must navigate static obstacles, as they go from source to destination, while maintaining the flock. Use Sccene.h to access the start and destination. The scene/obstacles information is supplied.

##### Level 2
There is a moving obstacle now. Remember the sheep code. Use the vector 'obstacles' to get your dynamic obstacle position at each time step.

##### Level 3
Navigate to the destination by crossing more obstacles. How much do your sheeps love fellowship?

### Compiling Instructions
1. Build your code - make
2. Run the run_scene"level_number".sh

If you get linker errors, make sure you set LD_LIBRARY_PATH to path of the 'libdynamic.so' file.

### Collision Detection
##### Static Obstacles
1. Use the Scene.h objects/pointers in the files to access start/end positions and other data. Flocking.cpp has a handle to Scene object called sceneMap. getCell(x,y) tells you if there is an obstacle in (x, y) or not.
2. Use collisionSDF[x][y] to know how far away (x, y) is from the nearest obstacle. Value of 0 mean (x, y) is on the edge of the obstacle and negative means it's inside: Flocking.cpp
3. Use the partialDerivatives[x][y] to know the direction away from the nearest osbtacle at position (x, y): Flocking.cpp

##### Dynamic Obstacles
1. Use the obstacle vector in "Constants.h" to access the location of the dynamic obstacle.

- Notes/Hints: You don't have to bother about VDBs and map handling. Just focus on working on the boids and flocking.

## My Submission
Flocking simulation is based on the algorithm presented by Craig Reynolds in 1987. The algorithm revovles mainly around three important rules called Separation, Alignment and Cohesion. Using these three rules, a steering vector is derived. This vector drives the simulation. A very weak destination steering vector is also added to ensure that the flock reaches the barn.

A collision detection method using the Signed Distance Function is used to avoid static obstacles as the flock wanders around. In one of the scenes, a dynamic obstacle (a tractor) is avoided by applying a force, on each Boid, in the direction opposite to the direction in which a Boid approaches the obstacle.

Static Collisions:
![alt tag](https://github.com/ganeshbelgur/dreamworks-flocking/blob/master/screenshots/static-collisions.png)

Dynamic Collisions:
![alt tag](https://github.com/ganeshbelgur/dreamworks-flocking/blob/master/screenshots/dynamic-collisions.png)

###### Don't blame me if the sheeps are reluctant to go to the barn. I've designed them to be that way! They will take their own time. :)

### References:
- C. W. Reynolds, “Flocks, herds and schools: a distributed behavioral model.” Computer Graphics, 2 1 (4):25-34, 1987.
- http://www.red3d.com/cwr/boids/
- https://github.com/usama-ghufran/steerQuest_ABAI
