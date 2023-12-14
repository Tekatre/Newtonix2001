#pragma once
#include "RigidBody.h"
#include "BSP.h"
#include "RigidContact.h"
using namespace std;
class RigidContactGenerator
{
	public:
	RigidContactGenerator();
	~RigidContactGenerator();

	RigidContact* contacts = new RigidContact();
	int contactsCount = 0;

	void CreateContact(BSP* bsp);
	void CreateContactIteration(BSP* bsp);
	RigidContact* getContacts();
};

