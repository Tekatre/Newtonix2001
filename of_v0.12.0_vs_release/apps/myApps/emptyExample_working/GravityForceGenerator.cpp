#include "GravityForceGenerator.h"

void GravityGenerator::updateForce(RigidBody* rigidBody, int type, Vecteur3D point)
{
	rigidBody->addForce(gravity);
}