#pragma once

#ifdef __LINUX_COMPILE
#include<memory.h>
#endif

template <class T>
class Grid
{
public:
	Grid(unsigned int x, unsigned int y, T* data)
	{
		mData = data;
		mMaxX = x;
		mMaxY = y;
	}

	unsigned int getMaxX() const
	{
		return mMaxX;
	}

	unsigned int getMaxY() const
	{
		return mMaxY;
	}

	T& getValue(unsigned int x, unsigned int y)
	{
		return mData[y*mMaxX + x];
	}

	~Grid() 
	{
		delete[] mData;
	}

	Grid(const Grid& grid) 
	{
		mMaxX = grid.mMaxX;
		mMaxY = grid.mMaxY;
		mData = new T[mMaxY * mMaxX];
		memcpy(mData, grid.mData, sizeof(T) * mMaxX * mMaxY);
	}
private:
	T* mData;
	unsigned int mMaxX;
	unsigned int mMaxY;
};