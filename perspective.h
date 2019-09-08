#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include "vecmat.h"

class Perspective {
public:
	Vec3 camera_pos;
	float screen_dist;
	float screen_width_world;
	float screen_width_pixels;

	Perspective(Vec3 camera_pos, float screen_dist, float screen_width_world, float screen_width_pixels) : camera_pos(camera_pos), screen_dist(screen_dist), screen_width_world(screen_width_world), screen_width_pixels(screen_width_pixels) {}
};

#endif
