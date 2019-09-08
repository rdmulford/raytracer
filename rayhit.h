#ifndef RAYHIT_H
#define RAYHIT_H

#include "ray.h"
#include "material.h"
#include "vecmat.h"
#include "util.h"

class RayHit {
public:
	Ray ray;
	Material mat;
	Vec3 normal;
	float t;

	RayHit() : ray(Ray()), mat(Material()), normal(Vec3()), t(0) {}
	RayHit(Ray ray, Material mat, Vec3 normal, float t) : ray(ray), mat(mat), normal(normal), t(t) {}

	RayHit& operator= (RayHit);
	RayHit nearest(RayHit hits[], int n);
};

#endif
