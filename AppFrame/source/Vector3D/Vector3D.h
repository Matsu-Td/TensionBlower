#pragma once

#include "DxLib.h"
#include <iostream>
#include <string>

class Vector3D
{
public:
	Vector3D() { _pos.x = _pos.y = _pos.z = 0.0f; } // 0‚Å‰Šú‰»
//	Vector3D() { _x = _y = _z = 0.0f; } // 0‚Å‰Šú‰»
	Vector3D(VECTOR vec) { _pos = vec; }  // 0 ˆÈŠO‚Å‰Šú‰»
//	Vector3D(float vec) { _x = _y = _z = vec; }  // 0 ˆÈŠO‚Å‰Šú‰»
	Vector3D(float x, float y, float z) { _x = x; _y = y; _z = z; }
	~Vector3D();

	Vector3D operator+=(const Vector3D& vec);
	Vector3D operator-=(const Vector3D& vec);
	Vector3D operator*=(const Vector3D& vec);
	Vector3D operator/=(const Vector3D& vec);
    float _x, _y, _z;
	VECTOR _pos;
};