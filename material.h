#ifndef MATERIAL_H
#define MATERIAL_H

#include "vecmat.h"

class Material {
public:
	Vec3 color;
	int reflective;

	Material() : color(Vec3(0)), reflective(0) {}
	Material(Vec3 color, int reflective) : color(color), reflective(reflective) {}
	Material& operator= (Material);
};

#endif
