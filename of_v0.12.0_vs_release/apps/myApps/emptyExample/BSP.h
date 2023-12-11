#pragma once
using namespace std;
#include <vector>
#include "RigidBody.h"
class BSP
{

	struct Plane {
		Vecteur3D position;
		Vecteur3D normal;
	};


	BSP* left;
	BSP* right;
	vector<RigidBody*> bodies;
	private:
		void GenerateBSPIteration(int depth);
		void addBodyInLeftChild(RigidBody* body);
		void addBodyInRightChild(RigidBody* body);
		
	public:
		void GenerateBSP(vector<RigidBody*> bodies);




	BSP();
	~BSP();
	

};

