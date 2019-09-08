#ifndef RAY_H
#define RAY_H

#include "vecmat.h"
#include "perspective.h"

class Ray {
public:
	Vec3 origin;
	Vec3 direction;
	
	Ray() : origin(Vec3()), direction(Vec3()) {}
	Ray(Vec3 origin, Vec3 direction) : origin(origin), direction(direction) {}

	Ray get(Perspective p, Vec3 screen_cord);
	Ray& operator= (Ray);
};

Vec3 intersect_position(Vec3 origin, Vec3 direction, float t);

#endif
