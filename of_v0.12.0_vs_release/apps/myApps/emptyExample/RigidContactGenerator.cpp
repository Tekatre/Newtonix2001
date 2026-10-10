#include "RigidContactGenerator.h"

RigidContactGenerator::RigidContactGenerator()
{
	data = new CollisionData();
	data->contactsLeft = 1000;
	data->friction = 0.5f;
	data->restitution = 0.5f;
}

RigidContactGenerator::~RigidContactGenerator()
{
	clearContacts();
	delete data;
}

void RigidContactGenerator::CreateContact(BSP* bsp)
{
	//parcourir l'arbre, regarder si une feuille contient 2 bodies
	data->contactsLeft = 1000;

	//la racine peut elle-même être une feuille (corps tous regroupés)
	CreateContactIteration(bsp, data);
}

void RigidContactGenerator::CreateContactIteration(BSP* bsp, CollisionData* cd)
{
	if (bsp == nullptr) {
		return;
	}
	if (bsp->isLeaf()) {
		if (bsp->bodies.size() > 1) {
			//create every pair of contact
			for (int i = 0; i < bsp->bodies.size() - 1; i++)
			{
				for (int j = i + 1; j < bsp->bodies.size(); j++)
				{
					//test rapide avec les sphères englobantes avant le test précis (et coûteux)
					float maxDistance = bsp->bodies[i]->getOuterRadius() + bsp->bodies[j]->getOuterRadius();
					Vecteur3D between = bsp->bodies[i]->getPosition() - bsp->bodies[j]->getPosition();
					if (between.ProduitScalaire(between) > maxDistance * maxDistance) {
						continue;
					}
				
					Primitive* prim1 = nullptr;
					Primitive* prim2 = nullptr; 

					if (bsp->bodies[i]->getShapeID() == 3) {
						prim1 = new Sphere(bsp->bodies[i]);
					}
					if (bsp->bodies[j]->getShapeID() == 3) {
						prim2 = new Sphere(bsp->bodies[j]);
					}
					if (bsp->bodies[i]->getShapeID() == 1 || bsp->bodies[i]->getShapeID() == 2) {
						prim1 = new Box(bsp->bodies[i]);
					}
					if (bsp->bodies[j]->getShapeID() == 1 || bsp->bodies[j]->getShapeID() == 2) {
						prim2 = new Box(bsp->bodies[j]);
					}
					if (prim1 && prim2) {
						generateContacts(*prim1, *prim2, cd);
					}
					//les primitives ne servent que pour la détection
					delete prim1;
					delete prim2;
				}
			}
		}
	}
	else {
		CreateContactIteration(bsp->left, cd);
		CreateContactIteration(bsp->right, cd);
	}

}

vector<RigidContact*> RigidContactGenerator::getContacts()
{

	//faire en sorte qu'il n'y ai pas de double (deux couple comportant bodyA et bodyB) :
	//une même paire peut apparaître dans plusieurs feuilles du BSP
	for (int i = 0; i < data->contacts.size(); i++)
	{
		for (int j = i + 1; j < data->contacts.size(); )
		{
			bool sameBodies = data->contacts[i]->body[0] == data->contacts[j]->body[0] && data->contacts[i]->body[1] == data->contacts[j]->body[1];
			bool swappedBodies = data->contacts[i]->body[0] == data->contacts[j]->body[1] && data->contacts[i]->body[1] == data->contacts[j]->body[0];
			if (sameBodies || swappedBodies) {
				delete data->contacts[j];
				data->contacts.erase(data->contacts.begin() + j);
				//ne pas incrémenter j : l'élément suivant a pris la place de celui supprimé
			}
			else {
				j++;
			}
		}
	}

	return data->contacts;
}

