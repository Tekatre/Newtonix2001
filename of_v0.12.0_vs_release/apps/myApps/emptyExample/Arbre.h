#pragma once

#include "RigidBody.h"
#include <vector>
using namespace std;
class Arbre
{
	public:
	Arbre();
	Arbre(int id);
	~Arbre();
	//struct of the tree
	vector<Arbre*> children;
	int id;
	vector<RigidBody*> bodies;


	void addChildren(Arbre* child);
	void setBodies(vector<RigidBody*> bodies);
};

