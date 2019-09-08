#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"

class Sphere : public Object {
public:
	Vec3 center;
	float radius;
	Material mat;

	Sphere() : center(Vec3()), radius(0), mat(Material()) {}
	Sphere(Vec3 center, float radius, Material mat) : center(center), radius(radius), mat(mat) {}

	RayHit intersect(Ray ray);
	Sphere& operator= (Sphere);
};

Vec3 sphere_normal(Vec3 intersect_pos, Vec3 center);

#endif
