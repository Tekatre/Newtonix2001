#include "RigidContactGenerator.h"

RigidContactGenerator::RigidContactGenerator()
{
}

RigidContactGenerator::~RigidContactGenerator()
{
}

void RigidContactGenerator::CreateContact(BSP* bsp)
{
	//parcourir l'arbre, regarder si une feuille contient 2 bodies
	if (!bsp->isLeaf()) {
		CreateContactIteration(bsp);
	}
	


}

void RigidContactGenerator::CreateContactIteration(BSP* bsp)
{
	if (bsp->isLeaf()) {
		if (bsp->bodies.size() > 1) {
			//create every pair of contact
			for (int i = 0; i < bsp->bodies.size() - 1; i++)
			{
				for (int j = i + 1; j < bsp->bodies.size(); j++)
				{
					RigidContact* contact = new RigidContact();
					contact->body[0] = bsp->bodies[i];
					contact->body[1] = bsp->bodies[j];
					contact->contactNormal = bsp->bodies[i]->getPosition() - bsp->bodies[j]->getPosition();
					contact->contactNormal.normalize();
					contact->penetration = bsp->bodies[i]->getPosition().distance(bsp->bodies[j]->getPosition());
					contact->restitution = 0.5f;
					contacts[contactsCount] = *contact;
				}
			}
		}
	}
	else {
		CreateContactIteration(bsp->left);
		CreateContactIteration(bsp->right);
	}

}

RigidContact* RigidContactGenerator::getContacts()
{
	return contacts;
}