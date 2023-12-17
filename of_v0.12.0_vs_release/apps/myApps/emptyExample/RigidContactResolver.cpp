#include "RigidContactResolver.h"

void RigidContactResolver::resolveContacts(vector<RigidContact*> contactArray, unsigned int numContacts, float duration)
{
	//Affichage des données
	for (unsigned int i = 0; i < numContacts; i++) {
		cout << "----------------------------------------------------------" << endl;
		cout << "Contact " << i << " : " << endl;
		cout << "Body 1 : " << contactArray[i]->body[0]->getPosition().getX() << " " << contactArray[i]->body[0]->getPosition().getY() << " " << contactArray[i]->body[0]->getPosition().getZ() << endl;
		cout << "Body 2 : " << contactArray[i]->body[1]->getPosition().getX() << " " << contactArray[i]->body[1]->getPosition().getY() << " " << contactArray[i]->body[1]->getPosition().getZ() << endl;
		cout << "World Contact Point : " << contactArray[i]->worldContactPoint.getX() << " " << contactArray[i]->worldContactPoint.getY() << " " << contactArray[i]->worldContactPoint.getZ() << endl;
		cout << "Contact Normal : " << contactArray[i]->contactNormal.getX() << " " << contactArray[i]->contactNormal.getY() << " " << contactArray[i]->contactNormal.getZ() << endl;
		cout << "Penetration : " << contactArray[i]->penetration << endl;
		cout << "Restitution : " << contactArray[i]->restitution << endl;
		cout << "Friction : " << contactArray[i]->friction << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << endl;
	}



	resolveInterpenetrationIteration(contactArray, numContacts, numContacts, duration);
	resolveVelocityIteration(contactArray, numContacts, numContacts, duration);

	
	
}

void RigidContactResolver::resolveInterpenetrationIteration(vector<RigidContact*> contactArray, unsigned int numContacts, int contactsLeft, float duration)
{
	if (contactsLeft == 0) {
		return;
	}
	float maxPenetration = 0;
	int maxIndex = 0;
	for (unsigned int i = 0; i < numContacts; i++) {
		if (contactArray[i]->penetration > maxPenetration && !contactArray[i]->InterpenetrationResolved) {
			maxPenetration = contactArray[i]->penetration;
			maxIndex = i;
		}
	}
	if (maxPenetration == 0) {
		return;
	}
	contactArray[maxIndex]->resolveInterpenetration(duration);
	contactArray[maxIndex]->InterpenetrationResolved = true;
	
	resolveInterpenetrationIteration(contactArray, numContacts, contactsLeft - 1, duration);

}

void RigidContactResolver::resolveVelocityIteration(vector<RigidContact*> contactArray, unsigned int numContacts, int contactsLeft, float duration)
{
	if (contactsLeft == 0) {
		return;
	}
	//calculate separating velocity for each contact
	float maxSeparatingVelocity = 0;
	int maxIndex = 0;
	for (unsigned int i = 0; i < numContacts; i++) {
		if (contactArray[i]->calculateSeparatingVelocity() < maxSeparatingVelocity && !contactArray[i]->VelocityResolved) {
			maxSeparatingVelocity = contactArray[i]->calculateSeparatingVelocity();
			maxIndex = i;
		}
	}
	if (maxSeparatingVelocity == 0) {
		return;
	}

	contactArray[maxIndex]->resolveVelocity(duration);
	contactArray[maxIndex]->VelocityResolved = true;

	resolveVelocityIteration(contactArray, numContacts, contactsLeft - 1, duration);

}
