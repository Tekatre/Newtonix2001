#pragma once
#include "Vecteur3D.h"
#include "Quaternion.h"

class Matrix33
{
private: 
	double values[9];
public:
	Matrix33 operator*(const Matrix33& other) const;
	Vecteur3D operator*(const Vecteur3D& vector) const;
	Matrix33 Inverse();
	Matrix33 Transpose();
	void setOrientation(const Quaternion& q);
	void setValues(double val0,double val1, double val2, double val3, double val4, double val5, double val6, double val7, double val8);
	double getValue(int pos);
};

