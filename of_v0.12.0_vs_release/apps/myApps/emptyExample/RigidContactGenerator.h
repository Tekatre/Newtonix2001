#pragma once
#include "RigidBody.h"
#include "BSP.h"
#include "RigidContact.h"
#include "Primitive.h"
#include "Box.h"
#include "Sphere.h"

using namespace std;
class RigidContactGenerator
{


	struct CollisionData {
		vector<RigidContact*> contacts;
		int contactsLeft;
		float friction;
		float restitution;

		void addContacts(int count, RigidContact* contact);
	};



	public:
	RigidContactGenerator();
	~RigidContactGenerator();

	//RigidContact** contacts = new RigidContact*[1000];
	vector<RigidContact*> contacts;
	CollisionData* data;
	int contactsCount = 0;

	void CreateContact(BSP* bsp);
	void CreateContactIteration(BSP* bsp, CollisionData* cd);
	//RigidContact** getContacts();
	vector<RigidContact*> getContacts();
	void addContact(RigidContact* contact);
	void clearContacts();

	void generateContacts( Primitive &firstPrimitive,  Primitive &secondPrimitive, CollisionData *data);
	void generateContacts( Sphere &firstPrimitive,  Sphere &secondPrimitive, CollisionData *data);
	void generateContacts( Box &firstPrimitive,  Sphere &secondPrimitive, CollisionData *data);
	void generateContacts( Box &firstPrimitive,  Box &secondPrimitive, CollisionData *data);
	static inline float penetrationOnAxis(Box &one, Box &two, Vecteur3D &axis, Vecteur3D &toCenter);

	static float transformToAxis(Box &box, Vecteur3D &axis);


};

