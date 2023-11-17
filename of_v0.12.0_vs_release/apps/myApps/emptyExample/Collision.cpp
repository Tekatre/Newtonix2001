#include "Collision.h"
#include <math.h>

Collision::Collision()
{
	// Constructeur par défaut
}

Collision::~Collision()
{
	// Destructeur
}

bool Collision::checkCollisionWithGround(Particule p, Ground g)
{
	//check if the particle is on the ground, it should came from above the ground, particle has a radius of p.getRayon() and ground has a height g.getH()
	if (p.getPosition().getY() - p.getRayon() <= g.getY() + g.height / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool Collision::checkCollision(Particule* p1, Particule* p2)
{
	// Check if the distance between the two particles is less than the sum of their radius
	double distance = sqrt(pow(p1->getPosition().getX() - p2->getPosition().getX(), 2) + pow(p1->getPosition().getY() - p2->getPosition().getY(), 2) + pow(p1->getPosition().getZ() - p2->getPosition().getZ(), 2));
	if (distance <= p1->getRayon() + p2->getRayon())
	{
		return true;
	}
	else
	{
		return false;
	}
}

