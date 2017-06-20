#include <cstring>
#include <openvdb/openvdb.h>
#include <stdlib.h>
#include <fstream>

#include "MapLoader.h"
using namespace std;

bool** MapLoader::loadVDBMap(char* filename)
{
  cout << "Loading VDB map... " << filename << endl;
	openvdb::initialize();

	// Create a VDB file object.
	openvdb::io::File file(filename);

	// Open the file. This reads the file header, but not any grids.
	file.open();

	openvdb::GridBase::Ptr baseGrid;
	baseGrid = file.readGrid("SDF");
	file.close();

	// Cast the generic grid pointer to a FloatGrid pointer.
	openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);

  string boundx = grid -> metaValue<string>("boundx");
  string boundy = grid -> metaValue<string>("boundy");
  string startx = grid -> metaValue<string>("startx");
  string starty = grid -> metaValue<string>("starty");
  string start_radius = grid -> metaValue<string>("start_radius");
  string endx = grid -> metaValue<string>("endx");
  string endy = grid -> metaValue<string>("endy");
  string end_radius = grid -> metaValue<string>("end_radius");

  x_boundary = stoi(boundx);
  y_boundary = stoi(boundy);

  startRadius = stof(start_radius);
  endRadius = stof(end_radius);

  int x_bound = x_boundary;
  int y_bound = y_boundary;
  int z_bound = 0;

  // Create the map data
  mapData = (bool**)malloc(sizeof(bool*) * y_boundary);
  grid_array = (float**)malloc(sizeof(float*) * y_boundary);

  for(int i = 0; i < y_boundary; i++)
  {
  	grid_array[i] = (float*)malloc(sizeof(float) * x_boundary);
    mapData[i] = (bool*)malloc(sizeof(bool) * x_boundary);
    memset(mapData[i], true, x_boundary);
    memset(grid_array[i], 999, x_boundary);
  }

	openvdb::FloatGrid::Accessor accessor = grid -> getAccessor();

	for(int x = 0; x < x_bound; x++)
	for(int y = 0; y < y_bound; y++)
  {
    openvdb::Coord pos(x, y, z_bound);
    grid_array[x][y] = accessor.getValue(pos);

    int padding = 5;
    if(grid_array[x][y] <= padding)
		    mapData[x][y] = false;

    grid_array[x][y] -= padding;
  }

  posStart = math::Vec2f(stoi(startx), stoi(starty));
  posEnd = math::Vec2f(stoi(endx),stoi(endy));
  loaded = true;
  return mapData;
}

float** MapLoader::getSDF()
{
  return grid_array;
}

MapLoader::MapLoader()
{
  this -> loaded = false;
  this -> mapData = nullptr;
}

Vec2f MapLoader::getStartPosition()
{
  return posStart;
}

Vec2f MapLoader::getEndPosition()
{
  return posEnd;
}

unsigned int MapLoader::gety_boundary()
{
  return y_boundary;
}

unsigned int MapLoader::getx_boundary()
{
  return x_boundary;
}

unsigned int MapLoader::getStartRadius()
{
  return startRadius;
}

unsigned int MapLoader::getEndRadius()
{
  return endRadius;
}
