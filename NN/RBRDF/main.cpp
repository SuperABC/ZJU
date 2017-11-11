#include "camera.h"
#include "light.h"
#include "brdf.h"
#include "gradient.h"

#define PI 3.1415926535

para_brdf Data;
cam_coord_system Cam;
light_system Light;

glm::vec3 normalize(glm::vec3 v) {
	float len = sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	return glm::vec3(v.x / len, v.y / len, v.z / len);
}
float length(glm::vec3 v) {
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

int main() {
	read_cam_and_light("cam_and_light.txt", Cam, Light);

	FILE *fp;
	fopen_s(&fp, "tmp.txt", "rb+");

	int size;
	fread(&size, sizeof(int), 1, fp);
	std::vector<para_brdf> para_value(size);
	for (int i = 0; i < size; i++) {
		para_value[i].read(fp);
	}
	fclose(fp);

	std::vector<glm::vec3>wi;
	glm::vec3 wo;

	compute_wiwo(1000, 1000, Cam, Light, wi, wo);

	light_brdf(1000, 1000, Cam, Light, para_value[0].get_para(), para_value[0].get_brdf());
	std::vector<para_brdf> para_res(size);
	for (int i = 0; i < size; i++) {
		gradient(wi, wo, para_value[i].get_brdf(), para_res[i].get_para());
	}

	return 0;
}