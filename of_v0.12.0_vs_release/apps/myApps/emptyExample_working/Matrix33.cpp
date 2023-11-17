#include "Matrix33.h"


Matrix33 Matrix33::operator*(const Matrix33& other) const
{
	Matrix33 result;
	result.values[0] = values[0] * other.values[0] + values[1] * other.values[3] + values[2] * other.values[6];
	result.values[1] = values[0] * other.values[1] + values[1] * other.values[4] + values[2] * other.values[7];
	result.values[2] = values[0] * other.values[2] + values[1] * other.values[5] + values[2] * other.values[8];

	result.values[3] = values[3] * other.values[0] + values[4] * other.values[3] + values[5] * other.values[6];
	result.values[4] = values[3] * other.values[1] + values[4] * other.values[4] + values[5] * other.values[7];
	result.values[5] = values[3] * other.values[2] + values[4] * other.values[5] + values[5] * other.values[8];

	result.values[6] = values[6] * other.values[0] + values[7] * other.values[3] + values[8] * other.values[6];
	result.values[7] = values[6] * other.values[1] + values[7] * other.values[4] + values[8] * other.values[7];
	result.values[8] = values[6] * other.values[2] + values[7] * other.values[5] + values[8] * other.values[8];

	return result;
}	

Vecteur3D Matrix33::operator*(const Vecteur3D& vector) const
{
	return Vecteur3D(values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ(),
				values[3] * vector.getX() + values[4] * vector.getY() + values[5] * vector.getZ(),
				values[6] * vector.getX() + values[7] * vector.getY() + values[8] * vector.getZ());
}

Matrix33 Matrix33::Inverse() {
		Matrix33 result;
	double determinant = values[0] * (values[4] * values[8] - values[5] * values[7]) -
		values[1] * (values[3] * values[8] - values[5] * values[6]) +
		values[2] * (values[3] * values[7] - values[4] * values[6]);

	if (determinant == 0) {
		result.values[0] = values[0];
		result.values[1] = values[1];
		result.values[2] = values[2];
		result.values[3] = values[3];
		result.values[4] = values[4];
		result.values[5] = values[5];
		result.values[6] = values[6];
		result.values[7] = values[7];		
		result.values[8] = values[8];
		return result;
	}

	double inverseDeterminant = 1.0 / determinant;

	result.values[0] = (values[4] * values[8] - values[5] * values[7]) * inverseDeterminant;
	result.values[1] = -(values[1] * values[8] - values[2] * values[7]) * inverseDeterminant;
	result.values[2] = (values[1] * values[5] - values[2] * values[4]) * inverseDeterminant;
	result.values[3] = -(values[3] * values[8] - values[5] * values[6]) * inverseDeterminant;
	result.values[4] = (values[0] * values[8] - values[2] * values[6]) * inverseDeterminant;
	result.values[5] = -(values[0] * values[5] - values[2] * values[3]) * inverseDeterminant;
	result.values[6] = (values[3] * values[7] - values[4] * values[6]) * inverseDeterminant;
	result.values[7] = -(values[0] * values[7] - values[1] * values[6]) * inverseDeterminant;
	result.values[8] = (values[0] * values[4] - values[1] * values[3]) * inverseDeterminant;

	return result;
}

Matrix33 Matrix33::Transpose() {
	Matrix33 result;
	result.values[0] = values[0];
	result.values[1] = values[3];
	result.values[2] = values[6];
	result.values[3] = values[1];
	result.values[4] = values[4];
	result.values[5] = values[7];
	result.values[6] = values[2];
	result.values[7] = values[5];
	result.values[8] = values[8];
	return result;
}

//void Matrix33::setOrientation(const Quaternion& q)
//{
//	
//}	

void Matrix33::setValues(double val0, double val1, double val2, double val3, double val4, double val5, double val6, double val7, double val8)
{
	values[0] = val0;
	values[1] = val1;
	values[2] = val2;
	values[3] = val3;
	values[4] = val4;
	values[5] = val5;
	values[6] = val6;
	values[7] = val7;
	values[8] = val8;
}

double Matrix33::getValue(int pos)
{
	return values[pos];
}