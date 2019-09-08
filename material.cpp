#include "material.h"

Material& Material::operator= (Material mat) {
	color = mat.color;
	reflective = mat.reflective;
	return *this;
}
