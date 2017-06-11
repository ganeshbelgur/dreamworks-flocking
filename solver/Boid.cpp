#include "Boid.h"
#include <iostream>
#include <cstdlib>
#include <cmath>
/*
Add functions needed to create a working flock.
*/

float generateRandom(float x, float y){
  return x + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(y-x)));
}

Boid::Boid(
  int x,
  int y,
  int xbound,
  int ybound,
  int mboundaryPadding,
  float mmaxSpeed,
  float mmaxForce,
  float mflockSepWeight,
  float mflockAliWeight,
  float mflockCohWeight,
  float mflockSepRadius,
  float mflockAliRadius,
  float mflockCohRadius
){
    loc.setval(x,y);
	  vel.setval(0.1, 0.1);
	  acc.setval(0, 0);
    r = 3.0;
    orient = (float)randomRange(0, 360);
    endCorner.setval(xbound,ybound);
    reachedDestination = false;
    hitObstacle = false;

    boundaryPadding = mboundaryPadding;
    maxSpeed = mmaxSpeed;
    maxForce = mmaxForce;
    flockSepWeight = mflockSepWeight;
    flockAliWeight = mflockAliWeight;
    flockCohWeight = mflockCohWeight;
    flockSepRadius = mflockSepRadius;
    flockAliRadius = mflockAliRadius;
    flockCohRadius = mflockCohRadius;
}

// Method to update location
void Boid::update(vector<Boid> &boids, Vec2f destination) {

	flock(boids, destination);

    vel *= maxSpeed;
    loc += vel;
    //acc.setval(0,0);  // Resetval accelertion to 0 each cycle
    orient = (float)atan2(vel.y,vel.x) * 180/PI + generateRandom(-20.0, 20.0);

    boundCheck(boundaryPadding);
}

void Boid::boundCheck(int padding){

  if(loc.x>endCorner.x-padding)
  {
      loc.x=endCorner.x-padding;
      vel.x=-vel.x;

  }

  else if(loc.x<0+padding)
   {
       loc.x=0+padding;
       vel.x=-vel.x;
   }

  if(loc.y>endCorner.y-padding)
  {
      loc.y=endCorner.y-padding;
      vel.y=-vel.y;
  }

  else if(loc.y<0+padding)
  {
      loc.y=0+padding;
      vel.y=-vel.y;
  }
}

//Flock your boids here
void Boid::flock(vector<Boid> &boids, Vec2f destination){
  int neighbourAlignmentCount = 0;
  int neighbourCohesionCount = 0;
  int neighbourSeparationCount = 0;

  Vec2f alignmentVector(0.0, 0.0);
  Vec2f cohesionVector(0.0, 0.0);
  Vec2f separationVector(0.0, 0.0);

  for(int i = 0; i < boids.size(); i++){
    float distance = dist(loc, boids[i].loc);

    if(distance < flockAliRadius && distance != 0.0f){
      alignmentVector.x += boids[i].vel.x;
      alignmentVector.y += boids[i].vel.y;
      neighbourAlignmentCount++;
    }

    if(distance < flockCohRadius && distance != 0.0f){
      cohesionVector.x += boids[i].loc.x;
      cohesionVector.y += boids[i].loc.y;
      neighbourCohesionCount++;
    }

    if(distance < flockSepRadius && distance != 0.0f){
      separationVector.x += boids[i].loc.x - loc.x;
      separationVector.y += boids[i].loc.y - loc.y;
      neighbourSeparationCount++;
    }
  }

  alignmentVector.x /= neighbourAlignmentCount;
  alignmentVector.y /= neighbourAlignmentCount;
  alignmentVector.normalize();

  cohesionVector.x /= neighbourCohesionCount;
  cohesionVector.y /= neighbourCohesionCount;
  cohesionVector = Vec2f(cohesionVector.x - loc.x, cohesionVector.y - loc.y);
  cohesionVector.normalize();

  separationVector.x /= neighbourSeparationCount;
  separationVector.y /= neighbourSeparationCount;
  separationVector.x *= -1;
  separationVector.y *= -1;
  separationVector.normalize();

  Vec2f resultant(0.0, 0.0);
  resultant.x += \
    (alignmentVector.x * flockAliWeight) + \
    (cohesionVector.x * flockCohWeight) + \
    (separationVector.x * flockSepWeight) + \
    (destination.x - loc.x) * 0.01;

  resultant.y += \
    (alignmentVector.y * flockAliWeight) + \
    (cohesionVector.y * flockCohWeight) + \
    (separationVector.y * flockSepWeight) + \
    (destination.y - loc.y) * 0.01;

  vel += Vec2f(resultant.x, resultant.y);
  std::cout << "destination.x: " << destination.x << endl << "destination.y: " << destination.y << endl;
  std::cout << "alignmentVector.x: " << alignmentVector.x << endl << "alignmentVector.y: " << alignmentVector.y << endl;
  std::cout << "cohesionVector.x: " << cohesionVector.x << endl << "cohesionVector.y: " << cohesionVector.y << endl;
  std::cout << "separationVector.x: " << separationVector.x << endl << "separationVector.y: " << separationVector.y << endl;
  std::cout << "resultant.x: " << resultant.x << endl << "resultant.y: " << resultant.y << endl;
}

bool Boid::isHit(int x, int y, int radius) {

    int range = 1;//calculation error range
    int dist = radius + range;
    if(pow((x-loc.x),2)+pow((y-loc.y),2) < (dist * dist) ){
        return true;
    }
    return false;
}


float Boid::dist(Vec2f v1,Vec2f v2)
{
    return v1.distance(v2);
}

float Boid::clamp(float val, float minval, float maxval)
{
    if(val<minval)
        return minval;
    else if (val>maxval)
        return maxval;
    else
        return val;
}
