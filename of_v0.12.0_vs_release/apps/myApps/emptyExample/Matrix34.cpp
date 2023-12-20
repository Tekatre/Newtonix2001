#include "Matrix34.h"
#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix33.h"

Matrix34 Matrix34::operator*(const Matrix34& other) const
{
	Matrix34 result;
	result.values[0] = values[0] * other.values[0] + values[1] * other.values[4] + values[2] * other.values[8];
	result.values[1] = values[0] * other.values[1] + values[1] * other.values[5] + values[2] * other.values[9];
	result.values[2] = values[0] * other.values[2] + values[1] * other.values[6] + values[2] * other.values[10];
	result.values[3] = values[0] * other.values[3] + values[1] * other.values[7] + values[2] * other.values[11] + values[3];

	result.values[4] = values[4] * other.values[0] + values[5] * other.values[4] + values[6] * other.values[8];
	result.values[5] = values[4] * other.values[1] + values[5] * other.values[5] + values[6] * other.values[9];
	result.values[6] = values[4] * other.values[2] + values[5] * other.values[6] + values[6] * other.values[10];
	result.values[7] = values[4] * other.values[3] + values[5] * other.values[7] + values[6] * other.values[11] + values[7];

	result.values[8] = values[8] * other.values[0] + values[9] * other.values[4] + values[10] * other.values[8];
	result.values[9] = values[8] * other.values[1] + values[9] * other.values[5] + values[10] * other.values[9];
	result.values[10] = values[8] * other.values[2] + values[9] * other.values[6] + values[10] * other.values[10];
	result.values[11] = values[8] * other.values[3] + values[9] * other.values[7] + values[10] * other.values[11] + values[11];

	return result;
}

Vecteur3D Matrix34::operator*(const Vecteur3D& vector) const
{
	Vecteur3D result;
	result.setX(values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ() + values[3]);
	result.setY(values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ() + values[7]);
	result.setZ(values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ() + values[11]);
	return result;
}

Matrix34 Matrix34::Inverse()
{
	Matrix33 sub_matrix;
	sub_matrix.setValues(values[0],values[1],values[2],values[4],values[5],values[6],values[8],values[9],values[10]);
	Matrix33 sub_matrix_inverse = sub_matrix.Inverse();
	Matrix34 result;
	result.values[0] = sub_matrix_inverse.getValue(0);
	result.values[1] = sub_matrix_inverse.getValue(1);
	result.values[2] = sub_matrix_inverse.getValue(2);
	result.values[3] = -values[3];
	result.values[4] = sub_matrix_inverse.getValue(3);
	result.values[5] = sub_matrix_inverse.getValue(4);
	result.values[6] = sub_matrix_inverse.getValue(5);
	result.values[7] = -values[7];
	result.values[8] = sub_matrix_inverse.getValue(6);
	result.values[9] = sub_matrix_inverse.getValue(7);
	result.values[10] = sub_matrix_inverse.getValue(8);
	result.values[11] = -values[11];
	return result;
}

void Matrix34::setOrientationAndPosition(const Quaternion& q, const Vecteur3D& pos)
{
	values[0] = 1 - 2 * q.getY() * q.getY() - 2 * q.getZ() * q.getZ();
	values[1] = 2 * q.getX() * q.getY() + 2 * q.getZ() * q.getW();
	values[2] = 2 * q.getX() * q.getZ() - 2 * q.getY() * q.getW();
	values[3] = pos.getX();
	values[4] = 2 * q.getX() * q.getY() - 2 * q.getZ() * q.getW();
	values[5] = 1 - 2 * q.getX() * q.getX() - 2 * q.getZ() * q.getZ();
	values[6] = 2 * q.getY() * q.getZ() + 2 * q.getX() * q.getW();
	values[7] = pos.getY();
	values[8] = 2 * q.getX() * q.getZ() + 2 * q.getY() * q.getW();
	values[9] = 2 * q.getY() * q.getZ() - 2 * q.getX() * q.getW();
	values[10] = 1 - 2 * q.getX() * q.getX() - 2 * q.getY() * q.getY();
	values[11] = pos.getZ();
}	

Vecteur3D Matrix34::TransformPosition(const Vecteur3D& vector)
{
	Vecteur3D result;
	result.setX(values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ() + values[3]);
	result.setY(values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ() + values[7]);
	result.setZ(values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ() + values[11]);
	return result;
}	

Vecteur3D Matrix34::TransformDirection(const Vecteur3D& vector)
{
	//ignore the translation part of the matrix
	Vecteur3D result;
	result.setX(values[0] * vector.getX() + values[1] * vector.getY() + values[2] * vector.getZ());
	result.setY(values[4] * vector.getX() + values[5] * vector.getY() + values[6] * vector.getZ());
	result.setZ(values[8] * vector.getX() + values[9] * vector.getY() + values[10] * vector.getZ());
	return result;

}

Matrix33 Matrix34::getOrientation()
{
	Matrix33 result;
	result.setValues(values[0],values[1],values[2],values[4],values[5],values[6],values[8],values[9],values[10]);
	return result;
}

Vecteur3D Matrix34::transformInverse(const Vecteur3D& vector) const
{
	Vecteur3D tmp = vector;
	tmp.setX(tmp.getX() - values[3]);
	tmp.setY(tmp.getY() - values[7]);
	tmp.setZ(tmp.getZ() - values[11]);
	return Vecteur3D(
		tmp.getX() * values[0] + tmp.getY() * values[4] + tmp.getZ() * values[8],
		tmp.getX() * values[1] + tmp.getY() * values[5] + tmp.getZ() * values[9],
		tmp.getX() * values[2] + tmp.getY() * values[6] + tmp.getZ() * values[10]
	);
}