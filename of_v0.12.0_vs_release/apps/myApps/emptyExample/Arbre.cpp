#include "Arbre.h"



Arbre::Arbre()
{
}
Arbre::Arbre(int id)
{
	this->id = id;
}

Arbre::~Arbre()
{
}

void Arbre::addChildren(Arbre* child)
{
	this->children[sizeof(this->children)] = child;
}

void Arbre::setBodies(vector<RigidBody*> bodies)
{
	this->bodies = bodies;
}



