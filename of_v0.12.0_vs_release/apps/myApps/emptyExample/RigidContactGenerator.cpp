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

	

	data = new CollisionData();
	data->contactsLeft = 1000;
	data->friction = 0.5f;
	data->restitution = 0.5f;

	if (!bsp->isLeaf()) {
		CreateContactIteration(bsp, data);
	}
	

	



}

void RigidContactGenerator::CreateContactIteration(BSP* bsp, CollisionData* cd)
{
	if (bsp->isLeaf()) {
		if (bsp->bodies.size() > 1) {
			//create every pair of contact
			for (int i = 0; i < bsp->bodies.size() - 1; i++)
			{
				for (int j = i + 1; j < bsp->bodies.size(); j++)
				{
				
					Primitive* prim1 = nullptr;
					Primitive* prim2 = nullptr; 

					if (bsp->bodies[i]->getShapeID() == 3) {
						prim1 = new Sphere(bsp->bodies[i]);
					}
					if (bsp->bodies[j]->getShapeID() == 3) {
						prim2 = new Sphere(bsp->bodies[j]);
					}
					if (bsp->bodies[i]->getShapeID() == 1) {
						prim1 = new Box(bsp->bodies[i]);
					}
					if (bsp->bodies[j]->getShapeID() == 1) {
						prim2 = new Box(bsp->bodies[j]);
					}
					if (prim1 && prim2) {
						generateContacts(*prim1, *prim2, cd);
					}
					



						//RigidContact* contact = new RigidContact();
						//contact->body[0] = bsp->bodies[i];
						//contact->body[1] = bsp->bodies[j];
						//contact->contactNormal = (bsp->bodies[i]->getPosition() - bsp->bodies[j]->getPosition()).normalize();
						//contact->penetration = bsp->bodies[i]->getOuterRadius() + bsp->bodies[j]->getOuterRadius() - (bsp->bodies[i]->getPosition().distance(bsp->bodies[j]->getPosition()));
						//contact->restitution = 0.5f;
						//contact->friction = 0.5f;
						//contact->worldContactPoint = (bsp->bodies[i]->getPosition() + bsp->bodies[j]->getPosition()) / 2;
						////addContact(contact);
						//contacts.push_back(contact);
					
					
				}
			}
		}
	}
	else {
		CreateContactIteration(bsp->left, cd);
		CreateContactIteration(bsp->right, cd);
	}

}
//
//RigidContact** RigidContactGenerator::getContacts()
//{
//	return contacts;
//}

vector<RigidContact*> RigidContactGenerator::getContacts()
{

	////faire en sorte qu'il n'y ai pas de double (deux couple comportant bodyA et bodyB)
	//for (int i = 0; i < contacts.size(); i++)
	//{
	//	for (int j = i + 1; j < contacts.size(); j++)
	//	{
	//		if (contacts[i]->body[0] == contacts[j]->body[0] && contacts[i]->body[1] == contacts[j]->body[1]) {
	//			contacts.erase(contacts.begin() + j);
	//		}
	//		else if (contacts[i]->body[0] == contacts[j]->body[1] && contacts[i]->body[1] == contacts[j]->body[0]) {
	//			contacts.erase(contacts.begin() + j);
	//		}
	//	}
	//}

	return data->contacts;
}
//void RigidContactGenerator::addContact(RigidContact* contact)
//{
//
//	contacts[contactsCount] = contact;
//	contacts[2] = contact;
//	contactsCount++;
//}

void RigidContactGenerator::clearContacts()
{
	contacts.clear();
	contactsCount = 0;
}


void RigidContactGenerator::generateContacts( Primitive& firstPrimitive,  Primitive& secondPrimitive, CollisionData* data)
{
	if (firstPrimitive.body->getShapeID() == 3 && secondPrimitive.body->getShapeID() == 3) {  //Sphere Sphere
		generateContacts((Sphere&)firstPrimitive, (Sphere&)secondPrimitive, data);
	}
	else if(firstPrimitive.body->getShapeID() == 1 && secondPrimitive.body->getShapeID() == 3) { //Box Sphere
			generateContacts((Box&)firstPrimitive, (Sphere&)secondPrimitive, data);
		}
	else if(firstPrimitive.body->getShapeID() == 3 && secondPrimitive.body->getShapeID() == 1) { //Sphere Box
			generateContacts((Box&)secondPrimitive, (Sphere&)firstPrimitive, data);
		}
	else {
		return;
	}
}

