#pragma once
#include "../Particule.h"
#include "../Ground.h"
class Collision
{


public:
	Collision();
	~Collision();
	bool checkCollision(Particule* p1, Particule* p2);
	bool checkCollisionWithGround(Particule p, Ground g);



};

