#include "light.h"

float light_diffuse(Vec3 normal, Vec3 light_dir) {
	Vec3 n = normal.normalized();
	Vec3 ld = light_dir.normalized();
	float diffuse = dot(n, ld);
	//diffuse = diffuse/2 + 0.5;
	if (diffuse < 0.2) {
		diffuse = 0.2;
	}
	return diffuse;
}
