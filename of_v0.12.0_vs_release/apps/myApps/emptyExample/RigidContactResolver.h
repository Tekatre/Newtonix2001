#pragma once
#include "RigidContact.h"
#include <vector>
using namespace std;

class RigidContactResolver
{
	public:
		void resolveContacts(vector<RigidContact*> contactArray, unsigned int numContacts, float duration);
private :
	void resolveInterpenetrationIteration(vector<RigidContact*> contactArray, unsigned int numContacts,int contactsLeft,float duration);
	void resolveVelocityIteration(vector<RigidContact*> contactArray, unsigned int numContacts, int contactsLeft, float duration);
};

