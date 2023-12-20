#include "Sphere.h"



Sphere::Sphere(RigidBody* body) : Primitive(body)
{
	//cast body as a SphereRigidBody
	this->body= body;
	SphereRigidBody* sphereBody = dynamic_cast<SphereRigidBody*>(body);
	//if the cast is successful, set the radius
	if (sphereBody != nullptr)
	{
		this->radius = sphereBody->getRadius();
	}
	else
	{
		this->radius = 1.0;
	}

}