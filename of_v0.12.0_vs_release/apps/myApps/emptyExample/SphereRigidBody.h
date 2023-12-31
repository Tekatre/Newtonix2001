#pragma once
#include "RigidBody.h"

class SphereRigidBody : public RigidBody
{
private :
	float radius = 1.0;
	int shapeID = 3;
	void calculateDerivedData() override;
	public:
		SphereRigidBody()
			:RigidBody() {

	};
		~SphereRigidBody();
		float getRadius();
		void setRadius(float Radius);
		float getOuterRadius() override;
		int getShapeID() override;
};

