#pragma once

#include "Vector.h"
#include <vector>

using namespace math;
using namespace std;

/* PLEASE READ!!!
This class can be used to define the unit of Flocking - Boid.
*/

class Boid {
public:

	/* This is the world space co-ordinates of the Boids.
	 Poulate this to view in Blender*/

	//Set these variables appropriately. These are required.
	Vec2f loc;
	bool reachedDestination;
	float orient;

	Vec2f vel,acc;
	Vec2i endCorner;

  float r;
	bool hitObstacle;
	int boundaryPadding;
	float maxSpeed;
	float maxForce;
	float flockSepWeight;
	float flockAliWeight;
	float flockCohWeight;
	float flockSepRadius;
	float flockAliRadius;
	float flockCohRadius;

	Boid(
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
	);

  float dist(Vec2f v1,Vec2f v2);
  float clamp(float val, float minval, float maxval);
	bool update(vector<Boid> &boids, Vec2f destination);
  void boundCheck(int padding);
  void flock(vector<Boid> &boids, Vec2f destination);
  bool isHit(int x,int y, int radius);
	void applyForce(Vec2f force);
	Vec2f seek(Vec2f target);
	Vec2f separate(vector<Boid> &boids);
	Vec2f align(vector<Boid> &boids);
	Vec2f cohesion(vector<Boid> &boids);
};
