#include "Flocking.h"
#include "Constants.h"

int Flocking::update()
{
  bool stopSimulation = false;
  for(int i = 0; i < boids.size(); i++){
      stopSimulation = boids[i].update(boids, destination, collisionSDF, partialDerivaties);
      if (stopSimulation)
        break;
  }

  obstacles.clear();
  return !stopSimulation;
}

void Flocking::addBoid(int x, int y){
  boids.push_back(
    Boid(
      x,
      y,
      x_bound,
      y_bound,
      boundaryPadding,
    	maxSpeed,
			maxForce,
			flockSepWeight,
			flockAliWeight,
			flockCohWeight,
			flockSepRadius,
			flockAliRadius,
			flockCohRadius
    )
  );
}

void Flocking::removeBoid(int x, int y, int radius)
{
    int i;
    for (i = 0; i < boids.size(); i++)
    {
      if(boids[i].isHit(x, y, radius))
      {
          boids.erase(boids.begin() + i);
      }
    }
}

int Flocking::flockSize()
{
  return boids.size();
}

void Flocking::setBounds(int x, int y)
{
  x_bound = x;
  y_bound = y;
}

void Flocking::setDestination(int x, int y, float area)
{
    destination.setval((float)x,(float)y);
    destinationArea = area;
    destinationSeek = destination;
}

void Flocking::setDestination(Vec2f dest,float area)
{
    destination = dest;
    destinationArea = area;
}

void Flocking::setSceneMap(Scene* scene)
{
    sceneMap = scene;
}

vector<Boid> Flocking::getBoids()
{
    return boids;
}

void Flocking::calculatePartialDerivaties()
{
    partialDerivaties = (Vec2f**)malloc(sizeof(Vec2f*) * x_bound);
    for(int i=0; i < x_bound; i++)
    {
        partialDerivaties[i] = (Vec2f*)malloc(sizeof(Vec2f*) * y_bound);
        memset(partialDerivaties[i], 0, y_bound);
    }

    int padding = 1;

    for(int i = padding; i < x_bound - padding; i++)
    {
        for(int j = padding; j < y_bound - padding; j++)
        {
            float dify = 0;
            if(collisionSDF[i][j] == 999 || collisionSDF[i][j - padding] == 999)
                dify = 0;
            else
                dify = collisionSDF[i][j] - collisionSDF[i][j - padding];

            float difx = 0;
            if(collisionSDF[i][j] == 999 || collisionSDF[i - padding][j] == 999)
                difx = 0;
            else
                difx = collisionSDF[i][j] - collisionSDF[i - padding][j];

            partialDerivaties[i][j].setval(difx, dify);
        }
    }
}

void Flocking::useCollisionSDF(bool val)
{
    useCollisionFromSDF = val;

    if(useCollisionFromSDF)
    {
        collisionSDF = sceneMap -> getSDFhandle();
    }
}

void Flocking::setSimulationParameters(
	int	mboundaryPadding,
  float	mmaxSpeed,
  float mmaxForce,
  float mflockSepWeight,
	float mflockAliWeight,
	float mflockCohWeight,
	float mcollisionWeight,
	float mflockSepRadius,
	float mflockAliRadius,
	float mflockCohRadius,
  float	mdestWeight)
  {
	boundaryPadding = mboundaryPadding;
	maxSpeed = mmaxSpeed;
	maxForce = mmaxForce;
	flockSepWeight = mflockSepWeight;
	flockAliWeight = mflockAliWeight;
	flockCohWeight = mflockCohWeight;
	collisionWeight = mcollisionWeight;
	flockSepRadius = mflockSepRadius;
	flockAliRadius = mflockAliRadius;
	flockCohRadius = mflockCohRadius;
	destWeight = mdestWeight;
}
