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
					contact->contactNormal = (bsp->bodies[i]->getPosition() - bsp->bodies[j]->getPosition()).normalize();
	
					contact->penetration = bsp->bodies[i]->getOuterRadius() + bsp->bodies[j]->getOuterRadius() - (bsp->bodies[i]->getPosition().distance(bsp->bodies[j]->getPosition()));
					contact->restitution = 0.5f;
					contact->friction = 0.5f;
					contact->worldContactPoint = bsp->bodies[i]->getPosition() - contact->contactNormal * contact->penetration / 2;
					//addContact(contact);
					contacts.push_back(contact);
				}
			}
		}
	}
	else {
		CreateContactIteration(bsp->left);
		CreateContactIteration(bsp->right);
	}

}
//
//RigidContact** RigidContactGenerator::getContacts()
//{
//	return contacts;
//}

vector<RigidContact*> RigidContactGenerator::getContacts()
{

	//faire en sorte qu'il n'y ai pas de double (deux couple comportant bodyA et bodyB)
	for (int i = 0; i < contacts.size(); i++)
	{
		for (int j = i + 1; j < contacts.size(); j++)
		{
			if (contacts[i]->body[0] == contacts[j]->body[0] && contacts[i]->body[1] == contacts[j]->body[1]) {
				contacts.erase(contacts.begin() + j);
			}
			else if (contacts[i]->body[0] == contacts[j]->body[1] && contacts[i]->body[1] == contacts[j]->body[0]) {
				contacts.erase(contacts.begin() + j);
			}
		}
	}


	return contacts;
}
void RigidContactGenerator::addContact(RigidContact* contact)
{

	contacts[contactsCount] = contact;
	contacts[2] = contact;
	contactsCount++;
}