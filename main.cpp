// Riley Mulford
// 11/26/2018
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <string>
#include "vecmat.h"
#include "material.h"
#include "perspective.h"
#include "ray.h"
#include "rayhit.h"
#include "sphere.h"
#include "triangle.h"
#include "util.h"
#include "scene.h"
#include "light.h"

using namespace std;

void render(Scene scene, Perspective p, string filename);
Vec3 trace(Scene scene, Ray ray, int depth);

int main(int argc, char** argv) {
	Perspective p = Perspective(Vec3(0, 0, 0), 2.0, 2.0, 512.0);
	Scene scene;
	string scenename;
	string filename;

	if (argc == 2) {
		scenename = argv[1];
	} else {
		printf("Please provide a scene (reference or custom)\n");
		return 0;
	}

	if (scenename == "reference") {
		filename = "reference.png";
		Material refl = Material(Vec3(0, 0, 0), 1);
		Material red = Material(Vec3(255, 0, 0), 0);
		Material blue = Material(Vec3(0, 0, 255), 0);
		Material white = Material(Vec3(255, 255, 255), 0);

		Sphere sph1 = Sphere(Vec3(0, 0, -16), 2, refl);
		Sphere sph2 = Sphere(Vec3(3, -1, -14), 1, refl);
		Sphere sph3 = Sphere(Vec3(-3, -1, -14), 1, red);

		Triangle back1 = Triangle(Vec3(-8, -2, -20), Vec3(8, -2, -20), Vec3(8, 10, -20), blue);
		Triangle back2 = Triangle(Vec3(-8, -2, -20), Vec3(8, 10, -20), Vec3(-8, 10, -20), blue);
		Triangle bot1 = Triangle(Vec3(-8, -2, -20), Vec3(8, -2, -10), Vec3(8, -2, -20), white);
		Triangle bot2 = Triangle(Vec3(-8, -2, -20), Vec3(-8, -2, -10), Vec3(8, -2, -10), white);
		Triangle right = Triangle(Vec3(8, -2, -20), Vec3(8, -2, -10), Vec3(8, 10, -20), red);

		Vec3 light = Vec3(3, 5, -15);

		Triangle* triangles = new Triangle[5];
		Sphere* spheres = new Sphere[3];

		triangles[0] = back1;
		triangles[1] = back2;
		triangles[2] = bot1;
		triangles[3] = bot2;
		triangles[4] = right;
		spheres[0] = sph1;
		spheres[1] = sph2;
		spheres[2] = sph3;

		scene = Scene(triangles, 5, spheres, 3, light, 1);

	} else if (scenename == "custom") {
		filename = "custom.png";
		Material refl = Material(Vec3(0,0,0), 1);
		Material grey = Material(Vec3(128,128,128), 0);
		Material gold = Material(Vec3(255,255,0), 0);
		Material red = Material(Vec3(200, 0, 0), 0);
		Material blue = Material(Vec3(0,0,200), 0);
		
		Sphere sph1 = Sphere(Vec3(3, 3, -15), 1, blue);
		Sphere sph2 = Sphere(Vec3(-3, 3, -15), 1, gold);
		Sphere sph3 = Sphere(Vec3(0, -1, -12), 1, red);
		Sphere sph4 = Sphere(Vec3(0, 2, -17), 2, refl);
		Sphere sph5 = Sphere(Vec3(0, 6, -18), 1, refl);

		Triangle back1 = Triangle(Vec3(-8, -2, -20), Vec3(8, -2, -20), Vec3(8, 10, -20), gold);
		Triangle back2 = Triangle(Vec3(-8, -2, -20), Vec3(8, 10, -20), Vec3(-8, 10, -20), gold);
		Triangle bot1 = Triangle(Vec3(-8, -2, -20), Vec3(8, -2, -10), Vec3(8, -2, -20), grey);
		Triangle bot2 = Triangle(Vec3(-8, -2, -20), Vec3(-8, -2, -10), Vec3(8, -2, -10), grey);
		Triangle right1 = Triangle(Vec3(8, -2, -20), Vec3(8, -2, -10), Vec3(8, 10, -20), red);
		Triangle right2 = Triangle(Vec3(8, -2, -10), Vec3(8, 10, -10), Vec3(8, 10, -20), red);
		Triangle left1 = Triangle(Vec3(-8, -2, -20), Vec3(-8, -2, -10), Vec3(-8, 10, -20), blue);
		Triangle left2 = Triangle(Vec3(-8, -2, -10), Vec3(-8, 10, -10), Vec3(-8, 10, -20), blue);
		Triangle top1 = Triangle(Vec3(-8, 8, -20), Vec3(8, 8, -10), Vec3(8, 8, -20), refl);
		Triangle top2 = Triangle(Vec3(-8, 8, -20), Vec3(-8, 8, -10), Vec3(8, 8, -10), refl);

		Vec3 light = Vec3(3, 5, -15);

		Triangle* triangles = new Triangle[10];
		Sphere* spheres = new Sphere[5];

		triangles[0] = back1;
		triangles[1] = back2;
		triangles[2] = bot1;
		triangles[3] = bot2;
		triangles[4] = right1;
		triangles[5] = right2;
		triangles[6] = left1;
		triangles[7] = left2;
		triangles[8] = top1;
		triangles[9] = top2;
		spheres[0] = sph1;
		spheres[1] = sph2;
		spheres[2] = sph3;
		spheres[3] = sph4;
		spheres[4] = sph5;

		scene = Scene(triangles, 10, spheres, 5, light, 1);
	} else {
		printf("Please provide a valid scenename (reference or custom)\n");
		return 0;
	}

	render(scene, p, filename);

	delete[] scene.triangles;
	delete[] scene.spheres;

	return 0;
}

