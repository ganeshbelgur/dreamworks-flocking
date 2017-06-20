#pragma once

#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <chrono>
#include <thread>

#include "Scene.h"
#include "Vector.h"
#include "Flocking.h"
#include "MapLoader.h"

using namespace math;

class Simulation
{
	public:
		void loadScene(char* mapFile);
		void init(
			long msleepTime,
		  int	mSheepCount,
		  int	mboundaryPadding,
		  float	mmaxSpeed,
		  float	mmaxForce,
		  float	mflockSepWeight,
		  float	mflockAliWeight,
		  float	mflockCohWeight,
		  float	mcollisionWeight,
		  float	mflockSepRadius,
			float	mflockAliRadius,
			float	mflockCohRadius,
			float	mdestWeight,
			int	mrandSeed
		);
		bool frame();
		void run();
		long long totalTime();
		Flocking* getFlockHandle();
		Scene* getSceneHandle();

		Simulation()
		{
		    x_bound = 200;
		    y_bound = 200;
	  }

	private:
	  Flocking flock;
		Scene* mScene;
		MapLoader ml;
		std::vector<Vec2f> mPath;

		std::fstream fd;
		std::chrono::steady_clock::time_point mStartTime;
		std::chrono::steady_clock::time_point mEndTime;

		unsigned int x_bound;
	  unsigned int y_bound;
	  Vec2f startPosition;
		Vec2f endPosition;
		float startPositionRadius;
		float endPositionRadius;

		//init variables
		long sleepTime;
	  int sheepCount;
	  int boundaryPadding;
	  float maxSpeed;
	  float maxForce;
		float flockSepWeight;
		float flockAliWeight;
		float flockCohWeight;
	  float collisionWeight;
		float flockSepRadius;
		float flockAliRadius;
		float flockCohRadius;
	  float destWeight;
	  int randSeed;
};
