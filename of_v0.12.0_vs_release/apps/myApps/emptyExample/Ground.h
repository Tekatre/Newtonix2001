#pragma once
#include "Particule.h"
class Ground
{
	int x;
	int y;
	int z;



public:
	int width = 5000;
	int height = 50;
	int depth = 5000;
	float restitution = 0.5f;
	Ground();
	~Ground();
	void setX(int x);
	void setY(int y);
	void setZ(int z);
	void setXYZ(int x, int y, int z);
	float getX();
	float getY();
	float getZ();
	float getW();
	float getH();
	float getD();

	Particule resolveCollision(Particule p, float duration);

};

