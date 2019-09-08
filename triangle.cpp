#include "triangle.h"

RayHit Triangle::intersect(Ray ray) {
	float xa, xb, xc, xd, xe, ya, yb, yc, yd, ye, za, zb, zc, zd, ze;
	float m, beta, gamma;
	float a, b, c, d, e, f, g, h, i, j, k, l;
	float t = INFINITE;

	RayHit miss = RayHit(ray, Material(), Vec3(), t);

	Vec3 vert1 = this->a;
	Vec3 vert2 = this->b;
	Vec3 vert3 = this->c;
	Vec3 ray_origin = ray.origin;
	Vec3 ray_direction = ray.direction;

	xa = vert1.x;
	xb = vert2.x;
	xc = vert3.x;
	xd = ray_direction.x;
	xe = ray_origin.x;
	ya = vert1.y;
	yb = vert2.y;
	yc = vert3.y;
	yd = ray_direction.y;
	ye = ray_origin.y;
	za = vert1.z;
	zb = vert2.z;
	zc = vert3.z;
	zd = ray_direction.z;
	ze = ray_origin.z;

	a = xa - xb;
	b = ya - yb;
	c = za - zb;
	d = xa - xc;
	e = ya - yc;
	f = za - zc;
	g = xd;
	h = yd;
	i = zd;
	j = xa - xe;
	k = ya - ye;
	l = za - ze;

	m = (a * ((e * i) - (h * f))) + (b * ((g * f) - (d * i))) + (c * ((d * h) - (e * g)));
	t = (-(((f * ((a * k) - (j * b))) + (e * ((j * c) - (a * l))) + (d * ((b * l) - (k * c))))) / m);

	// account for bump ray hits (and negative t)
	if (t < 0.0001) {
		return miss;
	}

	gamma = (((i * ((a * k) - (j * b))) + (h * ((j * c) - (a * l))) + (g * ((b * l) - (k * c)))) / m);

	if ((gamma < 0) || (gamma > 1)) {
		return miss;
	}

	beta = ((j * ((e * i) - (h * f)) + (k * ((g * f) - (d * i))) + (l * ((d * h) - (e * g)))) / m);

	if ((beta < 0) || (beta > (1 - gamma))) {
		return miss;
	}

	Vec3 intersect_pos = intersect_position(ray.origin, ray.direction, t);

	Vec3 normal = triangle_normal(this->a, this->b, this->c, intersect_pos);

	RayHit hit = RayHit(ray, this->mat, normal, t);
	hit.ray.origin = intersect_pos;
	
	return hit;
}

Triangle& Triangle::operator= (Triangle t) {
	a = t.a;
	b = t.b;
	c = t.c;
	mat = t.mat;
	return *this;
}

Vec3 triangle_normal(Vec3 a, Vec3 b, Vec3 c, Vec3 intersect_pos) {
	Vec3 U = b - a;
	Vec3 V = c - a;
	Vec3 N = V.cross(U);
	Vec3 normal = intersect_pos - N;
	normal = normal.normalized();
	return normal;
}
