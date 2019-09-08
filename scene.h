#ifndef SCENE_H
#define SCENE_H

#include "triangle.h"
#include "sphere.h"
#include "vecmat.h"

class Scene {
public:
	Triangle* triangles;
	int t_size;
	Sphere* spheres;
	int s_size;
	Vec3 light;
	int l_size;

	Scene() : triangles(new Triangle[0]), t_size(0), spheres(new Sphere[0]), s_size(0), light(Vec3()), l_size(0) {}
	Scene(Triangle* ts, int t_size, Sphere* ss, int s_size, Vec3 l, int l_size) : triangles(ts), t_size(t_size), spheres(ss), s_size(s_size), light(l), l_size(l_size) {}
};

#endif
