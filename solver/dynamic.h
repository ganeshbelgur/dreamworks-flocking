#include <iostream>
#include <vector>
#include "Vector.h"
#include "Boid.h"
using namespace std;
using namespace math;

int signum(float);
//vector<Vec3f> generatePath(Vec3f, Vec3f);

class DynamicObj{


public:
	vector<Vec3f> holes;
	vector<Vec3f> objPath;
	vector<Vec3f> generatePath(Vec3f, Vec3f);
	vector<Vec3f> getDynamicBox();
	vector<Vec3f> getDiagonal();

	bool detectDynamicCollision(vector<Boid> boids);	
};

bool colDetect(Boid);
void levelZero();
void levelOne();
void leveTwo();

void levelHandler(int);
void generateObstacles(int);
void initObstacles(int);
