#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class Triangle : public Object {
public:
	Vec3 a;
	Vec3 b;
	Vec3 c;
	Material mat;
	
	Triangle() : a(Vec3()), b(Vec3()), c(Vec3()), mat(Material()) {}
	Triangle(Vec3 a, Vec3 b, Vec3 c, Material mat) : a(a), b(b), c(c), mat(mat) {}
	
	RayHit intersect(Ray ray);
	Triangle& operator= (Triangle);
};

Vec3 triangle_normal(Vec3 a, Vec3 b, Vec3 c, Vec3 intersect_pos);

#endif
