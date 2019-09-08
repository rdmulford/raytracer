#ifndef VECMAT_H
#define VECMAT_H

#include <cmath>

class Vec3 {
public:
	float x, y, z;
	Vec3() : x(0), y(0), z(0) {}
	Vec3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {}
	Vec3(float xx) : x(xx), y(xx), z(xx) {}
	
	float length() const { return sqrt((x * x) + (y * y) + (z * z)); }
	void normalize() { *this /= length(); }
	Vec3 normalized() { return *this /= length(); }
	Vec3 cross(Vec3);
	float distance(Vec3);

	Vec3 operator+ (Vec3) const;
	Vec3 operator- (Vec3) const;
	Vec3 operator* (float) const;
	Vec3 operator/ (float) const;
	Vec3& operator+= (Vec3);
	Vec3& operator-= (Vec3);
	Vec3& operator*= (float);
	Vec3& operator/= (float);
	Vec3& operator= (Vec3);
	bool operator== (const Vec3&) const;
	bool operator!= (const Vec3&) const;
};

float dot(Vec3, Vec3);

#endif
