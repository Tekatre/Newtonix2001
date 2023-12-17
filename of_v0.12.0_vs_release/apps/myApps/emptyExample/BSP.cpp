#include "BSP.h"

BSP::BSP()
{
}

BSP::~BSP()
{
}

void BSP::GenerateBSP(vector<RigidBody*> Bodies)
{
	this->bodies = Bodies;
	int depth;
 	if (bodies.size() % 2 == 0)
	{
		depth = bodies.size() / 2;
	}
	else
	{
		depth = bodies.size()/ 2 + 1;
	}
	

	GenerateBSPIteration(depth);
	//cout << "BSP generated" << endl;
	
	
}

void BSP:: GenerateBSPIteration(int depth)
{
	if (depth <= 0)
	{
		
		return;
	}
	else
	{
		//searching for the longest distance between two bodies
		float maxDistance = 0;
		int index1 = 0;
		int index2 = 0;
		for (int i = 0; i < bodies.size()-1; i++)
		{
			for (int j = i+1; j < bodies.size(); j++)
			{
				if (i != j)
				{
					float distance = bodies[i]->getPosition().distance(bodies[j]->getPosition());
					if (distance > maxDistance)
					{
						maxDistance = distance;
						index1 = i;
						index2 = j;
					}
				}
			}
		}

		//find the middle point between the two bodies and the vecteur between them
		Vecteur3D middlePoint = (bodies[index1]->getPosition() + bodies[index2]->getPosition()) / 2;
		Vecteur3D vecteur = bodies[index1]->getPosition() - bodies[index2]->getPosition();
		Vecteur3D normal = vecteur.normalize();
		Plane plane;
		plane.position = middlePoint;
		plane.normal = normal;
		left = new BSP();
		right = new BSP();

		
		float c;
		for (int i = 0; i < bodies.size(); i++) {
			c = (bodies[i]->getPosition() - plane.position).ProduitScalaire(plane.normal);
			if (abs(c) >= bodies[i]->getOuterRadius())
			{
				if (c > 0)
				{
					addBodyInRightChild(bodies[i]);
				}
				else
				{
					addBodyInLeftChild(bodies[i]);
				}
			}
			else {
				addBodyInLeftChild(bodies[i]);
				addBodyInRightChild(bodies[i]);
			}
		}

		bodies.clear();

		if (left->bodies.size() > 1)
		{
			left->GenerateBSPIteration(depth - 1);
		}
		if (right->bodies.size() > 1)
		{
			right->GenerateBSPIteration(depth - 1);
		}




	}


	
}

void BSP::addBodyInLeftChild(RigidBody* body)
{
	
	left->bodies.push_back(body);

}

void BSP::addBodyInRightChild(RigidBody* body)
{
	
	right->bodies.push_back(body);

}

bool BSP::isLeaf()
{
	if (bodies.size() != 0 || bodies.size()!=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}