void RigidContactGenerator::clearContacts()
{
	for (RigidContact* contact : data->contacts) {
		delete contact;
	}
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
	else if (firstPrimitive.body->getShapeID() <= 2 && secondPrimitive.body->getShapeID() == 3) { //Box Sphere
			generateContacts((Box&)firstPrimitive, (Sphere&)secondPrimitive, data);
		}
	else if(firstPrimitive.body->getShapeID() == 3 && secondPrimitive.body->getShapeID() <= 2) { //Sphere Box
			generateContacts((Box&)secondPrimitive, (Sphere&)firstPrimitive, data);
		}
	else if(firstPrimitive.body->getShapeID() <= 2 && secondPrimitive.body->getShapeID() <= 2) { //Box Box
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
	if (dist > sphere.radius) return;
	
	Vecteur3D closestPointWorld = box.transform.TransformPosition(closestPoint);

	RigidContact* contact = new RigidContact();
	if (dist > 0.0001) {
		contact->contactNormal = (closestPointWorld - center).normalize();
	}
	else {
		//le centre de la sphère est dans la boîte : la normale ne peut pas être calculée
		//avec le point le plus proche, on utilise la direction entre les centres
		contact->contactNormal = (box.getAxis(3) - center).normalize();
	}
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

void RigidContactGenerator::fillPointFaceBoxBox(Box& one, Box& two, Vecteur3D& toCenter, CollisionData* data, int axisIndex, float penetration)
{
	//Contact entre une face de "one" (axe axisIndex) et un sommet de "two"
	//La normale doit pointer de two vers one
	Vecteur3D normal = one.getAxis(axisIndex);
	if (normal.ProduitScalaire(toCenter) > 0) {
		normal = normal * -1;
	}
	//Which vertex is in contact (in two's coordinate)?
	Vecteur3D vertex = two.halfSize;
	if (two.getAxis(0).ProduitScalaire(normal) < 0) vertex.setX(-vertex.getX());
	if (two.getAxis(1).ProduitScalaire(normal) < 0) vertex.setY(-vertex.getY());
	if (two.getAxis(2).ProduitScalaire(normal) < 0) vertex.setZ(-vertex.getZ());

	//create the contact data (vertex converti en coordonnées monde avec la transformation de two)
	RigidContact* contact = new RigidContact();
	contact->contactNormal = normal;
	contact->penetration = penetration;
	contact->worldContactPoint = two.transform * vertex;
	contact->setBodyData(one.body, two.body, data->friction, data->restitution);
	data->addContacts(1, contact);
}

void RigidContactGenerator::generateContacts(Box& one, Box& two, CollisionData* data)
{
	if (data->contactsLeft <= 0) return;

	float bestOverlap = FLT_MAX;
	int bestCase = -1;

	Vecteur3D toCenter = two.getAxis(3) - one.getAxis(3);

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

	for (int index = 0; index < 15; index++) {
		//axes parallèles : le produit vectoriel est nul, l'axe n'est pas utilisable
		if (axes[index].norme() < 0.0001) continue;
		//normalize() renvoie un nouveau vecteur : il faut stocker le résultat
		axes[index] = axes[index].normalize();
		float overlap = penetrationOnAxis(one, two, axes[index], toCenter);
		if (overlap < 0) return;
		if (overlap < bestOverlap) {
			bestOverlap = overlap;
			bestCase = index;
		}
	}
	if (bestCase < 0) return;

	if (bestCase < 3) {
		//une face de one contre un sommet de two
		fillPointFaceBoxBox(one, two, toCenter, data, bestCase, bestOverlap);
	}
	else if (bestCase < 6) {
		//une face de two contre un sommet de one : on inverse les rôles
		Vecteur3D toCenterInverse = toCenter * -1;
		fillPointFaceBoxBox(two, one, toCenterInverse, data, bestCase - 3, bestOverlap);
	}
	else {
		//contact arête-arête
		int oneAxisIndex = (bestCase - 6) / 3;
		int twoAxisIndex = (bestCase - 6) % 3;
		Vecteur3D oneAxis = one.getAxis(oneAxisIndex);
		Vecteur3D twoAxis = two.getAxis(twoAxisIndex);

		//La normale doit pointer de two vers one
		Vecteur3D bestAxis = axes[bestCase];
		if (bestAxis.ProduitScalaire(toCenter) > 0) {
			bestAxis = bestAxis * -1;
		}

		//point au milieu de l'arête en contact, pour chaque boîte
		Vecteur3D ptOnEdgeOne = one.halfSize;
		Vecteur3D ptOnEdgeTwo = two.halfSize;
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
		contact->worldContactPoint = getContactPoint(oneAxis, twoAxis, ptOnEdgeOne, ptOnEdgeTwo);
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

	//carrés des normes des directions des arêtes
	float smOne = axisOne.ProduitScalaire(axisOne);
	float smTwo = axisTwo.ProduitScalaire(axisTwo);
	float dotProductEdges = axisTwo.ProduitScalaire(axisOne);
	float denom = smOne * smTwo - dotProductEdges * dotProductEdges;
	if (abs(denom) < 0.0001) {
		//arêtes quasi parallèles
		return ptOnEdgeOne * 0.5 + ptOnEdgeTwo * 0.5;
	}
	float a = (dotProductEdges * dpStaTwo - smTwo * dpStaOne) / denom;
	float b = (smOne * dpStaTwo - dotProductEdges * dpStaOne) / denom;

	Vecteur3D nearestPointOne = ptOnEdgeOne + axisOne * a;
	Vecteur3D nearestPointTwo = ptOnEdgeTwo + axisTwo * b;

	return nearestPointOne * 0.5 + nearestPointTwo * 0.5;
}
