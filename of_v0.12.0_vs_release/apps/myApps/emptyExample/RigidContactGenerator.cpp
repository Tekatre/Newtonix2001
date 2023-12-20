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

	//faire en sorte qu'il n'y ai pas de double (deux couple comportant bodyA et bodyB)
	for (int i = 0; i < data->contacts.size(); i++)
	{
		for (int j = i + 1; j < data->contacts.size(); j++)
		{
			if (data->contacts[i]->body[0] == data->contacts[j]->body[0] && data->contacts[i]->body[1] == data->contacts[j]->body[1]) {
				data->contacts.erase(data->contacts.begin() + j);
			}
			else if (data->contacts[i]->body[0] == data->contacts[j]->body[1] && data->contacts[i]->body[1] == data->contacts[j]->body[0]) {
				data->contacts.erase(data->contacts.begin() + j);
			}
		}
	}

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
	data->contacts.clear();
	data->contactsLeft = 1000;
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
	else if(firstPrimitive.body->getShapeID() == 1 && secondPrimitive.body->getShapeID() == 1) { //Box Box
				generateContacts((Box&)firstPrimitive, (Box&)secondPrimitive, data);
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
	unsigned bestCase = 0;

	Vecteur3D axes[15];
	axes[0] = one.getAxis(0);
	axes[1] = one.getAxis(1);
	axes[2] = one.getAxis(2);

	axes[3] = two.getAxis(0);
	axes[4] = two.getAxis(1);
	axes[5] = two.getAxis(2);

	axes[6] = one.getAxis(0)^two.getAxis(0);
	axes[7] = one.getAxis(0)^two.getAxis(1);
	axes[8] = one.getAxis(0)^two.getAxis(2);
	axes[9] = one.getAxis(1)^two.getAxis(0);
	axes[10] = one.getAxis(1)^two.getAxis(1);
	axes[11] = one.getAxis(1)^two.getAxis(2);
	axes[12] = one.getAxis(2)^two.getAxis(0);
	axes[13] = one.getAxis(2)^two.getAxis(1);
	axes[14] = one.getAxis(2)^two.getAxis(2);

	for (unsigned index = 0; index < 15; index++) {
		Vecteur3D axis = axes[index];
		if (axis.norme() < 0.0001) continue;
		axis.normalize();
		Vecteur3D toCenter = two.getAxis(3) - one.getAxis(3);
		float overlap = penetrationOnAxis(one, two, axis, toCenter );
		if (overlap < 0) return;
		if (overlap < bestOverlap) {
			bestOverlap = overlap;
			bestCase = index;
		}
	}

	Vecteur3D bestAxis = axes[bestCase];

	if (bestCase >= 6 && bestCase <= 14) {

		Vecteur3D ptOnEdgeOne = one.halfSize;
		Vecteur3D ptOnEdgeTwo = two.halfSize;
		int oneAxisIndex = 0;
		int twoAxisIndex = 0;
		#pragma region calcul One/TwoAxisIndex
		if (bestCase == 6) {
			oneAxisIndex = 0;
			twoAxisIndex = 0;
		}
		else if (bestCase == 7) {
			oneAxisIndex = 0;
			twoAxisIndex = 1;
		}
		else if (bestCase == 8) {
			oneAxisIndex = 0;
			twoAxisIndex = 2;

		}
		else if (bestCase == 9) {
			oneAxisIndex = 1;
			twoAxisIndex = 0;

		}
		else if (bestCase == 10) {
			oneAxisIndex = 1;
			twoAxisIndex = 1;

		}
		else if (bestCase == 11) {
			oneAxisIndex = 1;
			twoAxisIndex = 2;

		}
		else if (bestCase == 12) {
			oneAxisIndex = 2;
			twoAxisIndex = 0;

		}
		else if (bestCase == 13) {
			oneAxisIndex = 2;
			twoAxisIndex = 1;

		}
		else if (bestCase == 14) {
			oneAxisIndex = 2;
			twoAxisIndex = 2;
		}

		#pragma endregion

		for (int i = 0; i < 3;i++) {
			if (i == oneAxisIndex) ptOnEdgeOne.setIndex(i, 0);
			else if (one.getAxis(i).ProduitScalaire(bestAxis) > 0) ptOnEdgeOne.setIndex(i, -ptOnEdgeOne.getIndex(i));
			if (i == twoAxisIndex) ptOnEdgeTwo.setIndex(i, 0);
			else if (two.getAxis(i).ProduitScalaire(bestAxis) < 0) ptOnEdgeTwo.setIndex(i, -ptOnEdgeTwo.getIndex(i));
		}

		ptOnEdgeOne = one.transform.TransformPosition(ptOnEdgeOne);
		ptOnEdgeTwo = two.transform.TransformPosition(ptOnEdgeTwo);

		RigidContact *contact = new RigidContact();
		contact->contactNormal = bestAxis;
		contact->penetration = bestOverlap;
		contact->worldContactPoint = getContactPoint(one.getAxis(oneAxisIndex), two.getAxis(twoAxisIndex), ptOnEdgeOne, ptOnEdgeTwo);
		contact->setBodyData(one.body, two.body, data->friction, data->restitution);
		data->addContacts(1, contact);
	}
	else {
		//Face to face contact
		Vecteur3D normal = bestAxis;
		if (bestAxis.ProduitScalaire(two.getAxis(3) - one.getAxis(3)) > 0) {
			normal = normal * -1;
		}
		//Which vertex is in contact (in two's coordinate)?
		Vecteur3D vertex = two.halfSize;
		if (two.getAxis(0).ProduitScalaire(normal) < 0) vertex.setX(-vertex.getX());
		if (two.getAxis(1).ProduitScalaire(normal) < 0) vertex.setY(-vertex.getY());
		if (two.getAxis(2).ProduitScalaire(normal) < 0) vertex.setZ(-vertex.getZ());
		
		//Convert to work coordinates
		//vertex = two.transform.TransformPosition(vertex);
		if (bestCase <3) {
			vertex = two.transform * vertex;
		}
		else {
			vertex = one.transform * vertex;
		}

		//create the contact data
		RigidContact* contact = new RigidContact();
		contact->contactNormal = normal;
		contact->penetration = bestOverlap;
		contact->worldContactPoint = vertex;
		contact->setBodyData(one.body, two.body, data->friction, data->restitution);
		data->addContacts(1, contact);
		

	}
	return;

}

Vecteur3D RigidContactGenerator::getContactPoint(Vecteur3D& axisOne, Vecteur3D& axisTwo, Vecteur3D& ptOnEdgeOne, Vecteur3D& ptOnEdgeTwo)
{
	Vecteur3D toSt = ptOnEdgeOne - ptOnEdgeTwo;
	float dpStaOne = axisOne.ProduitScalaire(toSt);
	float dpStaTwo = axisTwo.ProduitScalaire(toSt);

	float smOne = axisOne.norme();
	float smTwo = axisTwo.norme();
	float dotProductEdges = axisTwo.ProduitScalaire(axisOne);
	float denom = smOne * smTwo - dotProductEdges * dotProductEdges;
	float a = (dotProductEdges * dpStaTwo - smTwo * dpStaOne) / denom;
	float b = (smOne * dpStaTwo - dotProductEdges * dpStaOne) / denom;

	Vecteur3D nearestPointOne = ptOnEdgeOne + axisOne * a;
	Vecteur3D nearestPointTwo = ptOnEdgeTwo + axisTwo * b;

	return nearestPointOne * 0.5 + nearestPointTwo * 0.5;
}