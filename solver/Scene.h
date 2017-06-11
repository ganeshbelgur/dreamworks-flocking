#pragma once

#include "Vector.h"
#include "Grid.h"

using namespace math;

struct Cell
{
	bool passable;
};

class Scene
{
public:
	Scene(const Vec2f& startPosition, const Vec2f& endPosition, const Grid<bool>& grid,unsigned int startRadius,unsigned int endRadius)
		:mStartPosition(startPosition)
		,mEndPosition(endPosition)
		,mGrid(grid)
		,mStartRadius(startRadius)
		,mEndRadius(endRadius)
	{
	}

	Vec2f getStartPosition() const
	{
		return mStartPosition;
	}
	Vec2f getEndPosition() const
	{
		return mEndPosition;
	}

    float getStartRadius() const
	{
		return mStartRadius;
	}
	float getEndRadius() const
	{
		return mEndRadius;
	}

	const Grid<bool>& getGrid() const
	{
		return mGrid;
	}
	bool getCell(unsigned int x, unsigned int y)
	{
		return mGrid.getValue(x, y);
	}
	Vec2i getBounds()
	{
		return Vec2i(mGrid.getMaxX(),mGrid.getMaxY());
	}
	float** getSDFhandle()
	{
		return sdfPointer;
	}
	void setSDFhandle(float** sdfHandle)
	{
		sdfPointer=sdfHandle;
	}
private:
	Grid<bool> mGrid;
	Vec2f mStartPosition;
	Vec2f mEndPosition;
	float mStartRadius,mEndRadius;
	float** sdfPointer;
};
