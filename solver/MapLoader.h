#pragma once
#include "Vector.h"

using namespace math;

class MapLoader
{
public:
    
    bool** loadVDBMap(char* filename);
    Vec2f getStartPosition();
    Vec2f getEndPosition();
    float** getSDF(); 
    MapLoader();
    unsigned int getStartRadius();
    unsigned int getEndRadius();
    unsigned int gety_boundary();
    unsigned int getx_boundary();


private:
    bool** mapData;         
    Vec2f  posStart;        			// The starting point
    Vec2f  posEnd; 		         		// The ending point
    float startRadius,endRadius;		// Region around the start and end points within which the fishes will spawn and die respectively
    bool loaded;						// to keep track if the map has been loaded
    unsigned int x_boundary, y_boundary;// the limits of the map
	float** grid_array;					// The array to store the SDF from the vdb file. The grid is called "SDF"
};

