#include "sphere.h"

RayHit Sphere::intersect(Ray ray) {
	// setup
	float t = INFINITE;
	float r = this->radius;
	Vec3 e = ray.origin;
	Vec3 d = ray.direction;
	Vec3 c = this->center;
	Vec3 eminusc = e - c;

	// miss object
	RayHit miss = RayHit(ray, Material(), Vec3(), t);

	float discriminant = (dot(d, eminusc) * dot(d, eminusc)) - dot(d, d) * (dot(eminusc, eminusc) - (r*r));

	float pos_t, neg_t;
	if (discriminant == 0) {
		t = (-dot(d, eminusc) + sqrt(discriminant)) / dot(d, d);
	} else if (discriminant > 0) {
		pos_t = (-dot(d, eminusc) + sqrt(discriminant)) / dot(d, d);
		neg_t = (-dot(d, eminusc) - sqrt(discriminant)) / dot(d, d);

		if (pos_t < 0 && neg_t < 0) {
			return miss;
		} else if (pos_t < 0 && neg_t >= 0) {
			t = neg_t;
		} else if (neg_t < 0 && pos_t >= 0) {
			t = pos_t;
		} else {
			if (pos_t < neg_t) {
				t = pos_t;
			} else {
				t = neg_t;
			}
		}

	} else {
		return miss;
	}

	// account for bump ray hits
	if (t < 0.0001) {
		return miss;
	}

	Vec3 intersect_pos = intersect_position(ray.origin, ray.direction, t);
	Vec3 normal = sphere_normal(intersect_pos, this->center);
	RayHit hit = RayHit(ray, this->mat, normal, t);
	hit.ray.origin = intersect_pos;

	return hit;
}

Vec3 sphere_normal(Vec3 intersect_pos, Vec3 center) {
	Vec3 normal;
	normal = intersect_pos - center;
	normal = normal.normalized();
	return normal;
}

Sphere& Sphere::operator= (Sphere s) {
	center = s.center;
	radius = s.radius;
	mat = s.mat;
	return *this;
}

