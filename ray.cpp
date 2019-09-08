#include "ray.h"

Ray Ray::get(Perspective p, Vec3 screen_cord) {
	Vec3 origin = Vec3(0);
	Vec3 direction = screen_cord - p.camera_pos;
	direction.normalize();
	return Ray(origin, direction);
}

Ray& Ray::operator= (Ray ray) {
	origin = ray.origin;
	direction = ray.direction;
	return *this;
}

Vec3 intersect_position(Vec3 origin, Vec3 direction, float t) {
	Vec3 intersection = direction;
	intersection *= t;
	intersection += origin;
	return intersection;
}