void RigidContactGenerator::generateContacts( Sphere& one,  Sphere& two, CollisionData* data)
{
	if (data->contactsLeft <= 0) return;
	Vecteur3D positionOne = one.getAxis(3);
	Vecteur3D positionTwo = two.getAxis(3);

	Vecteur3D midline = positionOne - positionTwo;
	float size = midline.norme();
	if (size <= 0 || size >= one.radius + two.radius) {
		return;
	}
	Vecteur3D normal= midline * ((float)1.0 / size);

	RigidContact* contact = new RigidContact();
	contact->contactNormal = normal;
	contact->worldContactPoint=positionOne-midline*(float)0.5;
	contact->penetration = (one.radius + two.radius - size);
	contact->setBodyData(one.body, two.body,data->friction,data->restitution);
	data->addContacts(1, contact);
	return ;
}

void RigidContactGenerator::CollisionData::addContacts(int count, RigidContact* contact)
{
	contactsLeft -= count;
	contacts.push_back(contact);
}

void RigidContactGenerator::generateContacts(Box& box, Sphere& sphere, CollisionData* data)
{
	if (data->contactsLeft <= 0) return;
	Vecteur3D center = sphere.getAxis(3);
	Vecteur3D relCenter = box.transform.transformInverse(center);
	float test = abs(relCenter.getX());
	if (abs(relCenter.getX()) - sphere.radius > box.halfSize.getX() || abs(relCenter.getY()) - sphere.radius > box.halfSize.getY() || abs(relCenter.getZ()) - sphere.radius > box.halfSize.getZ()) {
		return;
	}

	Vecteur3D closestPoint(0, 0, 0);
	float dist;

	dist = relCenter.getX();
	if (dist > box.halfSize.getX()) dist = box.halfSize.getX();
	if (dist < -box.halfSize.getX()) dist = -box.halfSize.getX();
	closestPoint.setX(dist);

	dist = relCenter.getY();
	if (dist > box.halfSize.getY()) dist = box.halfSize.getY();
	if (dist < -box.halfSize.getY()) dist = -box.halfSize.getY();
	closestPoint.setY(dist);

	dist = relCenter.getZ();
	if (dist > box.halfSize.getZ()) dist = box.halfSize.getZ();
	if (dist < -box.halfSize.getZ()) dist = -box.halfSize.getZ();
	closestPoint.setZ(dist);

	dist = (closestPoint - relCenter).norme();
	if (dist > sphere.radius) return;		//TODO sphere.radius² ?
	
	Vecteur3D closestPointWorld = box.transform.TransformPosition(closestPoint);

	RigidContact* contact = new RigidContact();
	contact->contactNormal = (closestPointWorld - center).normalize();
	contact->worldContactPoint = closestPointWorld;
	contact->penetration = sphere.radius - dist;
	contact->setBodyData(box.body, sphere.body, data->friction, data->restitution);
	data->addContacts(1, contact);
	return;

}

inline float RigidContactGenerator::penetrationOnAxis(Box& one, Box& two, Vecteur3D& axis, Vecteur3D& toCenter)
{
	float oneProject = transformToAxis(one, axis);
	float twoProject = transformToAxis(two, axis);

	float distance = abs(toCenter.ProduitScalaire(axis));

	return oneProject + twoProject - distance;
}

float RigidContactGenerator::transformToAxis(Box& box, Vecteur3D& axis)
{
	return box.halfSize.getX() * abs(axis.ProduitScalaire(box.getAxis(0))) +
		box.halfSize.getY() * abs(axis.ProduitScalaire(box.getAxis(1))) +
		box.halfSize.getZ() * abs(axis.ProduitScalaire(box.getAxis(2)));
}

void RigidContactGenerator::generateContacts(Box& one, Box& two, CollisionData* data)
{
	if (data->contactsLeft <= 0) return;

	float bestOverlap = FLT_MAX;
	unsigned bestCase;

}