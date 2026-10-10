#include "BSP.h"

BSP::BSP()
{
}

BSP::~BSP()
{
	// les bodies n'appartiennent pas a l'arbre, seuls les noeuds enfants sont liberes
	delete left;
	delete right;
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
	if (depth <= 0 || bodies.size() < 2)
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

		//si tous les corps chevauchent le plan, la division ne separe rien :
		//ce noeud reste une feuille (sinon on recopierait les memes corps a chaque niveau)
		if (left->bodies.size() == bodies.size() && right->bodies.size() == bodies.size())
		{
			delete left;
			delete right;
			left = nullptr;
			right = nullptr;
			return;
		}

		//un enfant qui contient tous les corps du parent retrouverait exactement le meme plan :
		//on ne le subdivise que s'il contient strictement moins de corps
		if (left->bodies.size() > 1 && left->bodies.size() < bodies.size())
		{
			left->GenerateBSPIteration(depth - 1);
		}
		if (right->bodies.size() > 1 && right->bodies.size() < bodies.size())
		{
			right->GenerateBSPIteration(depth - 1);
		}

		bodies.clear();




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
	// une feuille est un noeud sans enfant (elle peut contenir 0, 1 ou plusieurs corps)
	return left == nullptr && right == nullptr;
}