#include "GravityForceGenerator.h"

void GravityGenerator::updateForce(RigidBody* rigidBody, Vecteur3D applicationPoint, int type)
{
	rigidBody->addForce(gravity);
}

//void GravityGenerator::updateForce(RigidBody* rigidBody)
//{
//	rigidBody->addForce(gravity);
//}