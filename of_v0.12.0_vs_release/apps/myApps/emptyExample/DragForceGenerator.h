#pragma once
#include "ForceGenerator.h"
class DragForceGenerator : public ForceGenerator
{
private:
	// coefficients choisis pour garder a peu pres le meme freinage qu'avant pour une masse de 10
	// (l'ancienne formule divisait la force par m deux fois)
	float k1 = 0.01;
	float k2 = 0.05;
public:
	void updateForce(RigidBody* rigidBody);
	Vecteur3D getBodyAnchor();
};

