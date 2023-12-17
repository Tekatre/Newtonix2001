#pragma once
#include "RigidBody.h"
class CylinderRigidBody : public RigidBody
{
private :
	float radius = 1.0;
	float height = 1.0;
	int shapeID = 2;

	void calculateDerivedData() override;
	public:
		CylinderRigidBody()
			:RigidBody() {

	};
		~CylinderRigidBody();
		float getRadius();
		void setRadius(float Radius);
		float getHeight();
		void setHeight(float Height);
		float getOuterRadius() override;
		int getShapeID() override;
};

