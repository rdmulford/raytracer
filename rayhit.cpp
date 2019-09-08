#include "rayhit.h"
#include <stdio.h>

RayHit& RayHit::operator= (RayHit rayhit) {
	ray = rayhit.ray;
	mat = rayhit.mat;
	normal = rayhit.normal;
	t = rayhit.t;
	return *this;
}

RayHit RayHit::nearest(RayHit hits[], int n) {
	float t = INFINITE;
	RayHit best_hit;
	for (int i = 0; i < n; i += 1) {
		if(hits[i].t <= t) {
			t = hits[i].t;
			best_hit = hits[i];
		}
	}
	return best_hit;
}