void render(Scene scene, Perspective p, string filename) {
	unsigned char output[TOTALCOMPONENTS];

	float pixel_length = p.screen_width_world / WIDTH;
	for (unsigned int y = 0; y < HEIGHT; y += 1) {
		for (unsigned int x = 0; x < WIDTH; x += 1) {
			Vec3 screen_coord = Vec3(-1+x*pixel_length + pixel_length/2, 1-y*pixel_length - pixel_length/2, -2);
			Ray ray = ray.get(p, screen_coord);

			Vec3 color = trace(scene, ray, 0);

			int pos = (y * HEIGHT + x) * 3;
			output[pos] = color.x;
			output[pos+1] = color.y;
			output[pos+2] = color.z;
		}
	}
	stbi_write_png(filename.c_str(), WIDTH, HEIGHT, 3, output, WIDTH*3);
}

Vec3 trace(Scene scene, Ray ray, int depth) {
	Vec3 color;
	int obj_size = scene.t_size + scene.s_size;
	RayHit* hits = new RayHit[obj_size];
	
	int hit_counter = 0;
	for (int i = 0; i < scene.t_size; i += 1) {
		hits[hit_counter] = scene.triangles[i].intersect(ray);
		hit_counter += 1;
	}
	for (int i = 0; i < scene.s_size; i += 1) {
		hits[hit_counter] = scene.spheres[i].intersect(ray);
		hit_counter += 1;
	}
	RayHit hit = hit.nearest(hits, obj_size);
	delete[] hits;
	color = hit.mat.color;
	if (hit.t != INFINITE) {
		if (hit.mat.reflective == 1 && depth < MAXDEPTH) {
			Ray r;
			float A = 2.0 * dot(hit.ray.direction, hit.normal);
			Vec3 temp = hit.normal * A;
			r.direction = hit.ray.direction - temp;
			r.origin  = (r.direction * 0.001) + hit.ray.origin;

			color = trace(scene, r, depth + 1);
		} else {
			Vec3 light_dir = scene.light - hit.ray.origin;
			float diffuse = light_diffuse(hit.normal, light_dir);

			Ray light_ray = Ray(hit.ray.origin, light_dir);
			//light_ray.origin = (light_dir * 0.000001) + hit.ray.origin * -1;
			RayHit* light_hits = new RayHit[obj_size];

			int light_hit_counter = 0;
			for (int i = 0; i < scene.t_size; i += 1) {
				light_hits[light_hit_counter] = scene.triangles[i].intersect(light_ray);
				light_hit_counter += 1;
			}
			for (int i = 0; i < scene.s_size; i += 1) {
				light_hits[light_hit_counter] = scene.spheres[i].intersect(light_ray);
				light_hit_counter += 1;
			}
			RayHit light_hit = light_hit.nearest(light_hits, obj_size);
			delete[] light_hits;

			float d1 = light_hit.ray.origin.distance(scene.light);
			float d2 = light_hit.ray.origin.distance(hit.ray.origin);

			// check if in shadow and hit is in front of light
			if(light_hit.t != INFINITE && d2 < d1) {
				color = hit.mat.color * 0.2;
			} else {
				color *= diffuse;
			}
		}
	}

	//color.x = ((hit.normal.x+1)/2) * 255;
	//color.y = ((hit.normal.y+1)/2) * 255;
	//color.z = ((hit.normal.z+1)/2) * 255;

	return color;
}
