#pragma once
#include "ForceGenerator.h"
class AnchorForceGenerator : public ForceGenerator
{
private:
		Vecteur3D anchor;
		Vecteur3D bodyAnchor;
		float k;
		float lzero;

	public:
		AnchorForceGenerator(Vecteur3D anchor, Vecteur3D bodyAnchor, float k, float lzero);
		void updateForce(RigidBody* rigidBody);
		Vecteur3D getBodyAnchor();
};

