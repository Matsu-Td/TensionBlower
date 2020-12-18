
#include "Vector3D.h"

Vector3D Vector3D::operator+=(const Vector3D& vec)
{
	Vector3D tmp;
	tmp._x = _x + vec._x;
	tmp._y = _y + vec._y;
	tmp._z = _z + vec._z;

	return tmp;
}

Vector3D Vector3D::operator-=(const Vector3D& vec)
{
	Vector3D tmp;
	tmp._x = _x - vec._x;
	tmp._y = _y - vec._y;
	tmp._z = _z - vec._z;

	return tmp;
}

Vector3D Vector3D::operator*=(const Vector3D& vec)
{
	Vector3D tmp;
	tmp._x = _x * vec._x;
	tmp._y = _y * vec._y;
	tmp._z = _z * vec._z;

	return tmp;
}

Vector3D Vector3D::operator/=(const Vector3D& vec)
{
	Vector3D tmp;
	tmp._x = _x / vec._x;
	tmp._y = _y / vec._y;
	tmp._z = _z / vec._z;

	return tmp;
}