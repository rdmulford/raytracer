#include "vecmat.h"

float Vec3::distance(Vec3 v) {
	float diffz = this->z - v.z;
	float diffY = this->y - v.y;
	float diffX = this->x - v.x;
	return sqrt((diffz * diffz) + (diffY * diffY) + (diffX * diffX));
}

Vec3 Vec3::cross(Vec3 v) {
	return Vec3((y * v.z) - (z * v.y), 
		(z * v.x) - (x * v.z), 
		(x * v.y) - (y * v.x));
}

Vec3 Vec3::operator+(Vec3 v)const{
	return Vec3(*this) += v;
}

Vec3 Vec3::operator-(Vec3 v) const{
	return Vec3(*this) -= v;
}

Vec3 Vec3::operator*(float scalar) const{
	return Vec3(*this) *= scalar;
}

Vec3 Vec3::operator/(float scalar) const{
	return Vec3(*this) /= scalar;
}

Vec3& Vec3::operator+=(Vec3 v){
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vec3& Vec3::operator-=(Vec3 v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vec3& Vec3::operator*=(float scalar){
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vec3& Vec3::operator/=(float scalar){
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vec3& Vec3::operator=(Vec3 v){
	x = v.x;
	y = v.y;
	z = v.z;
	return *this;
}

bool Vec3::operator==(const Vec3& v) const{
	return (x == v.x &&
		y == v.y &&
		z == v.z);
}

bool Vec3::operator!=(const Vec3& v) const{
	return !operator==(v);
}

float dot(Vec3 v1, Vec3 v2) { return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z); }
