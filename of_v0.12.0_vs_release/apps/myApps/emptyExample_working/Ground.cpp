#include "Ground.h"
#include <ofGraphics.h>

Ground::Ground()
{
	// Constructeur par défaut
	x = 0;
	y = 0;
	z = 0;
}

Ground::~Ground()
{
	// Destructeur
}


void Ground::setX(int x)
{
	// Mutateur
	this->x = x;
}

void Ground::setY(int y)
{
	// Mutateur
	this->y = y;
}

void Ground::setZ(int z)
{
	// Mutateur
	this->z = z;
}

void Ground::setXYZ(int x, int y, int z)
{
	// Mutateur
	this->x = x;
	this->y = y;
	this->z = z;
}

float Ground::getX()
{
	// Accesseur
	return x;
}

float Ground::getY()
{
	// Accesseur
	return y;
}

float Ground::getZ()
{
	// Accesseur
	return z;
}

float Ground::getW()
{
	// Accesseur
	return width;
}

float Ground::getH()
{
	// Accesseur
	return height;
}

float Ground::getD()
{
	// Accesseur
	return depth;
}

Particule Ground::resolveCollision(Particule p, float duration)
{
	//put the particle on the ground if it is below the ground and invert its velocity
	if (p.getPosition().getY() - p.getRayon() < y + height/2 && p.getPosition().getX() <= x+width/2 && p.getPosition().getX() >= x - width/2  && p.getPosition().getZ() <= z + depth/2 && p.getPosition().getZ() >= z - depth/2)
	{
		p.setPosition(Vecteur3D(p.getPosition().getX(), y + height/2 + p.getRayon(), p.getPosition().getZ()));
		p.setVelocite(Vecteur3D(p.getVelocite().getX(), -p.getVelocite().getY() * restitution, p.getVelocite().getZ()));

	}
	return p;
}