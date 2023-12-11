#pragma once

#include "Arbre.h"
#include "RigidBody.h"
#include <vector>
using namespace std;
class Octree
{
	private:
	Arbre* tree;


	public:
	Octree();
	~Octree();

	void GenerateOctree(vector<RigidBody*> listRigid);
	void GenerationIteration(vector<RigidBody*> listRigid, Arbre* tree, int profondeur);

};

