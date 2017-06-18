#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>
#include <unistd.h>     // Header file for sleeping.
#include <string.h>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <math.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "constants.h"
#include "Simulation.h"
#include "dynamic.h"
#include <iostream>

/* ASCII code for the escape key. */
#define ESCAPE 27

char map0[100] = "maps/scene0.vdb";
char map1[100]= "maps/scene1.vdb";
char map2[100] = "maps/scene2.vdb";
char map3[100] = "maps/scene3.vdb";

Flocking* flockDisplay;
Scene* sceneDisplay;

char* getMapForLevel(int level){
  if(level == 0)
    return map0;
  else if (level == 1)
    return map1;
  else if (level == 2)
    return map2;
  else if (level == 3)
    return map3;
  return map0;
}

int simMain(int argc, char* argv[]){
    if(argc<4)
    {
        printf("Ideally these are the parameters you should be passing to run the solver\n");
        printf("%s <sleep_time(ms)> <sheep_count> <boundary_padding> <random_seed> <level>\n", argv[0]);
        exit(0);
        return 1;
    }

    // The command line parameters for this would look like this:
    char* mapFile;  //path to the vdb file
    char* sleep_time = argv[1];  //eventually you'll make this 0 to see how fast your solver really is.
    char* sheep_count = argv[2];
    char* boundary_padding = argv[3];
    char* rand_seed = argv[4];
    char* clevel = argv[5];

    cout << "Command line parameters passed to the program: " << endl;
    cout << argv[1] << endl;
    cout << argv[2] << endl;
    cout << argv[3] << endl;
    cout << argv[4] << endl;
    cout << argv[5] << endl;

    level = stoi(clevel);
    long sleepTime = stoi(sleep_time);
    int sheepCount = stoi(sheep_count);
    int boundaryPadding = stoi(boundary_padding);
    int randSeed = stoi(rand_seed);

    mapFile = getMapForLevel(level);
    cout << "Simulating for level: " << level << endl;

    //Provide appropriate values for these:
    float maxSpeed = 0.5;
    float maxForce = 0.01;
    float flockSepWeight = 1.5;
    float flockAliWeight = 0.1;
    float flockCohWeight = 1.0;
    float collisionWeight = 0;
    float flockSepRadius = 50;
    float flockAliRadius = 250;
    float flockCohRadius = 100;
    float destWeight = 0;

    Simulation simulation;
    simulation.loadScene(mapFile);
    simulation.init(
      sleepTime,
      sheepCount,
      boundaryPadding,
      maxSpeed,
      maxForce,
      flockSepWeight,
      flockAliWeight,
      flockCohWeight,
      collisionWeight,
      flockSepRadius,
      flockAliRadius,
      flockCohRadius,
      destWeight,
      randSeed
    );

    flockDisplay = simulation.getFlockHandle();
    sceneDisplay = simulation.getSceneHandle();

    simulation.run();
    std::cout << "Total Simulation time: " << simulation.totalTime() << std::endl;

    exit(0);
    return 0;
}

int main(int argc, char **argv){
    flockDisplay=NULL;
    sceneDisplay=NULL;

    std::thread simThread(simMain, argc, argv);
    usleep(1000);
    levelHandler(level);

    while(true){} //To keep the main loop running

    return 0;
}
