#include "GravityForceGenerator.h"

void GravityGenerator::updateForce(RigidBody* rigidBody)
{
	rigidBody->addForce(gravity);
}