#include "RigidContactResolver.h"

void RigidContactResolver::resolveContacts(vector<RigidContact*> contactArray, unsigned int numContacts, float duration)
{
	resolveInterpenetrationIteration(contactArray, numContacts, numContacts, duration);
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

