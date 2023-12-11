#include "Octree.h"

Octree::Octree()
{
	this->tree = new Arbre(0);
}

Octree::~Octree()
{
}

void Octree::GenerateOctree(vector<RigidBody*> rigidBodies)
{

	GenerationIteration(rigidBodies, tree, 0);
	cout << "fin de la generation de l'octree" << endl;


	
}

void Octree::GenerationIteration(vector<RigidBody*> listRigid, Arbre* currenttree, int profondeur)
{
	if (profondeur < 5)
	{
		//on divise en 8
		//on récupère d'abord la position la plus éloignée en x, y et z
		float maxX = 0;
		float maxY = 0;
		float maxZ = 0;
		float minX = 0;
		float minY = 0;
		float minZ = 0;

		for (int i = 0; i < listRigid.size(); i++)
		{
			if (listRigid[i]->getPosition().getX() > maxX)
			{
				maxX = listRigid[i]->getPosition().getX();
			}
			if (listRigid[i]->getPosition().getY() > maxY)
			{
				maxY = listRigid[i]->getPosition().getY();
			}
			if (listRigid[i]->getPosition().getZ() > maxZ)
			{
				maxZ = listRigid[i]->getPosition().getZ();
			}
			if (listRigid[i]->getPosition().getX() < minX)
			{
				minX = listRigid[i]->getPosition().getX();
			}
			if (listRigid[i]->getPosition().getY() < minY)
			{
				minY = listRigid[i]->getPosition().getY();
			}
			if (listRigid[i]->getPosition().getZ() < minZ)
			{
				minZ = listRigid[i]->getPosition().getZ();
			}
		}

		//on calcule le centre de la boite
		float centerX = (maxX + minX) / 2;
		float centerY = (maxY + minY) / 2;
		float centerZ = (maxZ + minZ) / 2;
		Vecteur3D center = Vecteur3D(centerX, centerY, centerZ);

		//on crée les 8 enfants
		Arbre* children = new Arbre[8];
		for (int i = 0; i < 8; i++)
		{
			children[i] = Arbre(i); //les ids sont pas bons
		}

		//répartir les rigid body dans les enfants

		for (int i = 0; i < listRigid.size(); i++)
		{
			if (listRigid[i]->getPosition().getX() < center.getX() && listRigid[i]->getPosition().getY() < center.getY() && listRigid[i]->getPosition().getZ() < center.getZ())
			{
				children[0].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() > center.getX() && listRigid[i]->getPosition().getY() < center.getY() && listRigid[i]->getPosition().getZ() < center.getZ())
			{
				children[1].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() < center.getX() && listRigid[i]->getPosition().getY() > center.getY() && listRigid[i]->getPosition().getZ() < center.getZ())
			{
				children[2].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() > center.getX() && listRigid[i]->getPosition().getY() > center.getY() && listRigid[i]->getPosition().getZ() < center.getZ())
			{
				children[3].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() < center.getX() && listRigid[i]->getPosition().getY() < center.getY() && listRigid[i]->getPosition().getZ() > center.getZ())
			{
				children[4].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() > center.getX() && listRigid[i]->getPosition().getY() < center.getY() && listRigid[i]->getPosition().getZ() > center.getZ())
			{
				children[5].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() < center.getX() && listRigid[i]->getPosition().getY() > center.getY() && listRigid[i]->getPosition().getZ() > center.getZ())
			{
				children[6].bodies.push_back(listRigid[i]);
			}
			else if (listRigid[i]->getPosition().getX() > center.getX() && listRigid[i]->getPosition().getY() > center.getY() && listRigid[i]->getPosition().getZ() > center.getZ())
			{
				children[7].bodies.push_back(listRigid[i]);
			}
		}

		//on ajoute les enfants au parent
		for (int i = 0; i < 8; i++)
		{
			currenttree->addChildren(&children[i]);
			if (currenttree->children[i]->bodies.size()>1)
			{
				//si y'a plus d'un rigid body dans l'enfant on continue a diviser
				GenerationIteration(currenttree->children[i]->bodies, currenttree->children[i], profondeur + 1);
			}
		}
		
	}
	


}