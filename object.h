#ifndef OBJECT_H
#define OBJECT_H

#include "vecmat.h"
#include "material.h"
#include "ray.h"
#include "rayhit.h"
#include "util.h"
#include <stdio.h>

class Object {
public:
	Object() {}
	virtual ~Object() {}
};

#endif
