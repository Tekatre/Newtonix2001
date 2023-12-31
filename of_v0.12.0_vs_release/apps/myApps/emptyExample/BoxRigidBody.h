#include "RigidBody.h"

#pragma once
class BoxRigidBody : public RigidBody
{
private:
	int shapeID = 1;
	float width=1.0;
	float height=1.0;
	float depth=1.0;
public:
	BoxRigidBody()
		:RigidBody() {

	};
	~BoxRigidBody();

	float getWidth();
	void setWidth(float Width);
	float getHeight();
    void setHeight(float Height);
	float getDepth();
    void setDepth(float Depth);

    float getOuterRadius() override;
	int getShapeID() override;
private:
	void calculateDerivedData() override;
	
	
};

